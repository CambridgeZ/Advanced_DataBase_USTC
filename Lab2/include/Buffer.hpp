//
// Created by Mac on 24-11-1.
//
#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "config.hpp"
#include "Frame.hpp"


// 读磁盘的时候：根据page_id 确定 Buffer 当中是否存在相应的frame
// 写磁盘的时候： 根据frame_id 快速找到对应的page_id



#endif // __BUFFER_HPP__