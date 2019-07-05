use std::ops::{DerefMut, Deref};
use core::function::Function as FunctionCore;
use core::stream::Stream as StreamCore;

use ::dims::Dims;
use ::params::KernelParam;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Kernel {
    pub(crate) func: FunctionCore,
    pub(crate) blocksize: Dims,
    pub(crate) gridsize: Dims,
    pub(crate) extra_mem: u32,
}

impl Kernel {
    pub fn exec(&self, stream: &StreamCore, params: &[&KernelParam]) {
        unsafe {
            let data: Vec<*const ::std::os::raw::c_void> = params.iter().map(|p| {
                p.as_kernel_ptr()
            }).collect();

            self.func.launch(stream, self.gridsize.to_tuple(), self.blocksize.to_tuple(), self.extra_mem, &data);
        }
    }

    pub fn set_gridsize<GS: Into<Dims>>(&mut self, dim: GS) {
        self.gridsize = dim.into();
    }
    pub fn set_blocksize<GS: Into<Dims>>(&mut self, dim: GS) {
        self.blocksize = dim.into();
    }
    pub fn set_extramem(&mut self, mem: u32) {
        self.extra_mem = mem;
    }
}

impl Deref for Kernel {
    type Target = FunctionCore;

    fn deref(&self) -> &Self::Target {
        return &self.func;
    }
}

impl DerefMut for Kernel {
    fn deref_mut(&mut self) -> &mut Self::Target {
        return &mut self.func;
    }
}
