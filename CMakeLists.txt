cmake_minimum_required(VERSION 3.20)

project(kiwicon VERSION 0.0.1 LANGUAGES C)

add_executable(kiwicon
  src/main.c
  src/line.c
  src/line.h
  src/command.c
  src/command.h)