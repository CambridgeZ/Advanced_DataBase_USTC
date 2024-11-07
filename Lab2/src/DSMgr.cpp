#include "../include/DSMgr.hpp"
#include "../include/Frame.hpp"

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

