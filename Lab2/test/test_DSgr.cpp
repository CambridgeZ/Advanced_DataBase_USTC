//
// Created by Mac on 24-12-6.
//

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#include "../include/DSMgr.hpp"
#include "../include/Page.hpp"

using std::cout;
using std::endl;

TEST(DataStorageManagerTest, SampleTest) {
  DSMgr *ds_mgr = new DSMgr("test.db");
  char buf[PAGE_SIZE];
  char buf2[PAGE_SIZE];
  for (int i = 0; i < 30; i++) {
    Page *p = new Page(i);
    sprintf(p->getData(), "hello world, this is page %d", i);
    ds_mgr->WritePage(p);
  }
  for (int i = 0; i < 30; i++) {
    ds_mgr->ReadPage(i, buf);
    sprintf(buf2, "hello world, this is page %d", i);
    // cout << buf << endl;
    cout << buf2 << endl;
    EXPECT_EQ(strcmp(buf, buf2), 0);
  }
  delete ds_mgr;
  remove("test.db");
}

TEST(DataStorageManagerTest, SampleTest2) {
  DSMgr *ds_mgr = new DSMgr("test.db");
  Page **pages;
  pages = new Page*[10];
  for (int i = 0; i < 10; i++) {
    pages[i] = new Page();
    pages[i]->setPageId(ds_mgr->NewPage());
  }
  for (int i = 0; i < 10; i++) {
    ds_mgr->WritePage(pages[i]);
  }
  delete ds_mgr;
  remove("test.db");
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}