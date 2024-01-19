// Copyright 2024 Allied Vision Technologies GmbH. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef UNIT_TESTS__API_MOCK__API_MOCK_HPP_
#define UNIT_TESTS__API_MOCK__API_MOCK_HPP_

#include <VmbC/VmbCTypeDefinitions.h>

#include <gmock/gmock.h>

#include <string>
#include <memory>

class APIMock
{
public:
  static std::shared_ptr<APIMock> get_instance();
  static void * get_function_ptr(const std::string & name);

  MOCK_METHOD(
    VmbError_t, VersionQuery, (VmbVersionInfo_t * versionInfo,
    VmbUint32_t sizeofVersionInfo), ());
  MOCK_METHOD(
    VmbError_t, Startup, (const VmbFilePathChar_t * pathConfiguration), ());
  MOCK_METHOD(
    void, Shutdown, (), ());
  MOCK_METHOD(
    VmbError_t, CamerasList, (VmbCameraInfo_t * cameraInfo, VmbUint32_t listLength,
    VmbUint32_t * numFound, VmbUint32_t sizeofCameraInfo), ());
  MOCK_METHOD(
    VmbError_t, CameraInfoQueryByHandle, (VmbHandle_t cameraHandle,
    VmbCameraInfo_t * info, VmbUint32_t sizeofCameraInfo), ());
  MOCK_METHOD(
    VmbError_t, CameraInfoQuery, (const char * idString, VmbCameraInfo_t * info,
    VmbUint32_t sizeofCameraInfo), ());
  MOCK_METHOD(
    VmbError_t, CameraOpen, (const char * idString, VmbAccessMode_t accessMode,
    VmbHandle_t * cameraHandle), ());
  MOCK_METHOD(
    VmbError_t, CameraClose, (const VmbHandle_t cameraHandle), ());
  MOCK_METHOD(
    VmbError_t, FeaturesList, (VmbHandle_t handle, VmbFeatureInfo_t * featureInfoList,
    VmbUint32_t listLength, VmbUint32_t * numFound, VmbUint32_t sizeofFeatureInfo), ());
  MOCK_METHOD(
    VmbError_t, FeatureInfoQuery, (const VmbHandle_t handle, const char * name,
    VmbFeatureInfo_t * featureInfo, VmbUint32_t sizeofFeatureInfo), ());
  MOCK_METHOD(
    VmbError_t, FeatureListSelected, (const VmbHandle_t handle, const char * name,
    VmbFeatureInfo_t * featureInfoList, VmbUint32_t listLength, VmbUint32_t * numFound,
    VmbUint32_t sizeofFeatureInfo), ());
  MOCK_METHOD(
    VmbError_t, FeatureAccessQuery, (const VmbHandle_t handle, const char * name,
    VmbBool_t * isReadable, VmbBool_t * isWriteable), ());
  MOCK_METHOD(
    VmbError_t, FeatureIntGet, (const VmbHandle_t handle, const char * name,
    VmbInt64_t * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureIntSet, (const VmbHandle_t handle, const char * name,
    VmbInt64_t value), ());
  MOCK_METHOD(
    VmbError_t, FeatureIntRangeQuery, (const VmbHandle_t handle, const char * name,
    VmbInt64_t * min, VmbInt64_t * max), ());
  MOCK_METHOD(
    VmbError_t, FeatureIntIncrementQuery, (const VmbHandle_t handle, const char * name,
    VmbInt64_t * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureIntValidValueSetQuery, (const VmbHandle_t handle, const char * name,
    VmbInt64_t * buffer, VmbUint32_t bufferSize, VmbUint32_t * setSize), ());
  MOCK_METHOD(
    VmbError_t, FeatureFloatGet, (const VmbHandle_t handle, const char * name,
    double * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureFloatSet, (const VmbHandle_t handle, const char * name,
    double value), ());
  MOCK_METHOD(
    VmbError_t, FeatureFloatRangeQuery, (const VmbHandle_t handle, const char * name,
    double * min, double * max), ());
  MOCK_METHOD(
    VmbError_t, FeatureFloatIncrementQuery, (const VmbHandle_t handle, const char * name,
    VmbBool_t * hasIncrement, double * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumGet, (const VmbHandle_t handle, const char * name,
    const char ** value), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumSet, (const VmbHandle_t handle, const char * name,
    const char * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumRangeQuery, (const VmbHandle_t handle, const char * name,
    const char ** nameArray, VmbUint32_t arrayLength, VmbUint32_t * numFound), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumIsAvailable, (const VmbHandle_t handle, const char * name,
    const char * value, VmbBool_t * isAvailable), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumAsInt, (const VmbHandle_t handle, const char * name,
    const char * value, VmbInt64_t * intVal), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumAsString, (VmbHandle_t handle, const char * name,
    VmbInt64_t intValue, const char ** stringValue), ());
  MOCK_METHOD(
    VmbError_t, FeatureEnumEntryGet, (const VmbHandle_t handle, const char * featureName,
    const char * entryName, VmbFeatureEnumEntry_t * featureEnumEntry,
    VmbUint32_t sizeofFeatureEnumEntry), ());
  MOCK_METHOD(
    VmbError_t, FeatureStringGet, (const VmbHandle_t handle, const char * name,
    char * buffer, VmbUint32_t bufferSize, VmbUint32_t * sizeFilled), ());
  MOCK_METHOD(
    VmbError_t, FeatureStringSet, (const VmbHandle_t handle, const char * name,
    const char * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureStringMaxlengthQuery, (const VmbHandle_t handle, const char * name,
    VmbUint32_t * maxLength), ());
  MOCK_METHOD(
    VmbError_t, FeatureBoolGet, (const VmbHandle_t handle, const char * name,
    VmbBool_t * value), ());
  MOCK_METHOD(
    VmbError_t, FeatureBoolSet, (const VmbHandle_t handle, const char * name,
    VmbBool_t value), ());
  MOCK_METHOD(
    VmbError_t, FeatureCommandRun, (const VmbHandle_t handle, const char * name), ());
  MOCK_METHOD(
    VmbError_t, FeatureCommandIsDone, (const VmbHandle_t handle, const char * name,
    VmbBool_t * isDone), ());
  MOCK_METHOD(
    VmbError_t, FeatureRawGet, (const VmbHandle_t handle, const char * name, char * buffer,
    VmbUint32_t bufferSize, VmbUint32_t * sizeFilled), ());
  MOCK_METHOD(
    VmbError_t, FeatureRawSet, (const VmbHandle_t handle, const char * name,
    const char * buffer, VmbUint32_t bufferSize), ());
  MOCK_METHOD(
    VmbError_t, FeatureRawLengthQuery, (const VmbHandle_t handle, const char * name,
    VmbUint32_t * length), ());
  MOCK_METHOD(
    VmbError_t, FeatureInvalidationRegister, (VmbHandle_t handle, const char * name,
    VmbInvalidationCallback callback, void * userContext), ());
  MOCK_METHOD(
    VmbError_t, FeatureInvalidationUnregister, (VmbHandle_t handle, const char * name,
    VmbInvalidationCallback callback), ());
  MOCK_METHOD(
    VmbError_t, PayloadSizeGet, (VmbHandle_t handle, VmbUint32_t * payloadSize), ());
  MOCK_METHOD(
    VmbError_t, FrameAnnounce, (VmbHandle_t handle, const VmbFrame_t * frame,
    VmbUint32_t sizeofFrame), ());
  MOCK_METHOD(
    VmbError_t, FrameRevoke, (VmbHandle_t handle, const VmbFrame_t * frame), ());
  MOCK_METHOD(
    VmbError_t, FrameRevokeAll, (VmbHandle_t handle), ());
  MOCK_METHOD(
    VmbError_t, CaptureStart, (VmbHandle_t handle), ());
  MOCK_METHOD(
    VmbError_t, CaptureEnd, (VmbHandle_t handle), ());
  MOCK_METHOD(
    VmbError_t, CaptureFrameQueue, (VmbHandle_t handle, const VmbFrame_t * frame,
    VmbFrameCallback callback), ());
  MOCK_METHOD(
    VmbError_t, CaptureFrameWait, (const VmbHandle_t handle, const VmbFrame_t * frame,
    VmbUint32_t timeout), ());
  MOCK_METHOD(
    VmbError_t, CaptureQueueFlush, (VmbHandle_t handle), ());
  MOCK_METHOD(
    VmbError_t, TransportLayersList, (VmbTransportLayerInfo_t * transportLayerInfo,
    VmbUint32_t listLength, VmbUint32_t * numFound, VmbUint32_t sizeofTransportLayerInfo), ());
  MOCK_METHOD(
    VmbError_t, InterfacesList, (VmbInterfaceInfo_t * interfaceInfo,
    VmbUint32_t listLength, VmbUint32_t * numFound, VmbUint32_t sizeofInterfaceInfo), ());
  MOCK_METHOD(
    VmbError_t, MemoryRead, (const VmbHandle_t handle, VmbUint64_t address,
    VmbUint32_t bufferSize, char * dataBuffer, VmbUint32_t * sizeComplete), ());
  MOCK_METHOD(
    VmbError_t, MemoryWrite, (const VmbHandle_t handle, VmbUint64_t address,
    VmbUint32_t bufferSize, const char * dataBuffer, VmbUint32_t * sizeComplete), ());
  MOCK_METHOD(
    VmbError_t, SettingsSave, (VmbHandle_t handle, const VmbFilePathChar_t * filePath,
    const VmbFeaturePersistSettings_t * settings, VmbUint32_t sizeofSettings), ());
  MOCK_METHOD(
    VmbError_t, SettingsLoad, (VmbHandle_t handle, const VmbFilePathChar_t * filePath,
    const VmbFeaturePersistSettings_t * settings, VmbUint32_t sizeofSettings), ());
  MOCK_METHOD(
    VmbError_t, ChunkDataAccess, (const VmbFrame_t * frame,
    VmbChunkAccessCallback chunkAccessCallback, void * userContext), ());
};

#endif  // UNIT_TESTS__API_MOCK__API_MOCK_HPP_
