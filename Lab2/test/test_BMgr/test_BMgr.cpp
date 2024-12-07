//
// Created by Mac on 24-12-7.
//

#include <gtest/gtest.h>
#include <iostream>

#include "../../include/BMgr.hpp"

TEST(BMgrTest, SampleTest) {
  BMgr *bmgr = new BMgr("test.db", 5);
  page_id_t pid;
  for (int i = 0; i < 5; i++) {
    frame_id_t fid = bmgr->FixNewPage(pid);
    EXPECT_EQ(pid, i);
    bmgr->UnfixPage(pid);
  }
  // 0 1 2 3 4
  for (int i = 5; i < 10; i++) {
    EXPECT_EQ(bmgr->FixNewPage(pid), i - 5);
    EXPECT_EQ(pid, i);
    bmgr->UnfixPage(pid);
  }
  bmgr->PrintPageTable();
  bmgr->PrintReplacer();
  // 0 1 2 3 4
  bmgr->FixPage(5);
  bmgr->UnfixPage(5);
  bmgr->FixPage(8);
  bmgr->UnfixPage(8);
  bmgr->FixPage(6);
  bmgr->UnfixPage(6);
  bmgr->PrintReplacer();
  // 2 4 0 3 1
  int expect2[5] = {2, 4, 0, 3, 1};
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(expect2[i], bmgr->SelectVictim());
  }
  delete bmgr;
  remove("test.db");
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
