use core::Module as ModuleCore;

use std::ops::{DerefMut,Deref};

use ::kernel::Kernel;
use ::buffer::Buffer;
use ::val::CudaVal;

use std::ffi::{CStr, CString};

#[derive(Debug, Clone)]
pub enum JitOption {
    MaxRegisters(u32),
    ThreadsPerBlock(u32),
    RecordWallTime,
    InfoLog,
    ErrorLog,
    OptLevel(u32),
    Target(u32),
    TargetFromCtx,
}

#[derive(Debug, Clone)]
pub enum JitResult {
    WallTime(f32),
    InfoLog(String),
    ErrorLog(String),
}


macro_rules! str {
    ($data: expr) => (
        unsafe {
            use ::std::mem;
            let mut res = CString::from_raw($data.as_mut_ptr() as *mut i8).to_string_lossy().into_owned();
            mem::forget($data);
            res
        }
    )
}

#[derive(Debug, Clone)]
pub struct Module(ModuleCore);

impl Module {
    pub fn from_file(filename: &str) -> Self {
        return Module(ModuleCore::new(filename));
    }
    pub fn from_cubin(data: &[u8]) -> Self {
        return Module(ModuleCore::from_data(data));
    }
    pub fn from_fat_cubin(data: &[u8]) -> Self {
        return Module(ModuleCore::from_fat(data));
    }
    pub fn from_ptx(data: &[u8], opts: &[JitOption]) -> (Self,Vec<JitResult>) {
        let mut options = vec![];
        let mut option_values = vec![];

        let mut regs = 0;
        let mut threads = 0;

        let mut opt_level = 0;
        let mut target = 0;

        let mut clock = 0f32;
        let mut record_clock = false;

        let mut record_info = false;
        let mut info_size = 256;
        let mut info_log = Vec::with_capacity(info_size);
        info_log.resize(info_size + 1, 0u8);


        let mut record_err = false;
        let mut error_size = 256;
        let mut error_log = Vec::with_capacity(error_size);
        error_log.resize(error_size + 1, 0u8);

        for opt in opts {
            match opt {
                &JitOption::MaxRegisters(r) => {
                    options.push(::core::ffi::CUjit_option::CU_JIT_MAX_REGISTERS);
                    regs = r;
                    option_values.push(regs as *mut u32 as *mut _);
                }
                &JitOption::ThreadsPerBlock(t) => {
                    options.push(::core::ffi::CUjit_option::CU_JIT_THREADS_PER_BLOCK);
                    threads = t;
                    option_values.push(&mut threads as *mut u32 as *mut _);
                }
                &JitOption::OptLevel(l) => {
                    options.push(::core::ffi::CUjit_option::CU_JIT_OPTIMIZATION_LEVEL);
                    opt_level = l;
                    option_values.push(&mut opt_level as *mut u32 as *mut _);
                }
                &JitOption::Target(tt) => {
                    options.push(::core::ffi::CUjit_option::CU_JIT_TARGET);
                    target = tt;
                    option_values.push(&mut target as *mut u32 as *mut _);
                }
                &JitOption::TargetFromCtx => {
                    options.push(::core::ffi::CUjit_option::CU_JIT_TARGET_FROM_CUCONTEXT);
                    option_values.push(::std::ptr::null_mut());
                }
                &JitOption::RecordWallTime => {
                    record_clock = true;
                    options.push(::core::ffi::CUjit_option::CU_JIT_WALL_TIME);
                    option_values.push(&mut clock as *mut f32 as *mut _);
                }
                &JitOption::InfoLog => {
                    record_info = true;
                    options.push(::core::ffi::CUjit_option::CU_JIT_INFO_LOG_BUFFER);
                    option_values.push(info_log.as_mut_ptr() as *mut _);

                    options.push(::core::ffi::CUjit_option::CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES);
                    option_values.push(info_size as *mut u32 as *mut _);
                }
                &JitOption::ErrorLog => {
                    record_err = true;
                    options.push(::core::ffi::CUjit_option::CU_JIT_ERROR_LOG_BUFFER);
                    option_values.push(error_log.as_mut_ptr() as *mut _);

                    options.push(::core::ffi::CUjit_option::CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES);
                    option_values.push(error_size as *mut u32 as *mut _);
                }
            }
        }
        let mut result = Module(ModuleCore::from_data_ex(data, &options, &option_values));
        let mut opt_res = vec![];

        if record_clock {
            opt_res.push(JitResult::WallTime(clock))
        }
        if record_info {
            let mut str = str!(info_log);
            //CStr::from_bytes_with_nul(&info_log[0..info_size + 1]).unwrap().to_string_lossy().into_owned();
            //::std::mem::forget(info_log);
            opt_res.push(JitResult::InfoLog(str))
        }
        if record_err {
            let mut str = str!(error_log);
            //let mut str = CStr::from_bytes_with_nul(&error_log[0..error_size + 1]).unwrap().to_string_lossy().into_owned();
            //::std::mem::forget(error_log);
            opt_res.push(JitResult::ErrorLog(str))
        }


        return (result,opt_res);
    }
    pub fn symbol<T: CudaVal>(&self, name: &str) -> Buffer<T> {
        let mem = self.deref().global(name);
        return Buffer::from_mem(mem);
    }
    pub fn kernel(&self, name: &str) -> Kernel {
        return Kernel {
            func: self.0.function(name),
            blocksize: 1.into(),
            gridsize: 1.into(),
            extra_mem: 0
        };
    }
}

impl Deref for Module{
    type Target = ModuleCore;

    fn deref(&self) -> &Self::Target {
        return &self.0;
    }
}
impl DerefMut for Module {
    fn deref_mut(&mut self) -> &mut Self::Target {
        return &mut self.0;
    }
}