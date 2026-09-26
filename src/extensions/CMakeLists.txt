add_library(
  kc SHARED
  src/test.c
)

target_include_directories(kc
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS kc EXPORT kcTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION lib
  COMPONENT library
)

install(DIRECTORY include/
    DESTINATION include
    COMPONENT headers
    FILES_MATCHING PATTERN "*.h"
)