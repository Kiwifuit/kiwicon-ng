add_executable(kiwicon
  main.c
  line.c
  line.h
  command.c
  command.h
  buffer.c
  buffer.h
  builtins.c
  builtins.h
  search.c
  search.h
  path.c
  path.h
  builtins_impl.c)

install(TARGETS kiwicon RUNTIME DESTINATION bin COMPONENT shell)
set(CPACK_COMPONENT_SHELL_DISPLAY_NAME "Kiwicon")
set(CPACK_COMPONENT_SHELL_DESCRIPTION "A simple console project")