//
// Created by Mac on 24-11-1.
//
#ifndef __DSMGR_HPP__
#define __DSMGR_HPP__


//data storage manager 
#include <string>

using std::string;

#define MAXPAGES 1000

struct bFrame;

class DSMgr{
public:
    DSMgr();
    int OpenFile(string filename);
    int CloseFile();
    bFrame ReadPage(int page_id);
    int WritePage(int frame_id, bFrame frm);
    int Seek(int offset, int pos);
    FILE* GetFile();
    inline void IncNumPages();
    inline int GetNumPages();
    inline void SetUse(int index, int use_bit);
    inline int GetUse(int index);
private:
    FILE* cuurentFile;
    int numPages;
    int pages[MAXPAGES]
};


#endif // __DSMGR_HPP__