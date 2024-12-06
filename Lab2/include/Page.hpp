//
// Created by Mac on 24-11-1.
//

#ifndef LAB2_PAGE_HPP
#define LAB2_PAGE_HPP

#include "config.hpp"
#include <cstring>

class Page {
private:
    page_id_t page_id;
    size_t page_size;
    char data[PAGE_SIZE];// 页面当中存储的数据
    int pin_count;// 页被固定的次数
    bool dirty;// 页是否被修改

public:
    virtual ~Page() = default;

    explicit Page(size_t page_id, size_t page_size = PAGE_SIZE) : page_id(page_id), page_size(page_size), pin_count(0), dirty(false) {
        memset(data, 0, PAGE_SIZE*sizeof(char));
    }

    explicit Page() = default;

    page_id_t getPageId() const {
        return page_id;
    }

    size_t getPageSize() const {
        return page_size;
    }

    char* getData() {
        return data;
    }

    int getPinCount() const {
        return pin_count;
    }

    bool isDirty() const {
        return dirty;
    }

    void setDirty(bool dirty) {
        Page::dirty = dirty;
    }

    void incPinCount() {
        pin_count++;
    }

    void decPinCount() {
        pin_count--;
    }

    void setPageId(page_id_t page_id) {
        Page::page_id = page_id;
    }

};


#endif //LAB2_PAGE_HPP
