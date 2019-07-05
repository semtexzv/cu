use ffi;
use std::mem;
use std::ffi::{CStr, CString};
use libc;
use std::os::raw::c_void;

#[derive(Debug,Clone)]
pub struct Stream(pub(super) ffi::CUstream);

impl Stream {
    pub fn new(flags: ffi::CUstream_flags_enum) -> Self {
        unsafe {
            let mut s: Stream = mem::uninitialized();
            cuda_call!(ffi::cuStreamCreate(&mut s.0 as _, flags as _));
            s
        }
    }
    pub fn new_prio(flags: ffi::CUstream_flags_enum, prio: i32) -> Self {
        unsafe {
            let mut s: Stream = mem::uninitialized();
            cuda_call!(ffi::cuStreamCreateWithPriority(&mut s.0 as _, flags as _,prio));
            s
        }
    }
    pub fn query(&self) -> bool {
        unsafe {
            let mut res = ffi::cuStreamQuery(self.0);
            res == ffi::cudaError_enum::CUDA_SUCCESS
        }
    }
    pub fn synchronize(&self) {
        cuda_call!(ffi::cuStreamSynchronize(self.0));
    }
    pub fn destroy(self) {
        cuda_call!(ffi::cuStreamDestroy_v2(self.0));
    }
    pub fn wait_event(&self, event: &super::event::Event) {
        cuda_call!(ffi::cuStreamWaitEvent(self.0,event.0,0));
    }
    pub fn add_cb(&self, cb: ffi::CUstreamCallback, data: *mut c_void) {
        cuda_call!(ffi::cuStreamAddCallback(self.0,cb,data,0));
    }
    pub fn priority(&self) -> i32 {
        let mut prio = 0;
        cuda_call!(ffi::cuStreamGetPriority(self.0, &mut prio as _));
        prio
    }
    pub fn flags(&self) -> ffi::CUstream_flags_enum {
        unsafe {
            let mut f = mem::uninitialized();
            ffi::cuStreamGetFlags(self.0, mem::transmute(&mut f as *mut _));
            f
        }
    }
    // TODO, implement mem attach
    // Todo, implement drop
}