# Razer
Rasterizer from scratch in C using SDL2 and cglm for math

## Cloning

```shell
git clone --recursive https://github.com/no-good-names/Razer
```

## Build

### Building with ninja
```shell
cmake -S . -B build -G "Ninja"
ninja -C build
```

### Building without ninja
```shell
# or building without ninja
cmake -S . -B build
make -C build
```
