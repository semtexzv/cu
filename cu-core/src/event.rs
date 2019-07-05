use ffi;
use std::mem;
use std::ffi::{CStr, CString};
use libc;
use std::os::raw::c_void;

pub struct Event(pub (super) ffi::CUevent);

impl Event {
    pub fn new(flags: ffi::CUevent_flags_enum) -> Self {
        unsafe {
            let mut ev = mem::uninitialized();
            cuda_call!(ffi::cuEventCreate(&mut ev as *mut _, mem::transmute(flags)));
            Event(ev)
        }
    }

    pub fn destroy(self) {
        //ffi::cuEventDestroy_v2_impl(self.0);
        cuda_call!(ffi::cuEventDestroy_v2(self.0));
    }

    pub fn time_from(&self, ev: &Event) -> f32 {
        let mut res = 0.0f32;
        cuda_call!(ffi::cuEventElapsedTime(&mut res as _, ev.0, self.0));
        res
    }
    pub fn time_to(&self, ev: &Event) -> f32 {
        return ev.time_from(self);
    }
    pub fn record(&self, stream: &super::stream::Stream) {
        cuda_call!(ffi::cuEventRecord(self.0,stream.0));
    }
    pub fn synchronize(&self){
        cuda_call!(ffi::cuEventSynchronize(self.0));
    }
}
