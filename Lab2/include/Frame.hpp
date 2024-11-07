//
// Created by Mac on 24-11-1.
//
#ifndef __FRAME_HPP__
#define __FRAME_HPP__

#define FRAMESIZE 4096

// 表示和存放一个磁盘块

struct bFrame{
    char field[FRAMESIZE];
};

#endif // __FRAME_HPP