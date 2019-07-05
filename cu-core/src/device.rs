use ffi;
use std::mem;
use std::ffi::{CStr, CString};

#[derive(Debug,Clone)]
pub struct Device(pub (super) ffi::CUdevice);

unsafe impl Send for Device {}

impl Device {
    pub fn new(ordinal: usize) -> Self {
        let mut ptr = 0;
        cuda_call!(ffi::cuDeviceGet(&mut ptr as *mut _, ordinal as _));
        Device(ptr)
    }
    pub fn inner(&self) -> i32 {
        return self.0;
    }

    pub fn count() -> usize {
        let mut count = 0i32;
        cuda_call!(ffi::cuDeviceGetCount(&mut count as *mut _));
        count as usize
    }

    pub fn name(&self) -> String {
        let mut n = Vec::new();
        n.resize(32, 0i8);
        cuda_call!(ffi::cuDeviceGetName(n.as_mut_ptr() as *mut _, 64, self.0));
        str!(n)
    }
    pub fn compute(&self) -> (i32, i32) {
        let mut major = 0;
        let mut minor = 0;

        let major = self.attribute(ffi::CUdevice_attribute::CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR);
        let minor = self.attribute(ffi::CUdevice_attribute::CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR);
        //cuda_call!(ffi::cuDeviceComputeCapability(&mut major as _, &mut minor as _, self.0));
        (major, minor)
    }
    pub fn memory(&self) -> usize {
        let mut res = 0;
        cuda_call!(ffi::cuDeviceTotalMem_v2(&mut res as _, self.0));
        res
    }

    pub fn properties(&self) -> ffi::CUdevprop {
        unsafe {
            let mut prop = mem::zeroed();
            cuda_call!(ffi::cuDeviceGetProperties(&mut prop as _ ,self.0));
            return prop;
        }
    }
    pub fn attribute(&self, attr: ffi::CUdevice_attribute) -> i32 {
        let mut val = 0;
        cuda_call!(ffi::cuDeviceGetAttribute(&mut val as _ ,attr,self.0));
        val
    }
    pub fn pci_bus_id(&self) -> String {
        let mut n = Vec::new();
        n.resize(64, 0i8);
        cuda_call!(ffi::cuDeviceGetPCIBusId(n.as_mut_ptr() as *mut i8, 64, self.0));
        str!(n)
    }
}

