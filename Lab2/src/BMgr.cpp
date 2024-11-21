#include "../include/BMgr.hpp"
#include "../include/Frame.hpp"
#include "../include/BCB.hpp"
#include "../include/LRUReplacer.hpp"

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

int BMgr:: hash(int page_id){
    return page_id % DEFBUFSIZE;
}

// 查找页面是否已在缓冲区中，若不存在则加载页面
int BMgr::FixPage(int page_id, int prot) {
    int frame_id = hash(page_id);
    BCB* ptr = ptof[frame_id];
    while(ptr != nullptr){
        if(ptr->page_id == page_id){
            ptr->count++;
            return frame_id;
        }
        ptr = ptr->next;
    }
    // 如果没有找到
    // 选择一个牺牲者
    int victim = SelectVictim();
    if(victim == -1){
        return -1;
    }
    // 如果牺牲者是脏的，写回磁盘
    if(ptof[victim]->dirty == 1){
        // 写回磁盘
        // 从磁盘中读取数据
        fseek(DSMgr::GetFile(), ptof[victim]->page_id * PAGE_SIZE, SEEK_SET);
        fread(&frame[ptof[victim]->frame_id], sizeof(char), PAGE_SIZE, DSMgr::GetFile());
    }
    // 从BCB中删除
    RemoveBCB(ptof[victim], ptof[victim]->page_id);
    // 从hash表中删除
    ftop[ptof[victim]->frame_id] = -1;
    // 从LRU链表中删除
    RemoveLRUEle(ptof[victim]->frame_id);
    // 读取数据
    fseek(DSMgr::GetFile(), page_id * PAGE_SIZE, SEEK_SET);
    fread(&frame[ptof[victim]->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
    // 更新BCB
    ptof[victim]->page_id = page_id;
    ptof[victim]->count = 1;
    ptof[victim]->dirty = 0;
    ptof[victim]->latch = 1;
    // 更新hash表
    ftop[ptof[victim]->frame_id] = victim;
    // 更新LRU链表
    LRUList.push_back(ptof[victim]->frame_id);
    return victim;
}


int BMgr::SelectVictim(){

}

