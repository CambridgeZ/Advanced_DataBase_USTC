//
// Created by Mac on 24-11-14.
//

#ifndef LAB2_REPLACER_HPP
#define LAB2_REPLACER_HPP

// 替换算法
class Replacer {
public:
    virtual ~Replacer() = default;

    // 选择一个牺牲者
    virtual int SelectVictim() = 0;

    // 更新牺牲者的状态
    virtual void Update(int frame_id) = 0;
};


#endif //LAB2_REPLACER_HPP
