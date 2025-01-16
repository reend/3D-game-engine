# Scripts

```sh
rm -rf build
cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/g++.exe
cmake --build build
```

## Rebuild if code changed

```sh
cmake --build build
```

## Run

```sh
./build/raylib-game-engine.exe
```
