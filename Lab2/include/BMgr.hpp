//
// Created by Mac on 24-11-1.
//
#ifndef __BMGR_HPP__
#define __BMGR_HPP__

#include "config.hpp"
#include "DSMgr.hpp"
#include "Replacer.hpp"
#include <list>
#include <mutex>

using std::list;

struct BCB;
struct bFrame;

enum ReplacePolicy { Invalid = 0, Lru, Clock };
// Buffer Manager
class BMgr{
    using Lock = std::lock_guard<std::mutex>;
public:
    BMgr();
    BMgr(string filename, int policy = ReplacePolicy::Lru, int frame_num = FRAME_NUM);
    // Interface functions

    // 查找页面是否已在缓冲区中，若不存在则加载页面
    frame_id_t FixPage(int page_id);
    void FixNewPage(int& page_id, bFrame& frm);
    frame_id_t FixNewPage(int& page_id);
    frame_id_t UnfixPage(int page_id);
    int NumFreeFrames();

    // Internal functions
    // 选择替换页面。
    frame_id_t SelectVictim();

    // 通过page_id获取frame_id。
    frame_id_t Hash(int page_id);
    int hash(int page_id);
    void RemoveBCB(BCB* ptr, int page_id);

    // 通过frame_id删除LRU链表中的元素。
    void RemoveLRUEle(int frame_id);
    void UnsetDirty(int frame_id);
    void SetDirty(int frame_id);
    void PrintReplacer();
    void PrintPageTable();

    void printFrame(int frame_id);


private:
    // Hash Table

    // 通过frame_id 来找到对应的 page_id
    int ftop[DEFBUFSIZE];

    // 一个BCB指针数组，每个BCB其实指向后面是一个链表，这个链表是用来解决hash冲突的
    // 通过page_id 来找到对应的 frame
    // BCB 存储在 page_id % DEFBUFSIZE 的链表里面
    BCB* ptof[DEFBUFSIZE];

    // 用于替换的算法
    Replacer* replacer_;

    DSMgr* dsMgr;
    list<int> free_list_;
    std:: mutex latch_;
    bFrame frame[DEFBUFSIZE];

    // 用于LRU算法的链表， 用于记录最近访问的页面
    list<int> LRUList;
    int frame_num_;

    BCB* LRU_head;
    BCB* LRU_tail;

public:
    void ReMoveToTheTailOfLRUList(BCB* ptr);
    BCB* insertToTheTailOfLRUList(BCB* ptr);
    bool deleteBCBFromPTOF(int frame_id);

    void printLRUList();

    int BCB_count;

};

#endif // __BMGR_HPP__