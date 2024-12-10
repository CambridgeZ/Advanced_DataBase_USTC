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

    auto bmgr = new BMgr("test.db", ReplacePolicy::Lru, buf_size);

    FILE* trace_file = fopen(TRACE_FILE, "r");

    int op;

    page_id_t page_id;

    int count = 0;
    while(fscanf(trace_file, "%d %d\n", &op, &page_id) == 2){
        cout<< ++count<<" "<<op<<" "<<page_id<<" lines has finished" <<endl;
        if(op == 0){
            bmgr->FixPage(page_id);
        }
        else if(op == 1){
            int FrameID =  bmgr->FixPage(page_id);
            bmgr->SetDirty(FrameID);
        }
        else{
            bmgr->UnfixPage(page_id);
        }
    }

    fclose(trace_file);

    delete bmgr;

    cout << "IO count: " << DSMgr::getIOcount() << endl;

    return 0;
}
