__English__ | [简体中文](README_cn.md)

# AI for 2048

## Brief Introduction

This project includes:
* Use C++ to implement the 2048 game;
* Use OpenCV to display the 2048 game interface;
* Implement 2048 AI based on Mini-max search algorithm.

This project provides a Python version. The Python version of AI is implemented using the Monte Carlo search algorithm and the max-min search algorithm respectively. For details, see the [Python branch](https://github.com/Yue-0/2048/tree/Python).

## File Structure

```
2048
├── ai.hpp          # Mini-max search algorithm
├── CMakeLists.txt  # CMake file
├── game.hpp        # The 2048 game
├── LICENSE         # LICENSE
├── main.cpp        # Main program
├── README_cn.md    # Chinese description document
├── README.md       # English description document
└── window.hpp      # Visual window code
```

## Quick Start

### 1. Check the environment

This project relies on OpenCV (C++). If you have not configured OpenCV, please compile and configure OpenCV (C++) first.

It is recommended that the version of OpenCV is no lower than 4.5.5.

### 2.Clone

```shell
git clone https://github.com/Yue-0/2048.git
cd ./2048
```

### 3.Build

This project requires CMake for compilation.

```shell
mkdir build
cd ./build
cmake ..
make
```

After successful compilation, the compilation results will be generated in the build folder.

### 4.Run

Start main directly to start running the program.

```shell
./main
```

After starting the program, a window will appear. Click "AI" to let the AI start the game. Click "Keyboard" to start the game using the keyboard. You need to use ↑/↓/←/→ to control the direction.

## Shortcomings

There are still many deficiencies in this project, such as:

* The search tree is not pruned;
* The score function is not carefully designed;
* The updated cell is only 2, but it should be 2 or 4;
* ...
