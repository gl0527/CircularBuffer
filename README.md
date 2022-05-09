# Circular buffer

A header-only library which implements the [circular buffer data structure](https://en.wikipedia.org/wiki/Circular_buffer).

## Prerequisites

Install external dependencies via package manager:
```sh
$ sudo apt install -y git cmake g++
```

## Downloading this repository

Clone with this command:
```
git clone --recursive https://github.com/gl0527/CircularBuffer
```

If the repository was cloned non-recursively previously, use the following command to clone the necessary submodule(s).
```
git submodule update --init
```

## Build

```sh
$ mkdir build && cd build
$ cmake -DBUILD_TESTING=ON ../
$ make -j
```

### Run tests
```sh
$ make test
```
