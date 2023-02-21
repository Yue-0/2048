[English](README.md) | __简体中文__

## 简介

本项目是我的大二Python程序设计课程的期末作业，项目内容包括：
* 使用NumPy实现2048游戏；
* 使用PyGame显示2048游戏界面；
* 基于蒙特卡洛搜索算法实现2048AI。

我的AI几乎可以在每局游戏中达到2048甚至更高。

项目使用的编程语言为Python3.9。

## 文件结构

```
2048
├── color.json        # 定义界面的颜色
├── config.py         # 定义相关配置
├── font.ttf          # 字体文件
├── game.py           # 2048游戏
├── icon.jpeg         # 界面图标
├── LICENSE           # LICENSE文件
├── main.py           # 主程序
├── mcs.py            # 蒙特卡洛搜索算法
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

### 3.让AI开始玩2048

```shell
python main.py
```

## 不足

本项目还存在许多不足之处，例如：
* 游戏界面没有动画效果；
* 没有精心设计得分函数；
* 新出现的方块只有2，而不是2或4；
* ……
