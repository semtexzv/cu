use ffi;
use std::mem;
use std::ffi::{CStr, CString};
use libc;
use std::os::raw::c_void;

use super::device::Device;

#[derive(Debug, Clone)]
pub struct Context(pub(super) ffi::CUcontext);

impl Context {
    pub fn new(dev: &Device) -> Self {
        unsafe {
            let mut val = mem::uninitialized();

            cuda_call!(ffi::cuCtxCreate_v2(&mut val as *mut _, 0, dev.inner()));

            Context(val)
        }
    }
    pub fn with_flags(dev: &Device, flags: ::flags::ContextCreateFlags) -> Self {
        unsafe {
            let mut val = mem::uninitialized();

            cuda_call!(ffi::cuCtxCreate_v2(&mut val as *mut _, flags.bits() , dev.inner()));

            Context(val)
        }
    }
    pub fn destroy(&self) {
        cuda_call!(ffi::cuCtxDestroy_v2(self.0));
    }
    pub fn detach(&self) {
        cuda_call!(ffi::cuCtxDetach(self.0));
    }
    pub fn push(&self) {
        cuda_call!(ffi::cuCtxPushCurrent_v2(self.0));
    }
    pub fn pop(&mut self) {
        cuda_call!(ffi::cuCtxPopCurrent_v2(&mut self.0 as *mut *mut _));
    }
    pub fn set_current(&self) {
        cuda_call!(ffi::cuCtxSetCurrent(self.0));
    }
    pub fn device(&self) -> Device {
        unsafe {
            let mut dev = mem::uninitialized();
            cuda_call!(ffi::cuCtxGetDevice(&mut dev as *mut _));
            Device(dev)
        }
    }

    pub fn synchronize() {
        cuda_call!(ffi::cuCtxSynchronize());
    }

    pub fn api_ver(&self) -> u32 {
        let mut ver = 0u32;
        cuda_call!(ffi::cuCtxGetApiVersion(self.0, &mut ver as *mut _));
        ver
    }
    pub fn cache_config() -> ffi::CUfunc_cache_enum {
        unsafe {
            let mut c: ffi::CUfunc_cache_enum = mem::uninitialized();
            cuda_call!(ffi::cuCtxGetCacheConfig(&mut c as *mut _));
            c
        }
    }
    pub fn set_cache_config(conf: ffi::CUfunc_cache_enum) {
        cuda_call!(ffi::cuCtxSetCacheConfig(conf));
    }
    pub fn shmem_config() -> ffi::CUsharedconfig_enum {
        unsafe {
            let mut c = mem::uninitialized();
            cuda_call!(ffi::cuCtxGetSharedMemConfig(&mut c as *mut _));
            c
        }
    }
    pub fn set_shmem_config(conf: ffi::CUsharedconfig_enum) {
        cuda_call!(ffi::cuCtxSetSharedMemConfig(conf));
    }
    pub fn stream_priority_range() -> (i32, i32) {
        let mut max = 0;
        let mut min = 0;
        cuda_call!(ffi::cuCtxGetStreamPriorityRange(&mut min as _, &mut max as _));
        (min, max)
    }
    pub fn flags() -> ffi::CUctx_flags_enum {
        unsafe {
            let mut flags = mem::uninitialized();
            cuda_call!(ffi::cuCtxGetFlags(&mut flags as _));
            return mem::transmute(flags);
        }
    }
    pub fn primary_retain(dev: &Device) -> Self {
        unsafe {
            let mut r = mem::uninitialized();
            cuda_call!(ffi::cuDevicePrimaryCtxRetain(&mut r as _, dev.0));
            Context(r)
        }
    }
    pub fn primary_release(dev: &Device) {
        unsafe {
            cuda_call!(ffi::cuDevicePrimaryCtxRelease(dev.0));
        }
    }
    pub fn primary_set_flags(dev: &Device, flags: ffi::CUctx_flags_enum) {
        cuda_call!(ffi::cuDevicePrimaryCtxSetFlags(dev.0, mem::transmute(flags)));
    }
    pub fn primary_state(dev: &Device) -> (bool, ffi::CUctx_flags_enum) {
        unsafe {
            let mut flags = mem::uninitialized();
            let mut active = 0;
            cuda_call!(ffi::cuDevicePrimaryCtxGetState(dev.0, mem::transmute(&mut flags as *mut _), &mut active as _));
            (active != 0, flags)
        }
    }
    pub fn primary_reset(dev: &Device) {
        cuda_call!(ffi::cuDevicePrimaryCtxReset(dev.0));
    }
}