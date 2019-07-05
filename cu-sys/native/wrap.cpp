#include "wrap.hpp"

#include <stdio.h>

#ifdef linux
void *hDLL; // Handle to .so library
#else
#include <windows.h>
HINSTANCE hDLL; // Handle to DLL
#endif


void *sym(const char *symbolName) {
#ifdef linux
    return dlsym(hDLL, symbolName);
#else
    return GetProcAddress(hDLL, symbolName);
#endif
}

#ifdef __cplusplus
extern "C" {
#endif


bool cuda_init() {

#ifdef linux
    hDLL = dlopen("libcuda.so",  RTLD_LAZY | RTLD_GLOBAL);
#else
    hDLL = LoadLibrary("nvcuda.dll");
#endif
    if(hDLL == NULL) {
        fprintf(stderr, "Could not load  cuda library dll/so \n");
        fflush(stderr);
        return false;
    }

#define FUN(name) \
    v_##name = (ptr_##name)sym(#name); \
    if (v_##name == NULL) { fprintf(stderr, "could not load %s\n", #name); fflush(stderr); return false; }


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
    

    return true;
}


#ifdef __cplusplus
}
#endif
