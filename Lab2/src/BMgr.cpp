#include "../include/BMgr.hpp"
#include "../include/Frame.hpp"
#include "../include/BCB.hpp"
#include "../include/LRUReplacer.hpp"

#include <iostream>

using std::cout;
using std::endl;

BMgr::BMgr(){
    BCB_count = 0;
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
    LRU_tail = nullptr;
    LRU_head = nullptr;
    BCB_count = 0;
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
//    if(LRU_head!= nullptr){
//        cout<<"LRU_head: "<<LRU_head->frame_id<<endl;
//    }
    // 查找是否在缓冲区中
    int hash_id = hash(page_id);
    BCB* ptr = ptof[hash_id];
    while(ptr != nullptr){
        if(ptr->page_id == page_id){
            ptr->count++;
            ReMoveToTheTailOfLRUList(ptr);
            return ptr->frame_id;
        }
        ptr = ptr->next;
    }

    // 在表中没有找到

    if(BCB_count < DEFBUFSIZE){
        // 内存当中还有没有分配的块
        frame_id_t frameId = BCB_count;
        BCB_count++;
        BCB* newBCB = new BCB(page_id, frameId, 1);
        insertToTheTailOfLRUList(newBCB);
        newBCB->next = ptof[hash_id];
        ptof[hash_id] = newBCB;
        ftop[frameId] = page_id;
        // 将数据读入到frame当中
        dsMgr->ReadPage(page_id, frame[frameId].field);
        return frameId;
    }

    // 内存当中没有空闲的块了
    frame_id_t frame_id = SelectVictim();
    if(frame_id == -1){
        std::cerr<<"SelectVictimError: frame_id is -1"<<std::endl;
        exit(-1);
        return -1;
    }
    else if(frame_id > DEFBUFSIZE){
        // 出错后进行的相关测试
        std::cerr<<"SelectVictimError: frame_id is larger than DEFBUFSIZE"<<std::endl;
        // 遍历LRU 链表
        cout<<"show all the frame_id in the LRU list"<<endl;

        BCB* ptr = LRU_head;
        int this_count = 0;
        while(ptr!= nullptr && ptr != LRU_tail && this_count<1024){
            this_count++;
            cout<<ptr->frame_id<<"-->";
            ptr=ptr->LRU_next;
        }
        cout<<LRU_tail->frame_id<<endl;
        cout<<this_count<<endl;
        cout<<endl;

        ptr = LRU_tail;
        this_count = 0;
        while(ptr!= nullptr && ptr != LRU_head && this_count<1024){
            this_count++;
            cout<<ptr->frame_id<<"-->";
            ptr=ptr->LRU_prev;
        }
        cout<<ptr->frame_id<<endl;
        cout<<this_count<<endl;
        exit(-1);
        return -1;
    }
//    else{
//        cout<<"has successfully selected a victim"<<endl;
//        // 说明对于链表的破坏在找到之后对于链表的操作上
//    }

    // 找到分配得到的块当中原来的page_id
    // 将原来的BCB删除
    if(!deleteBCBFromPTOF(frame_id)){
        std::cerr<<"deleteBCBFromPTOFError: frame_id is -1"<<std::endl;
        //展示这个链表上面的所有的page_id和frame_id
        cout<<"frame_id:"<<frame_id<<endl;
        cout<<"show all the page_id and frame_id in the list"<<endl;
        BCB* p = ptof[hash_id];
        while(p != nullptr){
            cout<<"page_id: "<<p->page_id<<" frame_id: "<<p->frame_id<<endl;
            p = p->next;
        }
        exit(-1);
        return -1;
    }

    // 将新的page_id插入到BCB当中
    BCB* newBCB = new BCB(page_id, frame_id, 1);

    // 插入到LRU链表当中
    insertToTheTailOfLRUList(newBCB);
    // 插入到ptof表当中
    newBCB->next = ptof[hash_id];
    ptof[hash_id] = newBCB;
    ftop[frame_id] = page_id;
    // 将数据读入到frame当中
    dsMgr->ReadPage(page_id, frame[frame_id].field);

    return frame_id;
}

bool BMgr::deleteBCBFromPTOF(int frame_id) {
    int Old_page_id = ftop[frame_id];
    ftop[frame_id] = -1;
    int Old_hash_id = hash(Old_page_id);
    BCB *p = ptof[Old_hash_id];

    if(p->frame_id == frame_id){
        // 要删除的节点在链表的开头
        ptof[Old_hash_id] = p->next;
        delete p;
        return true;
    }
    else{
        while(p->next != nullptr){
            if(p->next->frame_id == frame_id){
                BCB* tmp = p->next;
                p->next = tmp->next;
                delete tmp;
                return true;
            }
            p = p->next;
        }
    }
    // 没有找到要删除的节点
    return false;
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
//    Lock lock(latch_);
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
    if(LRU_head == nullptr){
        return -1;
    }
    BCB* ptr = this->LRU_head;
    int ret = ptr->frame_id;
    if(ptr->dirty){
        // 处理写过的脏的页面
        dsMgr->WritePage(ptr->frame_id, frame[ptr->frame_id]);
    }
    LRU_head = ptr->LRU_next;
    return ret;
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

void BMgr::ReMoveToTheTailOfLRUList(BCB *ptr) {
    // 将当前指针指向的BCB移动到LRU链表的尾部
    if(LRU_head == ptr && LRU_tail == ptr){
        return ;
    }
    else if(LRU_head == ptr){
        LRU_head = ptr->LRU_next;
        ptr->LRU_next = nullptr;
        ptr->LRU_prev = LRU_tail;
        LRU_tail->LRU_next = ptr;
        LRU_tail = ptr;
    }
    else if(LRU_tail == ptr){
        return ;
    }
    else{
        ptr->LRU_prev->LRU_next = ptr->LRU_next;
        ptr->LRU_next->LRU_prev = ptr->LRU_prev;
        ptr->LRU_next = nullptr;
        ptr->LRU_prev = LRU_tail;
        LRU_tail->LRU_next = ptr;
        LRU_tail = ptr;
    }
}

BCB* BMgr::insertToTheTailOfLRUList(BCB *ptr) {
    // 插入到LRU链表的尾部
    if(LRU_head == nullptr){
        LRU_head = ptr;
        LRU_tail = ptr;
    }
    else{
        LRU_tail->LRU_next = ptr;
        ptr->LRU_prev = LRU_tail;
        LRU_tail = ptr;
    }
    return ptr;
}

void BMgr::printLRUList() {
    BCB* ptr = LRU_head;
    while(ptr != nullptr){
        cout<<"page_id: "<<ptr->page_id<<" frame_id: "<<ptr->frame_id<<" count: "<<ptr->count<<" dirty: "<<ptr->dirty<<" latch: "<<ptr->latch<<endl;
        ptr = ptr->LRU_next;
    }
}





