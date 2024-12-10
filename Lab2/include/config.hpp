//
// Created by Mac on 24-11-14.
//

#ifndef LAB2_CONFIG_HPP
#define LAB2_CONFIG_HPP

// 一般而言将页大小和帧大小设置为相同的值
#define PAGE_SIZE 4096
#define FRAMESIZE 4096

#define DEFBUFSIZE 1024
#define FRAME_NUM 1024

#include <cstddef>


using frame_id_t = int;
using page_id_t = int;

#endif //LAB2_CONFIG_HPP
