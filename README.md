__English__ | [简体中文](README_cn.md)

# AI for 2048

## Brief Introduction

This project is the final assignment of my sophomore Python programming course.
This project contents include:

* Use NumPy to realize 2048 game;
* Use PyGame to display 2048 interface;
* Implementation of a 2048 AI based on Monte Carlo search algorithm.

My AI can reach 2048 or higher in almost every game.

The programming language used in this project is Python 3.9.

## File Structure

```
2048
├── color.json        # Define the color of the interface
├── config.py         # Configurations
├── font.ttf          # Font file
├── game.py           # 2048 game
├── icon.jpeg         # Interface icon
├── LICENSE           # LICENSE
├── main.py           # Main program
├── mcs.py            # Monte Carlo search algorithm
├── README.md         # English description document
├── README_cn.md      # Chinese description document
└── requirements.txt  # List of requirements
```

## Quick Start

### 1.Clone

```shell
git clone https://github.com/Yue-0/2048.git
cd ./2048
```

### 2.Install requirements

Requirements are include：
* numpy
* pygame

```shell
pip install -r requirements.txt
```

### 3.Let AI play 2048 game

```shell
python main.py
```

## Shortcomings

There are still many deficiencies in this project, such as:

* The interface has no animation effect;
* The score function is not carefully designed;
* The updated cell is only 2, but it should be 2 or 4;
* ...
