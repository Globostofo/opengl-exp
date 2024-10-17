# Experimentations with OpenGL in C

Just some basic tests with *GLEW* and *GLFW* using the *C programming language*.  
Inspired by <https://www.opengl-tutorial.org/beginners-tutorials/>.

## Linux

### Install dependencies

Firstly, you need to install the different packages.

*Debian-like* :
```sh
sudo apt install -y cmake make g++ libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev
```

> **Note:** The project uses [cglm](https://github.com/recp/cglm) for graphics maths (vectors, matrixes). The dependency is statically compiled with CMake, you just need to init the git submodule with :

```sh
git submodule update --init --recursive
```

### Compilation

You can compile the project by running the following commands :

```sh
./bootstrap.sh
cd build
make -j $(nproc)
```

### Run

After compilation, you can find the executable at `build/src/main`.
