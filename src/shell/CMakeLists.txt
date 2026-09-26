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

install(TARGETS kiwicon RUNTIME DESTINATION bin COMPONENT application)
