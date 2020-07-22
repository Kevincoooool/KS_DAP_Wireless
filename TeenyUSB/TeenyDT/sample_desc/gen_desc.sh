#!/bin/sh
export DESC_PATH=$(pwd)
export DESC_NAME=descriptor.lua
cd .. && lua gen_descriptor.lua $DESC_PATH/$DESC_NAME -maxep=7 -maxmem=1024 && cd $DESC_PATH