#include "../include/BMgr.hpp"
#include "../include/Frame.hpp"
#include "../include/BCB.hpp"
#include "../include/LRUReplacer.hpp"

#include <iostream>

using std::cout;
using std::endl;

BMgr::BMgr(){
    for(int i = 0; i < DEFBUFSIZE; i++){
        ftop[i] = -1;
        ptof[i] = nullptr;
    }

    // 设置free_list
    for(int i = 0; i < DEFBUFSIZE; i++){
        free_list_.push_back(i);
    }
}

BMgr::BMgr(string filename, int policy, int frame_num){
    for(int i = 0; i < DEFBUFSIZE; i++){
        ftop[i] = -1;
        ptof[i] = nullptr;
    }
    dsMgr = new DSMgr(filename);
    frame_num_ = frame_num;
    for(int i = 0; i < frame_num; i++){
        free_list_.push_back(i);
    }
    if(policy == ReplacePolicy::Lru){
        replacer_ = new LRUReplacer(frame_num);
    }
    else{
        exit(1);
    }
}

void BMgr::PrintPageTable(){
    for(int i = 0; i < DEFBUFSIZE; i++){
        if(ptof[i] != nullptr){
            cout << "frame_id: " << i << " page_id: " << ptof[i]->page_id << " count: " << ptof[i]->count << " dirty: " << ptof[i]->dirty << " latch: " << ptof[i]->latch << endl;
        }
    }
}


void BMgr:: SetDirty(int frame_id){
    if(frame_id == -1){
        cout<<"SetDirtyError: frame_id is -1"<<endl;
        return ;
    }
    if(ptof[frame_id] == nullptr){
        return;
    }
    ptof[frame_id]->dirty = 1;
}

int BMgr:: hash(int page_id){
    return page_id % DEFBUFSIZE;
}


frame_id_t BMgr::FixPage(int page_id) {
    // 查找是否在缓冲区中
    for(int i=0 ; i< DEFBUFSIZE; i++){
        if(ftop[i] == page_id){
            // 在缓冲区当中
            ptof[i]->count++;
            return i;
        }
    }
    int frame_id = hash(page_id);
    BCB* ptr = ptof[frame_id];
    while(ptr != nullptr){
        if(ptr->page_id == page_id){
            // 如果在缓冲区中
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
    if(ptof[victim] != nullptr && ptof[victim]->dirty == 1){
        // 写回磁盘
        // 从磁盘中读取数据
        fseek(dsMgr->GetFile(), ptof[victim]->page_id * PAGE_SIZE, SEEK_SET);
        fread(&frame[ptof[victim]->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
    }
    // 从BCB中删除
    if(ptof[victim] != nullptr) {
        RemoveBCB(ptof[victim], ptof[victim]->page_id);
        // 从hash表中删除
        ftop[ptof[victim]->frame_id] = -1;
        // 从LRU链表中删除
        RemoveLRUEle(ptof[victim]->frame_id);
        // 读取数据
        //    fseek(dsMgr->GetFile(), page_id * PAGE_SIZE, SEEK_SET);
        //    fread(&frame[ptof[victim]->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
        dsMgr->ReadPage(page_id, frame[ptof[victim]->frame_id].field);
        // 更新BCB
        ptof[victim]->page_id = page_id;
        ptof[victim]->count = 1;
        ptof[victim]->dirty = 0;
        ptof[victim]->latch = 1;
        // 更新hash表
        ftop[ptof[victim]->frame_id] = page_id;
        // 更新LRU链表
        LRUList.push_back(ptof[victim]->frame_id);
    }
    else{
        // 更新BCB
        ptof[victim] = new BCB(page_id, victim, 1);
        // 更新hash表
        ftop[ptof[victim]->frame_id] = page_id;
        // 读取数据
        dsMgr->ReadPage(page_id, frame[ptof[victim]->frame_id].field);
        // 更新LRU链表
        LRUList.push_back(ptof[victim]->frame_id);
    }
    return victim;
}

void BMgr::FixNewPage(int& page_id, bFrame& frm){
    page_id = dsMgr->NewPage();
    int frame_id = SelectVictim();
    if(frame_id == -1){
        return;
    }
    if(ptof[frame_id]->dirty == 1){
        fseek(dsMgr->GetFile(), ptof[frame_id]->page_id * PAGE_SIZE, SEEK_SET);
        fwrite(&frame[ptof[frame_id]->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
    }
    RemoveBCB(ptof[frame_id], ptof[frame_id]->page_id);
    ftop[ptof[frame_id]->frame_id] = -1;
    RemoveLRUEle(ptof[frame_id]->frame_id);
    ptof[frame_id]->page_id = page_id;
    ptof[frame_id]->count = 1;
    ptof[frame_id]->dirty = 0;
    ptof[frame_id]->latch = 1;
    ftop[ptof[frame_id]->frame_id] = frame_id;
    LRUList.push_back(ptof[frame_id]->frame_id);
    frm = frame[ptof[frame_id]->frame_id];
}

frame_id_t BMgr::FixNewPage(int &page_id) {
    frame_id_t frame_id = SelectVictim();
    if(frame_id == -1){
        return -1;
    }

    page_id = dsMgr->NewPage();
    fseek(dsMgr->GetFile(), page_id * PAGE_SIZE, SEEK_SET);
    fread(&frame[ptof[frame_id]->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
    ptof[frame_id]->page_id = page_id;
    ptof[frame_id]->count = 1;
    ptof[frame_id]->dirty = 0;
    ptof[frame_id]->latch = 1;
    ftop[ptof[frame_id]->frame_id] = frame_id;
    LRUList.push_back(ptof[frame_id]->frame_id);
    return frame_id;
}

frame_id_t BMgr::UnfixPage(int page_id) {
    Lock lock(latch_);
    int frame_id = hash(page_id);
    BCB* ptr = ptof[frame_id];
    while(ptr != nullptr){
        if(ptr->page_id == page_id){
            ptr->count--;
            if(ptr->count == 0){
                ptr->latch = 0;
                replacer_->Insert(frame_id);
            }
            return frame_id;
        }
        ptr = ptr->next;
    }

    return -1;
}

int BMgr::NumFreeFrames(){
    return free_list_.size();
}

frame_id_t BMgr::Hash(int page_id) {
    return page_id % DEFBUFSIZE;
}

void BMgr::RemoveBCB(BCB* ptr, int page_id){
    if(ptr == nullptr){
        return;
    }
    int frame_id = Hash(page_id);
    BCB* p = ptof[frame_id];
    if(p == ptr){
        ptof[frame_id] = p->next;
        delete p;
        return;
    }
    while(p->next != nullptr){
        if(p->next == ptr){
            BCB* tmp = p->next;
            p->next = tmp->next;
            delete tmp;
            return;
        }
        p = p->next;
    }
}

void BMgr::UnsetDirty(int frame_id) {
    if(ptof[frame_id] == nullptr){
        return;
    }
    ptof[frame_id]->dirty = 0;
}

void BMgr::PrintFrame(int frame_id) {
    printf("frame %d:\n", frame_id);
    printf("page id: %d\n", ptof[frame_id]->page_id);
    printf("dirty: %d\n", ptof[frame_id]->dirty);
    printf("pin count: %d\n", ptof[frame_id]->count);
    printf("\n");
}

frame_id_t BMgr::SelectVictim() {
    frame_id_t frame_id = -1;
    if (!free_list_.empty()) {
        frame_id = free_list_.front();
        free_list_.pop_front();
        return frame_id;
    }
    frame_id_t victim_fid = replacer_->SelectVictim();
    if (victim_fid == -1)
        return -1;
    BCB* p = ptof[victim_fid];

    if (p->dirty == 1) {
//        fseek(dsMgr->GetFile(), p->page_id * PAGE_SIZE, SEEK_SET);
//        fwrite(&frame[p->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
        dsMgr->WritePage(p->frame_id, frame[p->frame_id]);
        p->dirty = 0;
    }

    ftop[ptof[victim_fid]->frame_id] = -1;
    RemoveBCB(ptof[victim_fid], ptof[victim_fid]->page_id);
    RemoveLRUEle(ptof[victim_fid]->frame_id);
    return victim_fid;

}

void BMgr:: RemoveLRUEle(int frid){
    LRUList.remove(frid);
    // 写回磁盘
    if(ptof[frid]->dirty == 1){
//        fseek(dsMgr->GetFile(), ptof[frid]->page_id * PAGE_SIZE, SEEK_SET);
//        fwrite(&frame[ptof[frid]->frame_id], sizeof(char), PAGE_SIZE, dsMgr->GetFile());
        dsMgr->WritePage(ptof[frid]->frame_id, frame[ptof[frid]->frame_id]);
    }
}

void BMgr::PrintReplacer() {
    replacer_->Print();
}





