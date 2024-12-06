//
// Created by Mac on 24-12-6.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../../include/LRUReplacer.hpp"
using namespace std;

TEST(LRUReplacerTest1, SampleTest) {
  LRUReplacer *replacer = new LRUReplacer(5);
  for (int i = 1; i <= 5; i++) {
    replacer->Insert(i);
    EXPECT_EQ(replacer->Size(), i);
  }
  replacer->Insert(1);
  // 2 3 4 5 1
  EXPECT_EQ(replacer->Size(), 5);
  // 3 4 5 1
  EXPECT_EQ(replacer->SelectVictim(), 2);
  EXPECT_EQ(replacer->Size(), 4);
  // 3 5 1
  replacer->Remove(4);
  EXPECT_EQ(replacer->Size(), 3);
  for (int i = 7; i <= 9; i++) {
    replacer->Insert(i);
  }
  // 5 1 7 8 9
  replacer->Insert(5);
  replacer->Insert(1);
  // 7 8 9 5 1
  EXPECT_EQ(replacer->SelectVictim(), 7);
  EXPECT_EQ(replacer->SelectVictim(), 8);
  EXPECT_EQ(replacer->SelectVictim(), 9);
  EXPECT_EQ(replacer->SelectVictim(), 5);
  EXPECT_EQ(replacer->SelectVictim(), 1);
  EXPECT_EQ(replacer->Size(), 0);
  for (int i = 10; i <= 14; i++) {
    replacer->Insert(i);
  }
  EXPECT_EQ(replacer->Size(), 5);
  delete replacer;
}

int main(int argc, char **argv) {
    /*
     * 程序运行输入参数：
     * 1. --gtest_filter=LRUReplacerTest1.SampleTest
     * 2. --gtest_filter=LRUReplacerTest2.SampleTest
     */
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


