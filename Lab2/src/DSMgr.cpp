#include "../include/DSMgr.hpp"
#include "../include/Frame.hpp"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::cerr;
using std::endl;

int DSMgr::IOcount = 0;

int DSMgr::OpenFile(string filename){
    cuurentFile = fopen(filename.c_str(), "r+");
    if(cuurentFile == nullptr){
        cuurentFile = fopen(filename.c_str(), "w+");
        if(cuurentFile == nullptr){
            return -1;
        }
    }
    return 0;
}

int DSMgr::CloseFile(){
    if(cuurentFile == nullptr){
        return -1;
    }
    fclose(cuurentFile);
    return 0;
}

FILE* DSMgr::GetFile(){
    return cuurentFile;
}

void DSMgr::SetUse(int index, int use_bit) {
    pages[index] = use_bit;
}

int DSMgr::GetUse(int index) {
    return pages[index];
}

void DSMgr::IncNumPages() {
    numPages++;
}

int DSMgr::GetNumPages() {
    return numPages;
}


int DSMgr::Seek(int offset, int pos) {
    return fseek(cuurentFile, offset, pos);
}

int DSMgr::WritePage(int frame_id, bFrame& frm) {
    IOcount++;
    if(frame_id >= DEFBUFSIZE){
        cerr << "Frame_id is out of range" << endl;
        std::cout<<"frame_id: "<<frame_id<<endl;
        return -1;
    }
    if(Seek(frame_id * FRAMESIZE, SEEK_SET) != 0){
        cerr << "Seek Error" << endl;
        return -1;
    }
    if(fwrite(frm.field, FRAMESIZE, 1, cuurentFile) != 1){
        cerr << "WritePage Error" << endl;
        return -1;
    }
    return 0;
}

int DSMgr::WritePage(Page* page){
    IOcount++;
    page_id_t page_id = page->getPageId();
    if(Seek(page_id * FRAMESIZE, SEEK_SET) != 0){
        cerr << "Seek Error" << endl;
        return -1;
    }

    if(fwrite(page->getData(), FRAMESIZE, 1, cuurentFile) != 1){
        cerr << "WritePage Error" << endl;
        return -1;
    }

    return 0;
}


DSMgr:: ~DSMgr(){
    CloseFile();
}

DSMgr::DSMgr(){
    numPages = 0;
    memset(pages, 0, sizeof(pages));
}

DSMgr::DSMgr(string filename){
    numPages = 0;
    memset(pages, 0, sizeof(pages));
    OpenFile(filename);


}

page_id_t DSMgr::NewPage(){
    bFrame frm;
    memset(frm.field, 0, FRAMESIZE);
    if(Seek(numPages * FRAMESIZE, SEEK_SET) != 0){
        cerr << "Seek Error" << endl;
        return -1;
    }
    if(fwrite(frm.field, FRAMESIZE, 1, cuurentFile) != 1){
        cerr << "WritePage Error" << endl;
        return -1;
    }
    IncNumPages();
    return numPages - 1;
}

void DSMgr::ReadPage(page_id_t page_id, char* data){
    IOcount++;
    if(Seek(page_id * FRAMESIZE, SEEK_SET) != 0){
        cerr << "Seek Error" << endl;
        return;
    }
    if(fread(data, FRAMESIZE, 1, cuurentFile) != 1){
//        cerr << "ReadPage Error" << endl;
        return;
    }
}


shared_ptr<bFrame> DSMgr::ReadPage(int page_id){
    IOcount++;
    shared_ptr<bFrame> ret = std::make_shared<bFrame>();
    if(Seek(page_id * FRAMESIZE, SEEK_SET) != 0){
        cerr << "Seek Error" << endl;
        return nullptr;
    }
    if(fread(ret->field, FRAMESIZE, 1, cuurentFile) != 1){
        cerr << "ReadPage Error" << endl;
        return nullptr;
    }
    return ret;
}






