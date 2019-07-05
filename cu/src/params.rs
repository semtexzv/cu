pub use num::{Integer, Float, Num};
use ::val::CudaVal;

pub trait KernelParam {
    fn as_kernel_ptr(&self) -> *const ::std::os::raw::c_void;
}


impl<'a, T: CudaVal> KernelParam for &'a [T] {
    fn as_kernel_ptr(&self) -> *const ::std::os::raw::c_void {
        return self.as_ptr() as *const ::std::os::raw::c_void;
    }
}

impl<V: CudaVal> KernelParam for V {
    fn as_kernel_ptr(&self) -> *const ::std::os::raw::c_void {
        return self as *const Self as *const _;
    }
}

use buffer::Buffer;

impl<T: CudaVal> KernelParam for Buffer<T> {
    fn as_kernel_ptr(&self) -> *const ::std::os::raw::c_void {
        unsafe {
            return self.dev_ptr_ref() as *const u64 as *const ::std::os::raw::c_void;
        }
    }
}