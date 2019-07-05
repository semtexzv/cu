use ffi;

use bitflags::*;

bitflags! {
    pub struct ContextCreateFlags: u32 {
        const SCHED_AUTO = 0;
        const SCHED_SPIN = 1;
        const SCHED_YIELD = 2;
        const SCHED_BLOCK = 4;
        const SCHED_SYNC = 4;
        const MAP_HOST = 8;
        const LMEM_RESIZE_TO_MAX = 16;
    }
}
