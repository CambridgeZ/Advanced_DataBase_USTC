//
// Created by Mac on 24-11-27.
//

#include "../include/LRUReplacer.hpp"

LRUReplacer::LRUReplacer(int max_size) {
    max_size_ = max_size;
    size_ = 0;
    head_ = new ListNode();
    tail_ = new ListNode();
    head_->next = tail_;
    tail_->prev = head_;
}

frame_id_t LRUReplacer::SelectVictim() {
    if (size_ == 0)
        return -1;
    frame_id_t ret;
    ret = head_->next->val;
    pop_node();
    return ret;
}

void LRUReplacer::Update(frame_id_t frame_id) {
    auto iter = map_.find(frame_id);
    if (iter == map_.end()) {
        return;
    }
    ListNode *tmp = iter->second;
    set_pointer(tmp->prev, tmp->next);
    append_node(tmp);
}

void LRUReplacer::Insert(frame_id_t frame_id) {
    auto iter = map_.find(frame_id);
    if (iter == map_.end()) {
        if (size_ == max_size_)
            pop_node();
        append_node(new ListNode(frame_id));
        return;
    }
    ListNode *tmp = iter->second;
    set_pointer(tmp->prev, tmp->next);
    size_--;
    append_node(tmp);
}

void LRUReplacer::Remove(frame_id_t frame_id) {
    auto iter = map_.find(frame_id);
    if (iter == map_.end()) {
        return;
    }
    ListNode *tmp = iter->second;
    set_pointer(tmp->prev, tmp->next);
    map_.erase(frame_id);
    size_--;
    delete tmp;
}

void LRUReplacer::Print() {

    printf("LRUReplacer: ");
    ListNode *p = head_->next;
    while (p != tail_) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int LRUReplacer::Size() {
    return size_;
}

void LRUReplacer::pop_node() {
    ListNode *tmp = head_->next;
    set_pointer(head_, tmp->next);
    map_.erase(tmp->val);
    delete tmp;
    size_--;
}

void LRUReplacer::append_node(ListNode *new_node) {
    ListNode *tmp = tail_->prev;
    map_[new_node->val] = new_node;
    set_pointer(tmp, new_node);
    set_pointer(new_node, tail_);
    size_++;
}

LRUReplacer::~LRUReplacer() {
    ListNode *p = head_;
    while (p != nullptr) {
        ListNode *tmp = p;
        p = p->next;
        delete tmp;
    }
}


