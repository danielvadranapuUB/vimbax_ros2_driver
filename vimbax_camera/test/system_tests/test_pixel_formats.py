# Copyright 2024 Allied Vision Technologies GmbH. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# ROS client lib
import rclpy
from rclpy.node import Node
from rclpy.service import Service
from rclpy import Future
from rclpy.subscription import Subscription
from sensor_msgs.msg import Image

# pytest libs
import pytest
import launch_pytest
import launch_ros
from launch import LaunchDescription
from launch.actions import ExecuteProcess

# VimbaX_Camera msgs
from vimbax_camera_msgs.srv import FeatureEnumInfoGet, FeatureEnumSet, StreamStartStop
from test_helper import check_error

from typing import List


import logging
LOGGER = logging.getLogger()

# The required formats are listed in requirement UNIRT-1118
REQUIRED_PIXEL_FORMATS = [
    "Mono8",
    "Mono12",
    "Mono16",
    "RGB8",
    "BGR8",
    "BayerRG16",
    "BayerRG12",
    "BayerRG10",
    "BayerRG8",
    "BayerBG16",
    "BayerBG12",
    "BayerBG10",
    "BayerBG8",
    "BayerGB16",
    "BayerGB12",
    "BayerGB10",
    "BayerGB8",
    "BayerGR16",
    "BayerGR12",
    "BayerGR10",
    "BayerGR8",
    "YCBCR422_8",
]

PFNC_TO_ROS = {
    "Mono8": "mono8",
    "Mono16": "mono16",
    "Mono12": "mono16",
    "BGR8": "bgr8",
    "RGB8": "rgb8",
    "BayerBG8": "bayer_bggr8",
    "BayerGB8": "bayer_gbrg8",
    "BayerRG8": "bayer_rggb8",
    "BayerGR8": "bayer_grbg8",
    "BayerRG16": "bayer_rggb16",
    "BayerRG12": "bayer_rggb16",
    "BayerRG10": "bayer_rggb16",
    "BayerBG16": "bayer_bggr16",
    "BayerBG12": "bayer_bggr16",
    "BayerBG10": "bayer_bggr16",
    "BayerGB16": "bayer_gbrg16",
    "BayerGB12": "bayer_gbrg16",
    "BayerGB10": "bayer_gbrg16",
    "BayerGR16": "bayer_grbg16",
    "BayerGR12": "bayer_grbg16",
    "BayerGR10": "bayer_grbg16",
    "YCbCr422_8": "yuv422",
}


@pytest.fixture(autouse=True)
def init_and_shutdown_ros():
    rclpy.init()

    # The test is run here
    yield

    rclpy.shutdown()


class PixelFormatTestNode(Node):
    """Custom ROS2 Node to make testing easier."""

    def __init__(self, name: str, test_node_name: str, timeout_sec: float = 10.0):
        super().__init__(name)
        self.__rcl_timeout_sec = float(timeout_sec)
        self.__enum_info_get_srv: Service = self.create_client(
            srv_type=FeatureEnumInfoGet, srv_name=f"/{test_node_name}/features/enum_info_get"
        )
        self.__enum_set_srv: Service = self.create_client(
            srv_type=FeatureEnumSet, srv_name=f"/{test_node_name}/features/enum_set"
        )
        self.__stream_start_srv: Service = self.create_client(
            srv_type=StreamStartStop, srv_name=f"/{test_node_name}/stream_start"
        )
        self.__stream_stop_srv: Service = self.create_client(
            srv_type=StreamStartStop, srv_name=f"/{test_node_name}/stream_stop"
        )
        self.__image_future: Future = Future()
        self.__image_sub: Subscription = self.create_subscription(
            Image,
            f"/{test_node_name}/image_raw",
            lambda msg: self.__image_future.set_result(msg),
            0,
        )

        # Magic timeout value
        assert self.__enum_info_get_srv.wait_for_service(timeout_sec=self.__rcl_timeout_sec)
        assert self.__enum_set_srv.wait_for_service(timeout_sec=self.__rcl_timeout_sec)
        assert self.__stream_start_srv.wait_for_service(timeout_sec=self.__rcl_timeout_sec)
        assert self.__stream_stop_srv.wait_for_service(timeout_sec=self.__rcl_timeout_sec)

    def __call_service_sync(self, srv: Service, request):
        future = srv.call_async(request)
        rclpy.spin_until_future_complete(
            node=self, future=future, timeout_sec=self.__rcl_timeout_sec
        )
        return future.result()

    def stop_stream(self) -> StreamStartStop.Response:
        return self.__call_service_sync(self.__stream_stop_srv, StreamStartStop.Request())

    def start_stream(self) -> StreamStartStop.Response:
        return self.__call_service_sync(self.__stream_start_srv, StreamStartStop.Request())

    def get_supported_pixel_formats(self) -> List[str]:
        """Receives the list of available pixel formats from the camera."""
        req: FeatureEnumInfoGet.Request = FeatureEnumInfoGet.Request()
        req.feature_name = "PixelFormat"
        res: FeatureEnumInfoGet.Response = self.__call_service_sync(self.__enum_info_get_srv, req)
        check_error(res.error)

        return res.available_values

    def set_pixel_format(self, format: str) -> FeatureEnumSet.Response:
        """Set the pixel format published by the camera."""
        req: FeatureEnumSet.Request = FeatureEnumSet.Request()
        req.feature_name = "PixelFormat"
        req.value = format
        return self.__call_service_sync(self.__enum_set_srv, req)

    def get_latest_image(self) -> Image:
        """Spins the default context until an Image is received from the Camera."""
        # Clear the future to receive a new Image
        self.__image_future = rclpy.Future()
        rclpy.spin_until_future_complete(
            node=self, future=self.__image_future, timeout_sec=self.__rcl_timeout_sec
        )
        return self.__image_future.result()


@launch_pytest.fixture(scope='class')
def vimbax_camera_node_class_scope():
    return LaunchDescription([
        ExecuteProcess(
            cmd=[
                "ros2",
                "node",
                "list",
                "--all"
            ],
            shell=True,
            output='both',
        ),
        launch_ros.actions.Node(
            package='vimbax_camera',
            namespace="/test_pixel_formats",
            executable='vimbax_camera_node',
            name="test_pixel_formats"
        ),
        launch_pytest.actions.ReadyToTest()
    ])


@pytest.mark.launch(fixture=vimbax_camera_node_class_scope)
class TestPixelFormat:
    """One VimbaXCamera node is started for all tests."""

    @pytest.mark.parametrize("format", REQUIRED_PIXEL_FORMATS)
    def test_format(self, format, launch_context, node_test_id):

        node: PixelFormatTestNode = PixelFormatTestNode(
            f"pytest_client_node_{node_test_id}", "test_pixel_formats", timeout_sec=5.0)

        # The PixelFormat cannot be changed while the camera is streaming
        check_error(node.stop_stream().error)

        # We can only test the formats required and supported by the attached camera
        if not (format in node.get_supported_pixel_formats()):
            pytest.skip(f"{format} is not supported by current camera")
            node.destroy_node()
            return

        # Set the pixel format
        LOGGER.info(f"Testing format: {format}")

        check_error(node.set_pixel_format(format).error)
        check_error(node.start_stream().error)

        image: Image = node.get_latest_image()

        check_error(node.stop_stream().error)
        # Assert the pixel format of the image matches the requested format
        assert image is not None
        # Because the ROS and PFNC formats differ in naming the encoding needs to be translated
        assert image.encoding == PFNC_TO_ROS[format]
        node.destroy_node()

    def test_invalid_value(self, launch_context, node_test_id):

        node: PixelFormatTestNode = PixelFormatTestNode(
            f"pytest_client_node_{node_test_id}", "test_pixel_formats", timeout_sec=5.0)
        try:
            node.stop_stream()
            # This should fail
            res = node.set_pixel_format("")
            error_msg: str = "Unexpected error: {} ({}); Expected -11 (VmbErrorInvalidValue)"
            assert res.error.code == -11,  error_msg.format(res.error.code, res.error.text)
        finally:
            node.destroy_node()
