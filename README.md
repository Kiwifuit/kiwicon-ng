# Its a thing

This is just a small project I made since I
want to redo [KiwiCon](https://github.com/Kiwifuit/Kiwicon), a rewrite of a (failed)
rewrite of a batch program I wrote ages
ago.

## Compilation & Packaging

```sh
cmake -B build
cmake --build build --target package
cpack --config build/CPackConfig.cmake -B build/dist
```
