//
// Created by Mac on 24-11-14.
//

#ifndef LAB2_LRUREPLACER_HPP
#define LAB2_LRUREPLACER_HPP

#include "Replacer.hpp"

class LRUReplacer : public Replacer {
public:
    LRUReplacer();
    ~LRUReplacer() override;

    // 选择一个牺牲者
    int SelectVictim() override;

    // 更新牺牲者的状态
    void Update(int frame_id) override;


};

#endif //LAB2_LRUREPLACER_HPP
