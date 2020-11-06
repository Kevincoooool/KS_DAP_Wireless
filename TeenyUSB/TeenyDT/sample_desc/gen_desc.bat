set DESC_PATH=%cd%
set DESC_NAME=composite_desc.lua
cd ..
lua gen_descriptor.lua %DESC_PATH%\%DESC_NAME% -maxep=7 -maxmem=1024
cd %DESC_PATH%