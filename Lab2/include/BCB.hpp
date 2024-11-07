//
// Created by Mac on 24-11-1.
//
#ifndef __BCB_HPP__
#define __BCB_HPP__

//buffer control block

struct BCB{
    BCB():page_id(-1), frame_id(-1), latch(0), count(0), dirty(0), next(nullptr){}
    int page_id;
    int frame_id;
    int latch;
    int count;
    int dirty;
    BCB* next;
};


#endif // __BCB_HPP__