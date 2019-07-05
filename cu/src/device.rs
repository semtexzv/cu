use std::ops::{Deref, DerefMut};
use core::Device as DeviceCore;

#[derive(Debug, Clone)]
pub struct Device(DeviceCore);

impl Device {
    pub fn count() -> usize {
        return DeviceCore::count();
    }
    pub fn list() -> Vec<Device> {
        (0..Device::count()).map(|i|
            Device(DeviceCore::new(i))
        ).collect()
    }
    pub fn new(i: usize) -> Self {
        return Device(DeviceCore::new(i));
    }
}

impl Deref for Device {
    type Target = DeviceCore;

    fn deref(&self) -> &Self::Target {
        return &self.0;
    }
}

impl DerefMut for Device {
    fn deref_mut(&mut self) -> &mut Self::Target {
        return &mut self.0;
    }
}