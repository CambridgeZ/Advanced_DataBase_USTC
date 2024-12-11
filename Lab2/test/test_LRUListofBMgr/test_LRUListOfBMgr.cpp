//
// Created by Mac on 24-12-11.
//

#include <iostream>
#include "../../include/BMgr.hpp"
#include "../../include/BCB.hpp"

void test1(){
    BMgr* bmgr = new BMgr();
    BCB* bcb = new BCB(1, 1, 1);
    bmgr->insertToTheTailOfLRUList(bcb);
    BCB* bcb2 = new BCB(2, 2, 1);
    bmgr->insertToTheTailOfLRUList(bcb2);
    BCB* bcb3 = new BCB(3, 3, 1);
    bmgr->insertToTheTailOfLRUList(bcb3);
    BCB* bcb4 = new BCB(4, 4, 1);
    bmgr->insertToTheTailOfLRUList(bcb4);

    bmgr->ReMoveToTheTailOfLRUList(bcb2);
    bmgr->ReMoveToTheTailOfLRUList(bcb);
    bmgr->ReMoveToTheTailOfLRUList(bcb);

    bmgr->printLRUList();
}

int main(){
    test1();
    return 0;
}