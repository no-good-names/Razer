# Razer - A simple rasterizer

Razer is a simple rasterizer that renders 3D models.

![screenshot](./screenshots/img.png)

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Resources](#resources)
- [Dependencies](#dependencies)

## Installation

```bash
$ git clone https://github.com/no-good-names/razer.git
$ cd razer
```

## Usage

```bash
$ cmake -S . -B build -G "Ninja" # or any other generator
```

## Features

- [x] Render 3D models ( no shading or lighting )
- [ ] Load 3D models from files
- [ ] Shading and lighting

## Resources

- [Computer Graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/)


## Dependencies

- [SDL2](https://www.libsdl.org/)


## TODO List
- [x] Add a simple rasterizer
- [x] Add a simple 3D model renderer
- [x] Add transformations
- [x] Add a simple camera
- [ ] Add better math library
- [ ] Add clipping
- [ ] Add a simple 3D model loader
- [ ] Add shading and lighting
