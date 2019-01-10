angru

C++ small framework with boost and pistache and STL and libpqxx
How to build using CMake

In order to build insomnia using CMake outside the source directory:

$ cd /path/to/insomnia/source
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ../
$ make

In order to do a multi-threaded build using ninja generator:

$ cd /path/to/insomnia/source
$ mkdir build
$ cd build
$ cmake -GNinja -DCMAKE_BUILD_TYPE=Release ../
$ ninja

In order to build using a different compiler (e.g. LLVM/Clang):

$ cd /path/to/insomnia/source
$ mkdir build
$ cd build
$ cmake -GNinja -DCMAKE_C_COMPILER=/usr/lib/llvm/6/bin/clang -DCMAKE_CXX_COMPILER=/usr/lib/llvm/6/bin/clang++ -DCMAKE_BUILD_TYPE=Release ../
$ ninja
