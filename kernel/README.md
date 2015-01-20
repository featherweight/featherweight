# featherweight-dev

This repository is intended for Featherweight developers and contributors. If you're just looking to use Featherweight, check out https://github.com/wirebirdlabs/featherweight.

Featherweight ships with a library (ftw32.dll, ftw64.dll, or ftw32.so, depending on target) which is used by VIs written in LabVIEW. This library wraps strategic open-source libraries written in C and exports their functionality for use in G.

The short tutorials below walk through building the featherweight library on currently-supported targets.

**Note:** Featherweight contributors and developers working in G typically will not need the build instructions below. The latest released version of the featherweight library ships with the main featherweight framework in G.

## Building for NI Linux Real-Time

#### Prerequisites
  1. Hardware target with NI Linux Real-Time
  1. Internet connection for hardware target *(Alternatively, repository and build toolchain may be transferred via USB or a local network connection, but that is outside the scope of this tutorial)*
  1. NI LabVIEW 2013 or higher

#### Preparing hardware target for building
  1. From NI MAX, ensure the latest firmware and software are installed on the hardware target
  1. From NI MAX, ensure a network adapter is enabled and internet-connected
  1. Log in to the device from a terminal; e.g., `ssh admin@192.168.0.10`
  1. Ensure that the package manager packages are up to date: `opkg update`
  1. Install build toolchain: `opkg install packagegroup-core-buildessential-dev`
  1. Install git in order to clone the repository: `opkg install git`
  1. Install root Certificate Authories in order to trust HTTPS SSL cert when cloning from GitHub: `opkg install ca-certificates`

#### Build process
  1. From an SSH command-line session, navigate to your home directory: `cd ~`
  1. Clone this repository with the `--recursive` flag to ensure all submodules are cloned: `git clone --recursive https://github.com/wirebirdlabs/featherweight-lib.git`
  1. Invoke build system generation: `autoreconf -i`
  1. Configure library for your system: `./configure`
  1. Build library: `make`
  1. Run unit tests: `make check`
  1. Install library: `make install`


##Building for Windows

#### Prerequisites
  1. CMake 2.8.12 or higher
  1. Microsoft Visual Studio 2010 or higher (Visual Studio Express is freely available for open source projects like Featherweight)
  1. NI LabVIEW 2013 or higher
  
#### Build process
  1. Clone this repository with the `--recursive` flag to ensure all submodules are cloned: `git clone --recursive https://github.com/wirebirdlabs/featherweight-lib.git`
  1. Navigate to the root and create a build directory: `md builds`
  1. Enter this new build directory: `cd builds`
  1. Invoke build system generation: `cmake ..`
  1. Open the newly generated MSVS solution: `featherweight.sln`
  1. Build the `ALL_BUILD` project to generate the library and tests
  1. Build `RUN_TESTS` to ensure unit tests pass
  1. Optionally, configure the `featherweight` project to more convenient settings while specifically developing:
    - /General/Output Directory: `..\..\ftw-master\ftw\lib\`
    - /General/Target Name: `ftw32`
    - /Debugging/Command: `"C:\Program Files (x86)\National Instruments\LabVIEW 2013\LabVIEW.exe"`
    - /Debugging/Command Arguments: `"C:\Users\Jack\repo\ftw-master\ftw\examples\FTW-Example-Actors.vi"`
    - /Linker/Advanced/Image Has Safe Exception Handlers: `No (/SAFESEH:NO)` (may be required due to labviewv.lib)
