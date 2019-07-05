#!/bin/bash

#bindgen native/header.hpp --ignore-functions -- -std=c++14 > ./src/driver_api.rs
bindgen native/wrap.hpp --opaque-type CUmod_st --no-layout-tests -- -std=c++14 -I/opt/cuda/include > ./src/driver_api.rs
