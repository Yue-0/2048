[English](README.md) | __简体中文__

## 简介

本项目内容包括：
* 使用 C++ 实现 2048 游戏；
* 使用 OpenCV 显示 2048 游戏界面；
* 基于最大最小搜索算法实现 2048 AI。

本项目提供 Python 版本，Python 版本的 AI 使用蒙特卡洛搜索算法和最大最小搜索算法分别实现，详见 [Python 分支](https://github.com/Yue-0/2048/tree/Python)。

## 文件结构

```
2048
├── ai.hpp          # AI 代码
├── CMakeLists.txt  # CMake 文件
├── game.hpp        # 2048 游戏代码
├── LICENSE         # LICENSE
├── main.cpp        # 主程序
├── README_cn.md    # 中文说明文件
├── README.md       # 英文说明文件
└── window.hpp      # 可视化窗口代码
```

## 快速开始

### 1.检查环境

本项目依赖 OpenCV（C++），如果你没有配置 OpenCV，请先编译并配置 OpenCV（C++）。

建议 OpenCV 的版本不低于 4.5.5。

### 2.克隆项目

```shell
git clone https://github.com/Yue-0/2048.git
cd ./2048
```

### 3.编译代码

本项目使用 CMake 进行编译。

```shell
mkdir build
cd ./build
cmake ..
make
```

编译成功后，会在 build 文件夹中生成编译结果。

### 4.运行程序

直接启动 main 即可开始运行程序。

```shell
./main
```

启动程序后，会出现一个窗口，点击 “AI” 即可让 AI 开始游戏，点击 “Keyboard” 即可使用键盘开始游戏，你需要使用 ↑/↓/←/→ 来控制方向。

## 不足

本项目还存在许多不足之处，例如：
* 没有精心设计得分函数；
* 没有对搜索树进行剪枝；
* 新出现的方块只有2，而不是2或4；
* ……
