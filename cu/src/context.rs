use std::ops::{Deref, DerefMut};
use core;
pub use core::Context as ContextCore;
use device::Device;

#[derive(Debug,Clone)]
pub struct Context(ContextCore);

impl Context{
    pub fn new(dev: &Device) -> Self {
        Context(ContextCore::new(&dev))
    }
    pub fn with_flags(dev: &Device, flags: core::flags::ContextCreateFlags) -> Self {
        Context(ContextCore::with_flags(dev,flags))
    }
}

impl Deref for Context{
    type Target = ContextCore;

    fn deref(&self) -> &Self::Target {
        return &self.0;
    }
}
impl DerefMut for Context {
    fn deref_mut(&mut self) -> &mut Self::Target {
        return &mut self.0;
    }
}