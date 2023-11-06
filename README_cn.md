[English](README.md) | __简体中文__

## 简介

本项目内容包括：
* 使用 Python 实现 2048 游戏；
* 使用 PyGame 显示 2048 游戏界面；
* 基于蒙特卡洛搜索算法和最大最小搜索算法实现 2048 AI。

本项目的 C++ 版本的 AI 具有更优秀的性能（即将发布）。

## 文件结构

```
2048
├── color.json        # 定义界面的颜色
├── font.ttf          # 字体文件
├── game.py           # 2048 游戏
├── icon.jpeg         # 界面图标
├── LICENSE           # LICENSE
├── main.py           # 主程序
├── mcs.py            # 蒙特卡洛搜索算法
├── mms.py            # 最大最小搜索算法
├── README.md         # 英文说明文件
├── README_cn.md      # 中文说明文件
└── requirements.txt  # 依赖库列表
```

## 快速开始

### 1.克隆项目

```shell
git clone https://github.com/Yue-0/2048.git
cd ./2048
```

### 2.安装依赖

项目依赖的库包括：
* numpy
* pygame

```shell
pip install -r requirements.txt
```

### 3.使用键盘开始游戏

运行 game.py 来使用键盘进行游戏，请使用 ↑/↓/←/→ 控制方向。

```shell
python game.py
```

### 4.让 AI 开始游戏

运行 main.py 即可让 AI 开始游戏，你可以通过命令行参数指定 AI 的策略：

```shell
python main.py --method mcs --step 50  # AI 的策略为蒙特卡洛搜索，次数为 50（默认 100）
python main.py --method mms --depth 3  # AI 的策略为最大最小搜索，深度为 3（默认 2）
```

main.py 的所有命令行参数如下表所示。

| 参数名      | 类型  | 默认值 | 说明                                                    |
|:---------|:---:|:---:|:------------------------------------------------------|
| --method | str | mcs | AI 的策略，必须为 mcs 或 mms                                  |
| --size   | int |  4  | 游戏棋盘的大小，必须为正整数，过大的值可能会带来错误，当 --method 为 mms 时，必须使用默认值 |
| --step   | int | 100 | 蒙特卡洛搜索的次数，必须为正整数，过大的值会导致程序运行缓慢                        |
| --depth  | int |  2  | 最大最小搜索的深度，必须为正整数，过大的值会导致程序运行缓慢                        |

你也可以直接运行下面的代码来查看它们。

```shell
python main.py --help
```

## 不足

本项目还存在许多不足之处，例如：
* 没有精心设计得分函数；
* 没有对搜索树进行剪枝；
* 新出现的方块只有2，而不是2或4；
* ……
