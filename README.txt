#On windows if you want to use CMake and MinGW compiler:
1. Install MinGW.
2. Install CMake.
3. Open command line and go to folder where the respository is, then:
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make

#On ubuntu
1. Install CMake
2. Open command line and go to folder where the respository is, then:
mkdir build
cd build
cmake ..
make
