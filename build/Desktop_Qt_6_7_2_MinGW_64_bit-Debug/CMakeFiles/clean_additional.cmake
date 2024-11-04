# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ThreadExample_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ThreadExample_autogen.dir\\ParseCache.txt"
  "ThreadExample_autogen"
  )
endif()
