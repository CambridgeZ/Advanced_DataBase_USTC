#include "BMgr.hpp"
#include "Frame.hpp"
#include "BCB.hpp"

BMgr::BMgr(){
    for(int i = 0; i < DEFBUFSIZE; i++){
        ftop[i] = -1;
        ptof[i] = nullptr;
    }
}

void BMgr:: SetDirty(int frame_id){
    if(ptof[frame_id] == nullptr){
        return;
    }
    ptof[frame_id]->dirty = 1;
}

void BMgr:: UnsetDirty(int frame_id){
    if(ptof[frame_id] == nullptr){
        return;
    }
    ptof[frame_id]->dirty = 0;
}


