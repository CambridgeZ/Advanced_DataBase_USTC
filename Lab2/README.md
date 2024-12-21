# README

[README_EN.md](README_EN.md)

## Introduction

再次项目当中需要实现一个简单的存储和缓存管理器

## 环境需要

- cmake 3.12 or later
- g++/clang++

## How to use

```shell
cmake -B build
```

确定在当前目录下生成了一个build文件夹，然后执行

```shell
cmake --build build
```

在执行完成上面的编译命令之后运行下面的命令以运行本程序生成的测试程序

```shell
../build/test_buffer_manager
```

## 项目结构

```shell
.
├── CMakeLists.txt
├── README.md
├── README_EN.md
├── buffer.pdf
├── data-5w-50w-zipf.txt
├── data_mini.txt
├── googletest # third party library for testing
├── include
│         ├── BCB.hpp # Buffer Control Block
│         ├── BMgr.hpp # Buffer Manager 缓存管理器
│         ├── Buffer.hpp
│         ├── DSMgr.hpp # Data Storage Manager 数据存储管理器，用于完成和磁盘的交互操作
│         ├── Frame.hpp # Frame
│         ├── LRUReplacer.hpp
│         ├── Page.hpp # Page
│         ├── Replacer.hpp 
│         └── config.hpp # 配置文件
├── main.cpp
├── src
│         ├── BMgr.cpp
│         ├── DSMgr.cpp
│         ├── LRUReplacer.cpp
│         └── Page.cpp
├── test
│         ├── test_BMgr
│         ├── test_DSgr
│         ├── test_LRUListofBMgr
│         └── test_LRUReplacer
├── test.db
└── 缓存.md
```

## Others

[设计思路](设计思路.md)

完整项目可以与2025年1月17日之后于[link](https://github.com/CambridgeZ/Advanced_DataBase_USTC/tree/main/Lab2)



