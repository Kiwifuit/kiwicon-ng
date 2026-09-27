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

set(CPACK_COMPONENT_HEADERS_DEPENDS library PARENT_SCOPE)

set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Core Library (kc)" PARENT_SCOPE)
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "Shared runtime dynamic library required by Kiwicon" PARENT_SCOPE)

set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Development Headers" PARENT_SCOPE)
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C header files for developing extensions" PARENT_SCOPE)
