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

