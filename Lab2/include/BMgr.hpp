//
// Created by Mac on 24-11-1.
//
#ifndef __BMGR_HPP__
#define __BMGR_HPP__

#include "DSMgr.hpp"

struct BCB;
struct bFrame;

// Buffer Manager
class BMgr{
public:
    BMgr();
    // Interface functions
    int FixPage(int page_id, int prot);
    void NewPage(int& page_id, bFrame& frm);
    int UnfixPage(int page_id);
    void FixNewPage(int& page_id, bFrame& frm);
    int NumFreeFrames();

    // Internal functions
    int SelectVictim();
    int Hash(int page_id);
    void RemoveBCB(BCB* ptr, int page_id);
    void RemoveLRUEle(int frame_id);
    void UnsetDirty(int frame_id);
    void SetDirty(int frame_id);
    void PrintFrame(int frame_id);

private:
    // Hash Table

    // 通过frame_id 来找到对应的 page_id
    int ftop[DEFBUFSIZE];

    // 一个BCB指针数组，每个BCB其实指向后面是一个链表，这个链表是用来解决hash冲突的
    // 通过page_id 来找到对应的 frame
    // BCB 存储在 page_id % DEFBUFSIZE 的链表里面
    BCB* ptof[DEFBUFSIZE];
};

#endif // __BMGR_HPP__