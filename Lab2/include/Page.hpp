//
// Created by Mac on 24-11-1.
//

#ifndef LAB2_PAGE_HPP
#define LAB2_PAGE_HPP

#include "config.hpp"

class Page {
private:
    size_t page_id;
    size_t page_size;
    char data[PAGE_SIZE];
    int pin_count;// 页被固定的次数

public:
    virtual ~Page() = default;

    explicit Page(size_t page_id, size_t page_size = PAGE_SIZE) : page_id(page_id), page_size(page_size), pin_count(0) {
        memset(data, 0, PAGE_SIZE);
    }

    size_t getPageId() const {
        return page_id;
    }

    size_t getPageSize() const {
        return page_size;
    }

};


#endif //LAB2_PAGE_HPP
