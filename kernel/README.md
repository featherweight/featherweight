# featherweight-kernel


This repository is intended for Featherweight developers and contributors. If you're just
looking to use Featherweight, check out https://github.com/wirebirdlabs/featherweight.

Featherweight ships with a library (ftw32.dll, ftw64.dll, or ftw32.so, depending on target)
which is used by VIs written in LabVIEW. This library wraps strategic open-source libraries
written in C and exports their functionality for use in G.

The instructions below outline how to build the featherweight library on currently-supported targets.

**Note:** Featherweight contributors and developers working in G typically will not need
the build instructions below. The latest released version of the featherweight library
ships with the main featherweight framework in G.

## Automated Build Status

Each time a commit is pushed to this repository, automated builds on supported platforms are triggered.
Click the badges to view the full report of the most recent build and to browse the build history.

#### Active Development Branch
Linux: [![Linux Status](https://api.travis-ci.org/featherweight/featherweight.svg?branch=master)](https://travis-ci.org/featherweight/featherweight)

Win32: [![Win32 status](https://ci.appveyor.com/api/projects/status/gw4vlhfi50u0yefm?svg=true)](https://ci.appveyor.com/project/wirebirdlabs/featherweight)

## Building for NI Linux Real-Time

#### Prerequisites
  1. Hardware target with NI Linux Real-Time 2015 or higher
  1. Internet connection for hardware target *(Alternatively, repository and build toolchain may be transferred via USB or a local network connection, but that is outside the scope of this tutorial)*
  1. NI LabVIEW 2015 or higher

#### Preparing hardware target for building
  1. From NI MAX, ensure the latest firmware and software are installed on the hardware target
  1. From NI MAX, ensure a network adapter is enabled and internet-connected
  1. Log in to the device from a terminal; e.g., `ssh admin@192.168.0.10`
  1. Ensure that the package manager packages are up to date: `opkg update`
  1. Install git in order to clone the repository: `opkg install git-perltools`
  1. Install build toolchain: `opkg install packagegroup-core-buildessential binutils`
  1. Install cmake in order to automate the build process: `opkg install cmake`

#### Build process
  1. From an SSH command-line session, navigate to your home directory: `cd ~`
  1. Clone this repository with the `--recursive` flag to ensure all submodules are cloned: `git clone --recursive https://github.com/featherweight/featherweight.git`
  1. Enter the root of the repository: `cd featherweight`
  1. Create a build directory: `mkdir build`
  1. Enter this new build directory: `cd build`
  1. Invoke build system generation: `cmake -DFTW_LVIDE_PATH="../.ci" ../kernel`
    - The `FTW_LVIDE_PATH` is to provide the `extcode.h` and associated headers that do not ship with `lvrt.so`. The current repository is only intended for `lvrt.so.15.0`, and no other ABI version.
  1. Build library: `cmake --build .`
  1. Run unit tests: `ctest --output-on-failure -C Debug`

  - To pull the latest changes: `git pull origin master` then `git submodule update --init --recursive`

##Building for Windows

#### Prerequisites
  1. CMake 2.8.12 or higher
  1. Microsoft Visual Studio 2010 or higher (Visual Studio Express is freely available for open source projects like Featherweight)
  1. NI LabVIEW 2015 or higher

#### Build process
  1. Clone this repository with the `--recursive` flag to ensure all submodules are cloned: `git clone --recursive https://github.com/featherweight/featherweight.git`
  1. Navigate into the repo root, and then enter the kernel directory: `cd kernel`
  1. Create a build directory: `mkdir build`
  1. Enter this new build directory: `cd build`
  1. Invoke build system generation: `cmake ..`
    - alternatively, specify the backend generator, such as `cmake -G "Visual Studio 14 2015 Win64" ..`
  1. Open the newly generated MSVS solution: `featherweight.sln`
  1. Build the `ALL_BUILD` project to generate the library and tests
  1. Build `RUN_TESTS` to ensure unit tests pass
  1. Optionally, configure the `featherweight` project with more convenient settings:
    - "Set as StartUp Project" for `featherweight` project
    - /General/Output Directory: `..\..\lib\`
    - /Debugging/Command: `"C:\Program Files (x86)\National Instruments\LabVIEW 2015\LabVIEW.exe"`
    - /Debugging/Command Arguments: `"..\..\FTW.lvproj"`
