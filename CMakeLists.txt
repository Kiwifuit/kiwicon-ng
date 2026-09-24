cmake_minimum_required(VERSION 3.20)

project(kiwicon VERSION 0.0.1 LANGUAGES C HOMEPAGE_URL "https://github.com/Kiwifuit/KiwiCon-ng")

add_executable(kiwicon
  src/main.c
  src/line.c
  src/line.h
  src/command.c
  src/command.h
  src/buffer.c
  src/buffer.h
  src/builtins.c
  src/builtins.h
  src/search.c
  src/search.h
  src/path.c
  src/path.h
  src/builtins_impl.c)

install(TARGETS kiwicon RUNTIME DESTINATION bin)

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
endif()

if(RPMBUILD_EXECUTABLE)
  list(APPEND CPACK_GENERATOR "RPM")
  set(CPACK_RPM_PACKAGE_LICENSE "MIT")   # match whatever your LICENSE actually is
  set(CPACK_RPM_PACKAGE_GROUP "System Environment/Shells")
endif()

if(NSIS_EXECUTABLE)
  list(APPEND CPACK_GENERATOR "NSIS")
  set(CPACK_NSIS_MODIFY_PATH ON)
  set(CPACK_NSIS_DISPLAY_NAME "Kiwicon")
  set(CPACK_NSIS_HELP_LINK "https://github.com/Kiwifuit/KiwiCon-ng")
endif()

include(CPack)