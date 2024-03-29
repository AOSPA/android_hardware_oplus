/*
 * Copyright (C) 2024 Paranoid Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <functional>
#include <memory>

#include <C2AllocatorBlob.h>
#include <C2AllocatorGralloc.h>
#include <C2AllocatorIon.h>
#include <C2BufferPriv.h>
#include <C2PlatformStorePluginLoader.h>

extern "C" c2_status_t
_ZN27C2PlatformStorePluginLoader15createAllocatorEjPNSt3__110shared_ptrI11C2AllocatorEENS0_8functionIFvPS2_EEE(
    void *thisptr, unsigned int allocatorId,
    std::shared_ptr<C2Allocator> *allocator,
    std::function<void(C2BlockPool *)> deleter);

extern "C" c2_status_t
_ZN27C2PlatformStorePluginLoader15createAllocatorEjPNSt3__110shared_ptrI11C2AllocatorEE(
    void *thisptr, unsigned int allocatorId,
    std::shared_ptr<C2Allocator> *allocator) {
  return _ZN27C2PlatformStorePluginLoader15createAllocatorEjPNSt3__110shared_ptrI11C2AllocatorEENS0_8functionIFvPS2_EEE(
      thisptr, allocatorId, allocator, [](C2BlockPool *ptr) { delete ptr; });
}

extern "C" void *
_ZN17C2PooledBlockPoolC1ERKNSt3__110shared_ptrI11C2AllocatorEEyNS_13BufferPoolVerE(
    void *thisptr, const std::shared_ptr<C2Allocator> &allocator,
    const C2BasicGraphicBlockPool::local_id_t localId, C2PooledBlockPool::BufferPoolVer ver);

extern "C" void *
_ZN17C2PooledBlockPoolC1ERKNSt3__110shared_ptrI11C2AllocatorEEy(
    void *thisptr, const std::shared_ptr<C2Allocator> &allocator,
    const C2BasicGraphicBlockPool::local_id_t localId) {
  return _ZN17C2PooledBlockPoolC1ERKNSt3__110shared_ptrI11C2AllocatorEEyNS_13BufferPoolVerE(
      thisptr, allocator, localId, C2PooledBlockPool::VER_HIDL);
}

namespace android {
const char *MEDIA_MIMETYPE_AUDIO_OZOAUDIO = "audio/ozoaudio";
}
