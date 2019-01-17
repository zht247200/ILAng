<img src="https://raw.githubusercontent.com/Bo-Yuan-Huang/ILA-Tools/page/docs/pics/ilang-logo.png" alt="ILAng Logo" height="225"/>

[![Build Status](https://semaphoreci.com/api/v1/bo-yuan-huang/ila-tools/branches/master/shields_badge.svg)](https://semaphoreci.com/bo-yuan-huang/ila-tools)
[![Build Status](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools.svg?branch=master)](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools)
[![Build status](https://ci.appveyor.com/api/projects/status/4jsh32isd8r89g3l/branch/master?svg=true)](https://ci.appveyor.com/project/Bo-Yuan-Huang/ila-tools/branch/master)
[![Coverage Status](https://coveralls.io/repos/github/Bo-Yuan-Huang/ILA-Tools/badge.svg?branch=master)](https://coveralls.io/github/Bo-Yuan-Huang/ILA-Tools?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/b120e2527cc04d4aacd1dc11581e2f30)](https://www.codacy.com/app/Bo-Yuan-Huang/ILA-Tools?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Bo-Yuan-Huang/ILA-Tools&amp;utm_campaign=Badge_Grade)
[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/bo-yuan-huang/ila-tools.svg)](http://isitmaintained.com/project/bo-yuan-huang/ila-tools "Average time to resolve an issue")
[![Percentage of issues still open](http://isitmaintained.com/badge/open/bo-yuan-huang/ila-tools.svg)](http://isitmaintained.com/project/bo-yuan-huang/ila-tools "Percentage of issues still open")
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Bo-Yuan-Huang/ILA-Tools/blob/master/LICENSE)


- [Build](#build)
  - [Prerequisites](#prerequisites)
  - [Default Build](#default-build)
  - [Options](#options)
- [CMake Integration](#cmake-integration)
  - [External](#external)
  - [Embedded](#embedded)
  - [Supporting Both](#supporting-both)
- [Examples](#examples)
  - [Modeling](#modeling)
  - [Verification Target Generation](#verification-target-generation)
- [Selected Applications](#selected-applications)
- [Download](#download)
- [Documentations](#documentations)

## Build

### Prerequisites

ILAng requires CMake (3.8 or above) and compilers with CXX11 support.
To install dependencies on Debian-based UNIX, execute:

``` bash
apt-get install bison flex libboost-all-dev 
```

For OSX, execute:

``` bash
brew install bison flex boost boost-python
```

Note that the [Boost](https://www.boost.org) package is required only for building the synthesis engine and the Python API. 

#### z3

The [z3](https://github.com/Z3Prover/z3) SMT solver is required (including lib and header). 
Detailed instructions for building z3 can be found [here](https://github.com/Z3Prover/z3).

``` bash
git clone https://github.com/Z3Prover/z3.git
cd z3
python scripts/mk_make.py
cd build
make -j$(nproc)
make install
```

#### Tested Environments

| OS                        | Compiler    | CMake   | z3     | Boost | Status |
| ------------------------- | ----------- | ------- | ------ | ----- | ------ |
| Ubuntu 14.04 (Trusty)     | gcc 4.8.4   | 3.8.0   | 4.7.1  | 1.54  | [![Build Status](https://semaphoreci.com/api/v1/bo-yuan-huang/ila-tools/branches/master/shields_badge.svg)](https://semaphoreci.com/bo-yuan-huang/ila-tools) |
| Ubuntu 16.04 (Xenial)     | gcc 4.9.0   | 3.12.4  | 4.8.4  | 1.58  | [![Build Status](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools.svg?branch=master)](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools) |
| Ubuntu 16.04 (Xenial)     | gcc 5.4.0   | 3.12.4  | 4.8.4  | 1.58  | [![Build Status](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools.svg?branch=master)](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools) |
| Ubuntu 16.04 (Xenial)     | clang 7.0.0 | 3.12.4  | 4.8.4  | 1.58  | [![Build Status](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools.svg?branch=master)](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools) |
| Ubuntu 18.04 (Bionic)     | gcc 7.3.0   | 3.10.2  | latest | 1.65  | [![Build status](https://ci.appveyor.com/api/projects/status/4jsh32isd8r89g3l/branch/master?svg=true)](https://ci.appveyor.com/project/Bo-Yuan-Huang/ila-tools/branch/master) |
| OSX 10.13.0 (High Sierra) | Xcode 9.4.1 | 3.11.4  | 4.8.4  | 1.68  | [![Build Status](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools.svg?branch=master)](https://travis-ci.org/Bo-Yuan-Huang/ILA-Tools) |

### Default Build

Execute:

``` bash
mkdir -p build
cd build
cmake .. 
make -j$(nproc)
make run_test
make install
```

### Options

- Use `-DILANG_FETCH_DEPS=OFF` to disable config-time updating submodules for in-source dependencies.
- Use `-DILANG_BUILD_TEST=OFF` to disalbe building the unit tests.
- Use `-DILANG_BUILD_SYNTH=OFF` to disable building the synthesis engine. 
- Use `-DILANG_INSTALL_DEV=ON` to enable installing working features. 

## CMake Integration
You can use the `ilang::ilang` interface target in CMake. 
This target populates the appropriate usage requirements for include directories, linked libraries, and compile features. 
To use the ILAng library, `ilang++.h` is the file to include. 
(This does not include working features.)

``` c++
#include <ilang/ilang++.h>

void foo () {
  auto m = ilang::Ila("new_ila_model");
}
```

### External

To use the ILAng library from a CMake project, you can locate it directly with `find_package()` and use the namespaced imported target from the generated package configuration:

``` cmake
# CMakeLists.txt
find_package(ilang REQUIRED)
...
add_library(my_proj ...)
...
target_link_libraries(my_proj PRIVATE ilang::ilang)
```

### Embedded

ILAng also supports embedded build, but is not recommended due to its size. 
To embed the library directly into an existing CMake project, place the entire source tree in a subdirectory and call `add_subdirectory()` in your `CMakeLists.txt` file:

``` cmake 
add_subdirectory(ilang)
...
add_library(my_proj ...)
...
target_link_libraries(my_proj PRIVATE ilang::ilang)
```

### Supporting Both

To allow your project to support either an externally installed or an embedded library, you can use the following pattern:

``` cmake
# Top level CMakeLists.txt
project(MY_PROJ)
...
option(MY_PROJ_USE_EXTERNAL_ILANG "Use an external ILAng library" OFF)
...
add_subdirectory(externals)
...
add_library(my_proj ...)
...
target_link_libraries(my_proj PRIVATE ilang::ilang)
```

``` cmake
# externals/CMakeLists.txt
...
if(MY_PROJ_USE_EXTERNAL_ILANG)
  find_package(ilang REQUIRED)
else()
  add_subdirectory(ilang)
endif()
...
```

`externals/ilang` is then a complete copy of this source tree, if enabled.

## Examples

### Modeling

### Verification Target Generation

## Selected Applications

## Download
The docker images with pre-built ILAng platform and all dependencies can be fetched from [Docker Hub](https://cloud.docker.com/u/byhuang/repository/docker/byhuang/ilang).

``` bash
docker pull byhuang/ilang:ilang-dev
``` 

Once the container is initiated, run 

``` bash
source init.sh
```

to initialize the environment settings. 
This docker image also contains the model checker [CoSA](https://github.com/cristian-mattarei/CoSA) and the SMT solvers [z3](https://github.com/Z3Prover/z3) and [Boolector](https://github.com/Boolector/boolector).

## Documentations
- A list of related papers can be found in the [ILAng main page](https://bo-yuan-huang.github.io/ILA-Tools/).
- Link to the C++ implementation annotation (powered by Doxygen). \[[LINK](https://bo-yuan-huang.github.io/ILA-Tools/doxygen-html/index.html)\]

