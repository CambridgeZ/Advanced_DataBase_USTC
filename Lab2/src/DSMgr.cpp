#include "../include/DSMgr.hpp"
#include "../include/Frame.hpp"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::cerr;


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
    if(frame_id >= numPages){
        cerr << "Frame_id is out of range" << endl;
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




