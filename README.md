# Route Planning using A*

This project implements Route Planning based on the A* algorithm using [OpenStreetMap](https://www.openstreetmap.org/#map=4/38.01/-95.84).

It is part of the [C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) and forked off of the provided [starter code](https://github.com/udacity/CppND-Route-Planning-Project).

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/udacity/CppND-Route-Planning-Project.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:udacity/CppND-Route-Planning-Project.git --recurse-submodules
```

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it

## Compiling and Running

### Steps to make it for on OSx
Assumption: The following are successfully installed (see instructions above):
* cmake >= 3.11.3,
* make >= 4.1 and
* g++ >= 7.4.0

Follow these steps to install IO2D:
1. Download a fresh build of libc++ from http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-x86_64-apple-darwin.tar.xz
2. Export appropriate CXX and LD flags to make clang use this version of the standard library (replace NEWPATH with a path of extracted archive contents):
  * In my machine, I unzipped the libc++ build here, `/Users/kat/Library/Cpp/`.
  * I added following entries in `.bash_profile` file (make sure to replace my path `/Users/kat/Library/Cpp/` with the path where you've saved the libc++ build):
  ```bash
    export CXXFLAGS="-nostdinc++ -isystem/Users/kat/Library/Cpp/clang+llvm-6.0.0-x86_64-apple-darwin/include/c++/v1"
    export LDFLAGS="-L/Users/kat/Library/Cpp/clang+llvm-6.0.0-x86_64-apple-darwin/lib -Wl,-rpath,/Users/kat/Library/Cpp/clang+llvm-6.0.0-x86_64-apple-darwin/lib"
  ```
3. Open a new terminal and then execute below commands:
4. Install Brew (if you haven't already): `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
5. Install libpng (if you haven't already): `brew install libpng`
6. `git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl` **Note:** I cloned this folder also inside `/Users/kat/Library/Cpp/`
 ```bash
 cd P0267_RefImpl
 mkdir Debug
 cd Debug
 cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=COREGRAPHICS_MAC ..
 cmake --build .
 make
 sudo make install
 ```
7. After this, this project should build by following the steps below.

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

