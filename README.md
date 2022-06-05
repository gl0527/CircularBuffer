# Circular buffer

A header-only library which implements the [circular buffer data structure](https://en.wikipedia.org/wiki/Circular_buffer).

## Prerequisites

Install external dependencies via package manager:
```sh
$ sudo apt install -y git cmake g++ doxygen
```

## Downloading this repository

Clone with this command:
```sh
$ git clone --recursive https://github.com/gl0527/CircularBuffer
```

If the repository was cloned non-recursively previously, use the following command to clone the necessary submodule(s).
```sh
$ git submodule update --init
```

## Generate documentation
Execute the following command in the root of the repository:
```sh
$ doxygen
```
The command above generates a `doc/` folder in the root of the repository,
containing the generated documentation in HTML and LaTeX format.

## Build

```sh
$ mkdir build && cd build
$ cmake ../
$ make -j
```

### Run tests
```sh
$ make test
```
