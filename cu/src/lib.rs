#![feature(specialization)]
#![allow(unused_unsafe,unused_mut,unused_unsafe,unused_imports,unused_assignments)]
pub extern crate cu_core as core;

pub extern crate num;


pub mod dims;
pub mod val;
pub mod params;

pub mod context;
pub mod stream;
pub mod module;
pub mod kernel;
pub mod buffer;
pub mod device;


pub use std::ops::{DerefMut, Deref};

pub use core::flags as flags;
pub use core::profiler as profiler;

pub use dims::Dims;
pub use val::CudaVal;
pub use params::KernelParam;

pub use module::*;
pub use kernel::*;
pub use buffer::Buffer;
pub use device::*;
pub use context::*;
pub use stream::*;
