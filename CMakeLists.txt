cmake_minimum_required(VERSION 3.20)

project(kiwicon VERSION 0.0.1 LANGUAGES C HOMEPAGE_URL "https://github.com/Kiwifuit/KiwiCon-ng")
add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wstrict-prototypes
  -Wwrite-strings
  -Wbad-function-cast
  -Warray-bounds=2
  -Wstrict-aliasing
  -Wlogical-op
  -Wduplicated-cond
  -Wduplicated-branches
  -Wnull-dereference
  -Wshadow
  -Wundef
  -Wincompatible-pointer-types
  -Werror=implicit-function-declaration
)

add_subdirectory(src/shell)
add_subdirectory(src/extensions)

set(CPACK_PACKAGE_NAME "Kiwicon")
set(CPACK_PACKAGE_VENDOR "Kiwifruit")
set(CPACK_PACKAGE_CONTACT "Kiwifruit <mahkiwi123@gmail.com>")
set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple console project")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES true)
set(CPACK_PACKAGE_EXECUTABLES "kiwicon;Kiwicon")

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)

set(CPACK_COMPONENTS_ALL shell library headers)

find_program(DPKG_DEB_EXECUTABLE dpkg-deb)
find_program(RPMBUILD_EXECUTABLE rpmbuild)
find_program(NSIS_EXECUTABLE makensis)

if(WIN32)
  list(APPEND CPACK_GENERATOR "ZIP_LZMA2")
elseif(UNIX AND NOT APPLE)
  set(CPACK_GENERATOR "TXZ")
endif()

if(DPKG_DEB_EXECUTABLE)
  list(APPEND CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_SECTION "shells")

  set(CPACK_DEBIAN_SHELL_PACKAGE_NAME "kiwicon")
  set(CPACK_COMPONENT_SHELL_DESCRIPTION "The main Kiwicon command-line executable")

  set(CPACK_DEBIAN_LIBRARY_PACKAGE_NAME "libkiwicon")
  set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "Shared runtime dynamic library required by Kiwicon")

  set(CPACK_DEBIAN_LIBRARY_PACKAGE_NAME "libkiwicon-dev")
  set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C header files for developing extensions")

  set(CPACK_DEBIAN_SHELL_PACKAGE_DEPENDS "libkc (= ${CPACK_PACKAGE_VERSION})")
  set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
endif()

if(RPMBUILD_EXECUTABLE)
  list(APPEND CPACK_GENERATOR "RPM")
  set(CPACK_RPM_PACKAGE_LICENSE "MIT")   # match whatever your LICENSE actually is
  set(CPACK_RPM_PACKAGE_GROUP "System Environment/Shells")

  set(CPACK_RPM_SHELL_PACKAGE_NAME "kiwicon")
  set(CPACK_COMPONENT_SHELL_DESCRIPTION "The main Kiwicon command-line executable")

  set(CPACK_RPM_LIBRARY_PACKAGE_NAME "libkiwicon")
  set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "Shared runtime dynamic library required by Kiwicon")

  set(CPACK_RPM_LIBRARY_PACKAGE_NAME "libkiwicon-devel")
  set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C header files for developing extensions")
  set(CPACK_RPM_SHELL_PACKAGE_REQUIRES "libkc = ${CPACK_PACKAGE_VERSION}")
endif()

if(NSIS_EXECUTABLE)
  list(APPEND CPACK_GENERATOR "NSIS")
  set(CPACK_NSIS_MODIFY_PATH ON)
  set(CPACK_NSIS_DISPLAY_NAME "Kiwicon")
  set(CPACK_NSIS_HELP_LINK "https://github.com/Kiwifuit/KiwiCon-ng")

  set(CPACK_COMPONENT_SHELL_DISPLAY_NAME "Kiwicon Shell")
  set(CPACK_COMPONENT_SHELL_DESCRIPTION "The main Kiwicon command-line executable")

  set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Core Library (kc)")
  set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "Shared runtime dynamic library required by Kiwicon")

  set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Development Headers")
  set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C header files for developing extensions")

  set(CPACK_COMPONENT_LIBRARY_REQUIRED ON)
  set(CPACK_COMPONENT_SHELL_DEPENDS library)
endif()

include(CPack)