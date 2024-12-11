//
// Created by Mac on 24-12-7.
//

#include <iostream>
#include "./include/BMgr.hpp"
#include "./include/LRUReplacer.hpp"

#define TRACE_FILE "./data-5w-50w-zipf.txt"

using std::cout;
using std::endl;


int main(){
    int buf_size = DEFBUFSIZE;
    auto buf = new bFrame[buf_size];

    // 检查test.db文件大小，如果小于50000*PAGE_SIZE，则扩充文件的大小到这个大小
    FILE* db_file = fopen("test.dbf", "r");
    if(db_file == nullptr){
        db_file = fopen("test.dbf", "w");
        void* buffer = malloc(50000 * PAGE_SIZE);
        fwrite(buffer, PAGE_SIZE, 50000, db_file);
        free(buffer);
    }
    fclose(db_file);

    auto bmgr = new BMgr("test.dbf", ReplacePolicy::Lru, buf_size);

    FILE* trace_file = fopen(TRACE_FILE, "r");

    int op;

    page_id_t page_id;

    int count = 0;
    while(fscanf(trace_file, "%d,%d\n", &op, &page_id) == 2){
//        cout<< ++count<<" "<<op<<" "<<page_id<<" lines has finished" <<endl;
        if(op == 0){// read
            bmgr->FixPage(page_id);
        }
        else if(op == 1){ // write
            int FrameID =  bmgr->FixPage(page_id);
            bmgr->SetDirty(FrameID);
        }
//        bmgr->UnfixPage(page_id);
    }
    fclose(trace_file);

    delete bmgr;

    cout << "IO count: " << DSMgr::getIOcount() << endl;

    return 0;
}
