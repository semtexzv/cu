#pragma once

//#include <C:\\Program Files\NVIDIA GPU Computing
//Toolkit\CUDA\v8.0\include\cuda.h>

#include <cuda.h>
#include <cudaProfiler.h>

//#include </opt/cuda/include/cuda.h> // cudaError_t, CUDARTAPI, etc.
//#include </opt/cuda/include/cudaProfiler.h>

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

/// Wrapper for CUDA's dynamic link library.
#ifndef __dv
#define __dv(x)
#endif

#ifdef linux
#include <dlfcn.h> //dyopen, dlsym, dlclose
#include <errno.h> // fopen_s
#include <stdlib.h>
#include <string.h> //memeset
#endif

extern "C" bool cuda_init();

#define FUN(name)                                                              \
  typedef decltype(&name) ptr_##name;                                          \
  ptr_##name v_##name = NULL;

FUN(cuInit);
FUN(cuGetErrorName);
FUN(cuGetErrorString);

FUN(cuDriverGetVersion);
FUN(cuDeviceGet);
FUN(cuDeviceGetAttribute);
FUN(cuDeviceGetCount);
FUN(cuDeviceGetName);
FUN(cuDeviceGetProperties);
FUN(cuDeviceTotalMem_v2);
FUN(cuDeviceComputeCapability);

FUN(cuDeviceGetPCIBusId);
FUN(cuDeviceGetByPCIBusId);

FUN(cuDevicePrimaryCtxGetState);
FUN(cuDevicePrimaryCtxRelease);
FUN(cuDevicePrimaryCtxReset);
FUN(cuDevicePrimaryCtxRetain);
FUN(cuDevicePrimaryCtxSetFlags);

FUN(cuCtxAttach);
FUN(cuCtxDetach);

FUN(cuCtxCreate_v2);
FUN(cuCtxDestroy_v2);
FUN(cuCtxGetApiVersion);
FUN(cuCtxGetCacheConfig);
FUN(cuCtxGetCurrent);
FUN(cuCtxGetDevice);
FUN(cuCtxGetFlags);
FUN(cuCtxGetLimit);

FUN(cuCtxGetSharedMemConfig);
FUN(cuCtxSetSharedMemConfig);

FUN(cuCtxGetStreamPriorityRange);

FUN(cuCtxPopCurrent_v2);
FUN(cuCtxPushCurrent_v2);
FUN(cuCtxSetCacheConfig);
FUN(cuCtxSetCurrent);
FUN(cuCtxSetLimit)
FUN(cuCtxSynchronize);

FUN(cuLinkAddData_v2);
FUN(cuLinkAddFile_v2);
FUN(cuLinkComplete);
FUN(cuLinkCreate_v2);
FUN(cuLinkDestroy);
FUN(cuModuleGetFunction);
FUN(cuModuleGetGlobal_v2);
FUN(cuModuleGetSurfRef);
FUN(cuModuleGetTexRef);
FUN(cuModuleLoad);
FUN(cuModuleLoadData);
FUN(cuModuleLoadDataEx);
FUN(cuModuleLoadFatBinary);
FUN(cuModuleUnload);

FUN(cuIpcCloseMemHandle);
FUN(cuIpcGetEventHandle);
FUN(cuIpcGetMemHandle);
FUN(cuIpcOpenEventHandle);
FUN(cuIpcOpenMemHandle);

FUN(cuMemAlloc_v2);
FUN(cuMemAllocHost_v2);
FUN(cuMemAllocManaged);
FUN(cuMemAllocPitch_v2);
FUN(cuMemFree_v2);
FUN(cuMemFreeHost);
FUN(cuMemGetAddressRange_v2);
FUN(cuMemGetInfo_v2);
FUN(cuMemHostAlloc);
FUN(cuMemHostGetDevicePointer_v2);
FUN(cuMemHostGetFlags);
FUN(cuMemHostRegister_v2);
FUN(cuMemHostUnregister);

FUN(cuMemcpy);
FUN(cuMemcpy2D_v2);
FUN(cuMemcpy2DAsync_v2);
FUN(cuMemcpy2DUnaligned_v2);
FUN(cuMemcpy3D_v2);
FUN(cuMemcpy3DAsync_v2);

FUN(cuMemcpyAtoA_v2)
FUN(cuMemcpyAtoD_v2);
FUN(cuMemcpyAtoH_v2);
FUN(cuMemcpyAtoHAsync_v2);
FUN(cuMemcpyDtoA_v2);
FUN(cuMemcpyDtoD_v2);
FUN(cuMemcpyDtoDAsync_v2);
FUN(cuMemcpyDtoHAsync_v2);
FUN(cuMemcpyHtoA_v2);
FUN(cuMemcpyHtoAAsync_v2);
FUN(cuMemcpyHtoDAsync_v2);

FUN(cuMemcpyHtoD_v2);
FUN(cuMemcpyDtoH_v2);

FUN(cuMemsetD2D8_v2);
FUN(cuMemsetD2D16_v2);
FUN(cuMemsetD2D32_v2);
FUN(cuMemsetD16_v2);
FUN(cuMemsetD32_v2);
FUN(cuMemsetD8_v2);

FUN(cuMemAdvise);
FUN(cuMemPrefetchAsync);
FUN(cuMemRangeGetAttribute);
FUN(cuMemRangeGetAttributes);
FUN(cuPointerGetAttribute);
FUN(cuPointerGetAttributes);
FUN(cuPointerSetAttribute);

FUN(cuStreamAddCallback);
FUN(cuStreamAttachMemAsync);
FUN(cuStreamCreate);
FUN(cuStreamCreateWithPriority);
FUN(cuStreamDestroy_v2);
FUN(cuStreamGetFlags);
FUN(cuStreamGetPriority);
FUN(cuStreamQuery);
FUN(cuStreamSynchronize);
FUN(cuStreamWaitEvent);

FUN(cuEventCreate);
FUN(cuEventDestroy_v2);
FUN(cuEventElapsedTime);
FUN(cuEventQuery);
FUN(cuEventRecord);
FUN(cuEventSynchronize);
FUN(cuStreamBatchMemOp);
FUN(cuStreamWaitValue32);
FUN(cuStreamWriteValue32);

FUN(cuFuncGetAttribute);
FUN(cuFuncSetCacheConfig);
FUN(cuFuncSetSharedMemConfig);
FUN(cuLaunchKernel);

FUN(cuOccupancyMaxActiveBlocksPerMultiprocessor);
FUN(cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags);
FUN(cuOccupancyMaxPotentialBlockSize);
FUN(cuOccupancyMaxPotentialBlockSizeWithFlags);

FUN(cuSurfRefGetArray);
FUN(cuSurfRefSetArray);

FUN(cuTexRefCreate);
FUN(cuTexRefDestroy);

FUN(cuTexRefGetAddress_v2);
FUN(cuTexRefGetAddressMode);
FUN(cuTexRefGetArray);
FUN(cuTexRefGetFilterMode);


FUN(cuProfilerInitialize);
FUN(cuProfilerStart);
FUN(cuProfilerStop);


#undef FUN

#ifdef __cplusplus
extern "C" {
#endif

CUresult CUDAAPI cuGetErrorName(CUresult error, const char **pStr) {
  return v_cuGetErrorName(error, pStr);
}

CUresult CUDAAPI cuGetErrorString(CUresult error, const char **pStr) {
  return v_cuGetErrorString(error, pStr);
}

/*
CUresult CUDAAPI cuArray3DCreate(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR
*pAllocateArray) {

    return v_cuArray3DCreate(pHandle, pAllocateArray);
}

CUresult CUDAAPI cuArray3DCreate_v2(CUarray *pHandle, const
CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray) {

    return v_cuArray3DCreate_v2(pHandle, pAllocateArray);
}

CUresult CUDAAPI cuArray3DGetDescriptor(CUDA_ARRAY3D_DESCRIPTOR
*pArrayDescriptor, CUarray hArray) {

    return v_cuArray3DGetDescriptor(pArrayDescriptor, hArray);
}

CUresult CUDAAPI cuArray3DGetDescriptor_v2(CUDA_ARRAY3D_DESCRIPTOR
*pArrayDescriptor, CUarray hArray) {

    return v_cuArray3DGetDescriptor_v2(pArrayDescriptor, hArray);
}
CUresult CUDAAPI cuArrayCreate(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR
*pAllocateArray) {

    return v_cuArrayCreate(pHandle, pAllocateArray);
}

CUresult CUDAAPI cuArrayCreate_v2(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR
*pAllocateArray) {

    return v_cuArrayCreate_v2(pHandle, pAllocateArray);
}

CUresult CUDAAPI cuArrayDestroy(CUarray hArray) {

    return v_cuArrayDestroy(hArray);
}

CUresult CUDAAPI cuArrayGetDescriptor(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor,
CUarray hArray) {

    return v_cuArrayGetDescriptor(pArrayDescriptor, hArray);
}

CUresult CUDAAPI cuArrayGetDescriptor_v2(CUDA_ARRAY_DESCRIPTOR
*pArrayDescriptor, CUarray hArray) {

    return v_cuArrayGetDescriptor_v2(pArrayDescriptor, hArray);
}

*/

CUresult CUDAAPI cuCtxAttach(CUcontext *pctx, unsigned int flags) {

  return v_cuCtxAttach(pctx, flags);
}

CUresult CUDAAPI cuCtxDetach(CUcontext ctx) { return v_cuCtxDetach(ctx); }
/*
CUresult CUDAAPI cuCtxCreate(CUcontext *pctx, unsigned int flags, CUdevice dev)
{

    return v_cuCtxCreate(pctx, flags, dev);
}
 */

CUresult CUDAAPI cuCtxCreate_v2(CUcontext *pctx, unsigned int flags,
                                CUdevice dev) {

  return v_cuCtxCreate_v2(pctx, flags, dev);
}

CUresult CUDAAPI cuCtxDestroy_v2(CUcontext ctx) {

  return v_cuCtxDestroy_v2(ctx);
}

CUresult CUDAAPI cuCtxGetApiVersion(CUcontext ctx, unsigned int *version) {
  return v_cuCtxGetApiVersion(ctx, version);
}

CUresult CUDAAPI cuCtxGetCacheConfig(CUfunc_cache *pconfig) {
  return v_cuCtxGetCacheConfig(pconfig);
}

CUresult CUDAAPI cuCtxGetDevice(CUdevice *device) {

  return v_cuCtxGetDevice(device);
}

CUresult CUDAAPI cuCtxGetLimit(size_t *pvalue, CUlimit limit) {
  return v_cuCtxGetLimit(pvalue, limit);
}

CUresult CUDAAPI cuCtxPopCurrent_v2(CUcontext *pctx) {

  return v_cuCtxPopCurrent_v2(pctx);
}

CUresult CUDAAPI cuCtxPushCurrent_v2(CUcontext ctx) {

  return v_cuCtxPushCurrent_v2(ctx);
}

CUresult CUDAAPI cuCtxSetCacheConfig(CUfunc_cache config) {

  return v_cuCtxSetCacheConfig(config);
}

CUresult CUDAAPI cuCtxSetCurrent(CUcontext ctx) {
  return v_cuCtxSetCurrent(ctx);
}

CUresult CUDAAPI cuCtxSetLimit(CUlimit limit, size_t value) {

  return v_cuCtxSetLimit(limit, value);
}

CUresult CUDAAPI cuCtxGetSharedMemConfig(CUsharedconfig *pConfig) {
  return v_cuCtxGetSharedMemConfig(pConfig);
}

CUresult CUDAAPI cuCtxSetSharedMemConfig(CUsharedconfig config) {
  return v_cuCtxSetSharedMemConfig(config);
}

CUresult CUDAAPI cuCtxGetStreamPriorityRange(int *leastPriority,
                                             int *greatestPriority) {
  return v_cuCtxGetStreamPriorityRange(leastPriority, greatestPriority);
}

CUresult CUDAAPI cuCtxGetFlags(unsigned int *flags) {
  return v_cuCtxGetFlags(flags);
}
CUresult CUDAAPI cuCtxSynchronize(void) { return v_cuCtxSynchronize(); }

CUresult CUDAAPI cuDeviceGet(CUdevice *device, int ordinal) {

  return v_cuDeviceGet(device, ordinal);
}

CUresult CUDAAPI cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib,
                                      CUdevice dev) {

  return v_cuDeviceGetAttribute(pi, attrib, dev);
}

CUresult CUDAAPI cuDeviceGetCount(int *count) {

  return v_cuDeviceGetCount(count);
}

CUresult CUDAAPI cuDeviceGetName(char *name, int len, CUdevice dev) {

  return v_cuDeviceGetName(name, len, dev);
}

CUresult CUDAAPI cuDeviceGetProperties(CUdevprop *prop, CUdevice dev) {

  return v_cuDeviceGetProperties(prop, dev);
}

CUresult CUDAAPI cuDeviceTotalMem_v2(size_t *bytes, CUdevice dev) {

  return v_cuDeviceTotalMem_v2(bytes, dev);
}

CUresult CUDAAPI cuDeviceComputeCapability(int *major, int *minor,
                                           CUdevice dev) {

  return v_cuDeviceComputeCapability(major, minor, dev);
}

CUresult CUDAAPI cuDeviceGetByPCIBusId(CUdevice *dev, const char *pciBusId) {
  return v_cuDeviceGetByPCIBusId(dev, pciBusId);
}

CUresult CUDAAPI cuDeviceGetPCIBusId(char *pciBusId, int len, CUdevice dev) {
  return v_cuDeviceGetPCIBusId(pciBusId, len, dev);
}

CUresult CUDAAPI cuDevicePrimaryCtxRetain(CUcontext *pctx, CUdevice dev) {
  return v_cuDevicePrimaryCtxRetain(pctx, dev);
}
CUresult CUDAAPI cuDevicePrimaryCtxRelease(CUdevice dev) {
  return v_cuDevicePrimaryCtxRelease(dev);
}

CUresult CUDAAPI cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags) {
  return v_cuDevicePrimaryCtxSetFlags(dev, flags);
}

CUresult CUDAAPI cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int *flags,
                                            int *active) {
  return v_cuDevicePrimaryCtxGetState(dev, flags, active);
}

CUresult CUDAAPI cuDevicePrimaryCtxReset(CUdevice dev) {
  return v_cuDevicePrimaryCtxReset(dev);
}

CUresult CUDAAPI cuDriverGetVersion(int *driverVersion) {

  return v_cuDriverGetVersion(driverVersion);
}

CUresult CUDAAPI cuEventCreate(CUevent *phEvent, unsigned int Flags) {

  return v_cuEventCreate(phEvent, Flags);
}

CUresult CUDAAPI cuEventDestroy_v2(CUevent hEvent) {

  return v_cuEventDestroy_v2(hEvent);
}

CUresult CUDAAPI cuEventElapsedTime(float *pMilliseconds, CUevent hStart,
                                    CUevent hEnd) {

  return v_cuEventElapsedTime(pMilliseconds, hStart, hEnd);
}

CUresult CUDAAPI cuEventQuery(CUevent hEvent) { return v_cuEventQuery(hEvent); }

CUresult CUDAAPI cuEventRecord(CUevent hEvent, CUstream hStream) {

  return v_cuEventRecord(hEvent, hStream);
}

CUresult CUDAAPI cuEventSynchronize(CUevent hEvent) {

  return v_cuEventSynchronize(hEvent);
}

CUresult CUDAAPI cuFuncGetAttribute(int *pi, CUfunction_attribute attrib,
                                    CUfunction hfunc) {

  return v_cuFuncGetAttribute(pi, attrib, hfunc);
}

CUresult CUDAAPI cuLaunchKernel(CUfunction f, unsigned int gridDimX,
                                unsigned int gridDimY, unsigned int gridDimZ,
                                unsigned int blockDimX, unsigned int blockDimY,
                                unsigned int blockDimZ,
                                unsigned int sharedMemBytes, CUstream hStream,
                                void **kernelParams, void **extra) {
  return v_cuLaunchKernel(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY,
                          blockDimZ, sharedMemBytes, hStream, kernelParams,
                          extra);
}

CUresult CUDAAPI cuOccupancyMaxActiveBlocksPerMultiprocessor(
    int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize) {
  return v_cuOccupancyMaxActiveBlocksPerMultiprocessor(
      numBlocks, func, blockSize, dynamicSMemSize);
}
/*
CUresult CUDAAPI cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z) {

    return v_cuFuncSetBlockShape(hfunc, x, y, z);
}

CUresult CUDAAPI cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes) {

    return v_cuFuncSetSharedSize(hfunc, bytes);
}

CUresult CUDAAPI cuGetExportTable(const void **ppExportTable, const CUuuid
*pExportTableId) {

    return v_cuGetExportTable(ppExportTable, pExportTableId);
}

CUresult CUDAAPI cuGraphicsMapResources(unsigned int count, CUgraphicsResource
*resources, CUstream hStream) {

    return v_cuGraphicsMapResources(count, resources, hStream);
}

CUresult CUDAAPI
_cuGraphicsResourceGetMappedPointer(CUdeviceptr *pDevPtr, unsigned int *pSize,
CUgraphicsResource resource) {

    return v_cuGraphicsResourceGetMappedPointer(pDevPtr, pSize, resource);
}

CUresult CUDAAPI
_cuGraphicsResourceGetMappedPointer_v2(CUdeviceptr *pDevPtr, unsigned int
*pSize, CUgraphicsResource resource) {

    return v_cuGraphicsResourceGetMappedPointer_v2(pDevPtr, pSize, resource);
}

CUresult CUDAAPI cuGraphicsResourceSetMapFlags(CUgraphicsResource resource,
unsigned int flags) {

    return v_cuGraphicsResourceSetMapFlags(resource, flags);
}

CUresult CUDAAPI
_cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource
resource, unsigned int arrayIndex,
                                     unsigned int mipLevel) {

    return v_cuGraphicsSubResourceGetMappedArray(pArray, resource, arrayIndex,
mipLevel);
}

CUresult CUDAAPI cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource
*resources, CUstream hStream) {

    return v_cuGraphicsUnmapResources(count, resources, hStream);
}

CUresult CUDAAPI cuGraphicsUnregisterResource(CUgraphicsResource resource) {

    return v_cuGraphicsUnregisterResource(resource);
}

 */

CUresult CUDAAPI cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config) {

  return v_cuFuncSetCacheConfig(hfunc, config);
}

CUresult CUDAAPI cuInit(unsigned int Flags) { return v_cuInit(Flags); }

/*
CUresult CUDAAPI cuLaunch(CUfunction f) {

    return v_cuLaunch(f);
}

CUresult CUDAAPI cuLaunchGrid(CUfunction f, int grid_width, int grid_height) {

    return v_cuLaunchGrid(f, grid_width, grid_height);
}

CUresult CUDAAPI cuLaunchGridAsync(CUfunction f, int grid_width, int
grid_height, CUstream hStream) {

    return v_cuLaunchGridAsync(f, grid_width, grid_height, hStream);
}

CUresult CUDAAPI cuMemAlloc(CUdeviceptr *dptr, unsigned int bytesize) {

    return v_cuMemAlloc(dptr, bytesize);
}
 */

CUresult CUDAAPI cuMemAlloc_v2(CUdeviceptr *dptr, size_t bytesize) {

  return v_cuMemAlloc_v2(dptr, bytesize);
}

/*
CUresult CUDAAPI cuMemAllocHost(void **pp, unsigned int bytesize) {

    return v_cuMemAllocHost(pp, bytesize);
}
*/
CUresult CUDAAPI cuMemAllocHost_v2(void **pp, size_t bytesize) {

  return v_cuMemAllocHost_v2(pp, bytesize);
}

/*
CUresult CUDAAPI
_cuMemAllocPitch(CUdeviceptr *dptr, unsigned int *pPitch, unsigned int
WidthInBytes, unsigned int Height,
                 unsigned int ElementSizeBytes) {

    return v_cuMemAllocPitch(dptr, pPitch, WidthInBytes, Height,
ElementSizeBytes);
}
 */

CUresult CUDAAPI _cuMemAllocPitch_v2(CUdeviceptr *dptr, size_t *pPitch,
                                     size_t WidthInBytes, size_t Height,
                                     unsigned int ElementSizeBytes) {

  return v_cuMemAllocPitch_v2(dptr, pPitch, WidthInBytes, Height,
                              ElementSizeBytes);
}

CUresult CUDAAPI cuMemcpy2D_v2(const CUDA_MEMCPY2D *pCopy) {

  return v_cuMemcpy2D_v2(pCopy);
}

CUresult CUDAAPI cuMemcpy2DAsync_v2(const CUDA_MEMCPY2D *pCopy,
                                    CUstream hStream) {

  return v_cuMemcpy2DAsync_v2(pCopy, hStream);
}

CUresult CUDAAPI cuMemcpy2DUnaligned_v2(const CUDA_MEMCPY2D *pCopy) {

  return v_cuMemcpy2DUnaligned_v2(pCopy);
}

CUresult CUDAAPI cuMemcpy3D_v2(const CUDA_MEMCPY3D *pCopy) {

  return v_cuMemcpy3D_v2(pCopy);
}

CUresult CUDAAPI cuMemcpy3DAsync_v2(const CUDA_MEMCPY3D *pCopy,
                                    CUstream hStream) {

  return v_cuMemcpy3DAsync_v2(pCopy, hStream);
}

CUresult CUDAAPI cuMemcpyAtoA_v2(CUarray dstArray, size_t dstOffset,
                                 CUarray srcArray, size_t srcOffset,
                                 size_t ByteCount) {

  return v_cuMemcpyAtoA_v2(dstArray, dstOffset, srcArray, srcOffset, ByteCount);
}

CUresult CUDAAPI cuMemcpyAtoD_v2(CUdeviceptr dstDevice, CUarray srcArray,
                                 size_t srcOffset, size_t ByteCount) {

  return v_cuMemcpyAtoD_v2(dstDevice, srcArray, srcOffset, ByteCount);
}

CUresult CUDAAPI cuMemcpyAtoH_v2(void *dstHost, CUarray srcArray,
                                 size_t srcOffset, size_t ByteCount) {

  return v_cuMemcpyAtoH_v2(dstHost, srcArray, srcOffset, ByteCount);
}

CUresult CUDAAPI cuMemcpyAtoHAsync_v2(void *dstHost, CUarray srcArray,
                                      size_t srcOffset, size_t ByteCount,
                                      CUstream hStream) {

  return v_cuMemcpyAtoHAsync_v2(dstHost, srcArray, srcOffset, ByteCount,
                                hStream);
}

CUresult CUDAAPI cuMemcpyDtoA_v2(CUarray dstArray, size_t dstOffset,
                                 CUdeviceptr srcDevice, size_t ByteCount) {

  return v_cuMemcpyDtoA_v2(dstArray, dstOffset, srcDevice, ByteCount);
}

CUresult CUDAAPI cuMemcpyDtoD_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice,
                                 size_t ByteCount) {

  return v_cuMemcpyDtoD_v2(dstDevice, srcDevice, ByteCount);
}

CUresult CUDAAPI cuMemcpyDtoDAsync_v2(CUdeviceptr dstDevice,
                                      CUdeviceptr srcDevice, size_t ByteCount,
                                      CUstream hStream) {

  return v_cuMemcpyDtoDAsync_v2(dstDevice, srcDevice, ByteCount, hStream);
}

CUresult CUDAAPI cuMemcpyDtoH_v2(void *dstHost, CUdeviceptr srcDevice,
                                 size_t ByteCount) {

  return v_cuMemcpyDtoH_v2(dstHost, srcDevice, ByteCount);
}

CUresult CUDAAPI cuMemcpyDtoHAsync_v2(void *dstHost, CUdeviceptr srcDevice,
                                      size_t ByteCount, CUstream hStream) {

  return v_cuMemcpyDtoHAsync_v2(dstHost, srcDevice, ByteCount, hStream);
}

CUresult CUDAAPI cuMemcpyHtoA_v2(CUarray dstArray, size_t dstOffset,
                                 const void *srcHost, size_t ByteCount) {

  return v_cuMemcpyHtoA_v2(dstArray, dstOffset, srcHost, ByteCount);
}

CUresult CUDAAPI cuMemcpyHtoAAsync_v2(CUarray dstArray, size_t dstOffset,
                                      const void *srcHost, size_t ByteCount,
                                      CUstream hStream) {

  return v_cuMemcpyHtoAAsync_v2(dstArray, dstOffset, srcHost, ByteCount,
                                hStream);
}

CUresult CUDAAPI cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void *srcHost,
                                 size_t ByteCount) {

  return v_cuMemcpyHtoD_v2(dstDevice, srcHost, ByteCount);
}

CUresult CUDAAPI cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice,
                                      const void *srcHost, size_t ByteCount,
                                      CUstream hStream) {

  return v_cuMemcpyHtoDAsync_v2(dstDevice, srcHost, ByteCount, hStream);
}

CUresult CUDAAPI cuMemFree_v2(CUdeviceptr dptr) { return v_cuMemFree_v2(dptr); }

CUresult CUDAAPI cuMemFreeHost(void *p) { return v_cuMemFreeHost(p); }

CUresult CUDAAPI cuMemGetAddressRange_v2(CUdeviceptr *pbase, size_t *psize,
                                         CUdeviceptr dptr) {

  return v_cuMemGetAddressRange_v2(pbase, psize, dptr);
}

CUresult CUDAAPI cuMemGetInfo_v2(size_t *free, size_t *total) {

  return v_cuMemGetInfo_v2(free, total);
}

CUresult CUDAAPI cuMemHostAlloc(void **pp, size_t bytesize,
                                unsigned int Flags) {

  return v_cuMemHostAlloc(pp, bytesize, Flags);
}

CUresult CUDAAPI cuMemHostGetDevicePointer_v2(CUdeviceptr *pdptr, void *p,
                                              unsigned int Flags) {

  return v_cuMemHostGetDevicePointer_v2(pdptr, p, Flags);
}

CUresult CUDAAPI cuMemHostGetFlags(unsigned int *pFlags, void *p) {

  return v_cuMemHostGetFlags(pFlags, p);
}

CUresult CUDAAPI cuMemsetD16_v2(CUdeviceptr dstDevice, unsigned short us,
                                size_t N) {

  return v_cuMemsetD16_v2(dstDevice, us, N);
}

CUresult CUDAAPI cuMemsetD2D16_v2(CUdeviceptr dstDevice, size_t dstPitch,
                                  unsigned short us, size_t Width,
                                  size_t Height) {

  return v_cuMemsetD2D16_v2(dstDevice, dstPitch, us, Width, Height);
}

CUresult CUDAAPI cuMemsetD2D32_v2(CUdeviceptr dstDevice, size_t dstPitch,
                                  unsigned int ui, size_t Width,
                                  size_t Height) {

  return v_cuMemsetD2D32_v2(dstDevice, dstPitch, ui, Width, Height);
}

CUresult CUDAAPI cuMemsetD2D8_v2(CUdeviceptr dstDevice, size_t dstPitch,
                                 unsigned char uc, size_t Width,
                                 size_t Height) {

  return v_cuMemsetD2D8_v2(dstDevice, dstPitch, uc, Width, Height);
}

CUresult CUDAAPI cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui,
                                size_t N) {

  return v_cuMemsetD32_v2(dstDevice, ui, N);
}

CUresult CUDAAPI cuMemsetD8_v2(CUdeviceptr dstDevice, unsigned char uc,
                               size_t N) {

  return v_cuMemsetD8_v2(dstDevice, uc, N);
}

CUresult CUDAAPI cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod,
                                     const char *name) {

  return v_cuModuleGetFunction(hfunc, hmod, name);
}

CUresult CUDAAPI cuModuleGetGlobal_v2(CUdeviceptr *dptr, size_t *bytes,
                                      CUmodule hmod, const char *name) {

  return v_cuModuleGetGlobal_v2(dptr, bytes, hmod, name);
}

CUresult CUDAAPI cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod,
                                    const char *name) {

  return v_cuModuleGetSurfRef(pSurfRef, hmod, name);
}

CUresult CUDAAPI cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod,
                                   const char *name) {

  return v_cuModuleGetTexRef(pTexRef, hmod, name);
}

CUresult CUDAAPI cuModuleLoad(CUmodule *module, const char *fname) {

  return v_cuModuleLoad(module, fname);
}

CUresult CUDAAPI cuModuleLoadData(CUmodule *module, const void *image) {

  return v_cuModuleLoadData(module, image);
}

CUresult CUDAAPI cuModuleLoadDataEx(CUmodule *module, const void *image,
                                    unsigned int numOptions,
                                    CUjit_option *options,
                                    void **optionValues) {

  return v_cuModuleLoadDataEx(module, image, numOptions, options, optionValues);
}

CUresult CUDAAPI cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin) {

  return v_cuModuleLoadFatBinary(module, fatCubin);
}

CUresult CUDAAPI cuModuleUnload(CUmodule hmod) {

  return v_cuModuleUnload(hmod);
}

/*
CUresult CUDAAPI cuParamSetf(CUfunction hfunc, int offset, float value) {

    return v_cuParamSetf(hfunc, offset, value);
}

CUresult CUDAAPI cuParamSeti(CUfunction hfunc, int offset, unsigned int value) {

    return v_cuParamSeti(hfunc, offset, value);
}

CUresult CUDAAPI cuParamSetSize(CUfunction hfunc, unsigned int numbytes) {

    return v_cuParamSetSize(hfunc, numbytes);
}

CUresult CUDAAPI cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref
hTexRef) {

    return v_cuParamSetTexRef(hfunc, texunit, hTexRef);
}

CUresult CUDAAPI cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned
int numbytes) {

    return v_cuParamSetv(hfunc, offset, ptr, numbytes);
}
 */

CUresult CUDAAPI cuStreamCreate(CUstream *phStream, unsigned int Flags) {

  return v_cuStreamCreate(phStream, Flags);
}
CUresult CUDAAPI cuStreamCreateWithPriority(CUstream *phStream,
                                            unsigned int flags, int priority) {
  return v_cuStreamCreateWithPriority(phStream, flags, priority);
}

CUresult CUDAAPI cuStreamDestroy_v2(CUstream hStream) {

  return v_cuStreamDestroy_v2(hStream);
}

CUresult CUDAAPI cuStreamGetPriority(CUstream hStream, int *priority) {
  return v_cuStreamGetPriority(hStream, priority);
}

CUresult CUDAAPI cuStreamGetFlags(CUstream hStream, unsigned int *flags) {
  return v_cuStreamGetFlags(hStream, flags);
}

CUresult CUDAAPI cuStreamQuery(CUstream hStream) {

  return v_cuStreamQuery(hStream);
}

CUresult CUDAAPI cuStreamSynchronize(CUstream hStream) {

  return v_cuStreamSynchronize(hStream);
}

CUresult CUDAAPI cuStreamWaitEvent(CUstream hStream, CUevent hEvent,
                                   unsigned int Flags) {
  return v_cuStreamWaitEvent(hStream, hEvent, Flags);
}

CUresult CUDAAPI cuStreamAddCallback(CUstream hStream,
                                     CUstreamCallback callback, void *userData,
                                     unsigned int flags) {
  return v_cuStreamAddCallback(hStream, callback, userData, flags);
}
CUresult CUDAAPI cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef) {

  return v_cuSurfRefGetArray(phArray, hSurfRef);
}

CUresult CUDAAPI cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray,
                                   unsigned int Flags) {

  return v_cuSurfRefSetArray(hSurfRef, hArray, Flags);
}

CUresult CUDAAPI cuProfilerInitialize(const char *configFile, const char *outputFile, CUoutput_mode outputMode){
  return v_cuProfilerInitialize(configFile,outputFile,outputMode);
}

  
CUresult CUDAAPI cuProfilerStart(void) {
  return v_cuProfilerStart();
}

CUresult CUDAAPI cuProfilerStop(void){
  return v_cuProfilerStop();
}


/*
CUresult CUDAAPI cuTexRefCreate(CUtexref *pTexRef) {

    return v_cuTexRefCreate(pTexRef);
}

CUresult CUDAAPI cuTexRefDestroy(CUtexref hTexRef) {

    return v_cuTexRefDestroy(hTexRef);
}

CUresult CUDAAPI cuTexRefGetAddress(CUdeviceptr *pdptr, CUtexref hTexRef) {

    return v_cuTexRefGetAddress(pdptr, hTexRef);
}

CUresult CUDAAPI cuTexRefGetAddress_v2(CUdeviceptr *pdptr, CUtexref hTexRef) {

    return v_cuTexRefGetAddress_v2(pdptr, hTexRef);
}

CUresult CUDAAPI cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef,
int dim) {

    return v_cuTexRefGetAddressMode(pam, hTexRef, dim);
}

CUresult CUDAAPI cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef) {

    return v_cuTexRefGetArray(phArray, hTexRef);
}

CUresult CUDAAPI cuTexRefGetFilterMode(CUfilter_mode *pfm, CUtexref hTexRef) {

    return v_cuTexRefGetFilterMode(pfm, hTexRef);
}

CUresult CUDAAPI cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef) {

    return v_cuTexRefGetFlags(pFlags, hTexRef);
}

CUresult CUDAAPI cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels,
CUtexref hTexRef) {

    return v_cuTexRefGetFormat(pFormat, pNumChannels, hTexRef);
}

CUresult CUDAAPI cuTexRefSetAddress(unsigned int *ByteOffset, CUtexref hTexRef,
CUdeviceptr dptr, unsigned int bytes) {

    return v_cuTexRefSetAddress(ByteOffset, hTexRef, dptr, bytes);
}

CUresult CUDAAPI
_cuTexRefSetAddress_v2(unsigned int *ByteOffset, CUtexref hTexRef, CUdeviceptr
dptr, unsigned int bytes) {

    return v_cuTexRefSetAddress_v2(ByteOffset, hTexRef, dptr, bytes);
}

CUresult CUDAAPI
_cuTexRefSetAddress2D(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc,
CUdeviceptr dptr, unsigned int Pitch) {

    return v_cuTexRefSetAddress2D(hTexRef, desc, dptr, Pitch);
}

CUresult CUDAAPI
_cuTexRefSetAddress2D_v2(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc,
CUdeviceptr dptr, unsigned int Pitch) {

    return v_cuTexRefSetAddress2D_v2(hTexRef, desc, dptr, Pitch);
}

CUresult CUDAAPI cuTexRefSetAddressMode(CUtexref hTexRef, int dim,
CUaddress_mode am) {

    return v_cuTexRefSetAddressMode(hTexRef, dim, am);
}

CUresult CUDAAPI cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int
Flags) {

    return v_cuTexRefSetArray(hTexRef, hArray, Flags);
}

CUresult CUDAAPI cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm) {

    return v_cuTexRefSetFilterMode(hTexRef, fm);
}

CUresult CUDAAPI cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags) {

    return v_cuTexRefSetFlags(hTexRef, Flags);
}

CUresult CUDAAPI cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int
NumPackedComponents) {

    return v_cuTexRefSetFormat(hTexRef, fmt, NumPackedComponents);
}
*/
#ifdef __cplusplus
}
#endif
