//
// Created by Mac on 24-11-14.
//

#ifndef LAB2_REPLACER_HPP
#define LAB2_REPLACER_HPP

#include "config.hpp"

// 替换算法
class Replacer {
public:
    virtual ~Replacer() = default;

    // 选择一个牺牲者
    virtual frame_id_t SelectVictim() = 0;

    // 更新牺牲者的状态
    virtual void Update(frame_id_t frame_id) = 0;

    virtual void Insert(frame_id_t frame_id) = 0;

    virtual void Remove(frame_id_t frame_id) = 0;

    virtual void Print() = 0;

    virtual int Size() = 0;
};


#endif //LAB2_REPLACER_HPP
