//
// Created by Mac on 24-11-1.
//
#ifndef __BMGR_HPP__
#define __BMGR_HPP__

#include "DSMgr.hpp"

struct BCB;
struct bFrame;

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
    int ftop[DEFBUFSIZE];
    BCB* ptof[DEFBUFSIZE];
};

#endif // __BMGR_HPP__