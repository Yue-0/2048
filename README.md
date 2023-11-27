__English__ | [简体中文](README_cn.md)

# AI for 2048

## Brief Introduction

This project includes:
* Use C++ to implement the 2048 game;
* Use OpenCV to display the 2048 game interface;
* Implement 2048 AI based on Alpha-beta pruning search algorithm and use multi-threaded search;
* The main program uses asynchronous processing technology, and the AI can search while updating the game screen.

The probability of the AI achieved by this project reaching 2048 or higher is about 63%, and the maximum value reached in 100 games is as follows:

| Maximum   | 512 | 1024 | 2048 | 4096 |
| :-------: | :-: | :--: | :--: | :--: |
| frequency | 9   | 28   | 48   | 15   |

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
