//
// Created by Mac on 24-11-14.
//

#ifndef LAB2_LRUREPLACER_HPP
#define LAB2_LRUREPLACER_HPP

#include "Replacer.hpp"
#include <unordered_map>

class LRUReplacer : public Replacer {
public:
    LRUReplacer(int max_size);
    ~LRUReplacer() override;

    // 选择一个牺牲者
    frame_id_t SelectVictim() override;

    // 更新牺牲者的状态
    void Update(frame_id_t frame_id) override;

    void Insert(frame_id_t frame_id) override;

    void Remove(frame_id_t frame_id) override;

    void Print() override;

    int Size() override;

private:

    struct ListNode {
        ListNode() = default;
        ListNode(frame_id_t _val) : val(_val) {}
        frame_id_t val;
        ListNode *prev, *next;
    };

    inline void set_pointer(ListNode *p, ListNode *q) {
        p->next = q;
        q->prev = p;
    }

    void pop_node();

    void append_node(ListNode *new_node);

    std::unordered_map<int, ListNode *> map_;
    ListNode *head_, *tail_;
    int size_;
    int max_size_;

};

#endif //LAB2_LRUREPLACER_HPP
