# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SkinPainter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SkinPainter_autogen.dir\\ParseCache.txt"
  "SkinPainter_autogen"
  )
endif()
