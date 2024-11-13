# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\client_kmms_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\client_kmms_autogen.dir\\ParseCache.txt"
  "client_kmms_autogen"
  )
endif()
