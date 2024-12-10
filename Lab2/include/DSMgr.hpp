//
// Created by Mac on 24-11-1.
//
#ifndef __DSMGR_HPP__
#define __DSMGR_HPP__

#include <memory>
#include "config.hpp"
//data storage manager 
#include <string>
#include "Page.hpp"
#include "Frame.hpp"

using std::string;
using std::shared_ptr;

#define MAXPAGES 1000

struct bFrame;

class DSMgr{
public:
    explicit DSMgr();
    explicit DSMgr(string filename);
    ~DSMgr();
    // 打开指定的文件
    int OpenFile(string filename);

    // 关闭文件
    int CloseFile();

    // 创建新的页面
    page_id_t NewPage();

    // 读取指定的页面
    void ReadPage(page_id_t page_id, char* data);

    // 读取指定的页面
    shared_ptr<bFrame> ReadPage(int page_id);

    // 写入页面数据
    int WritePage(int frame_id, bFrame& frm);

    int WritePage(Page* page);


    // 移动文件指针
    int Seek(int offset, int pos);

    // 获取文件指针
    FILE* GetFile();

    // 增加页面计数
    inline void IncNumPages();

    // 获取页面计数
    inline int GetNumPages();

    // 设置页面使用位
    inline void SetUse(int index, int use_bit);

    // 获取页面使用位
    inline int GetUse(int index);

    inline static int getIOcount(){
        return IOcount;
    }
private:
    FILE* cuurentFile;
    int numPages;
    int pages[MAXPAGES];
    static int IOcount;
};


#endif // __DSMGR_HPP__