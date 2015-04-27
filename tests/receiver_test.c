//#include "receiver.c" //c extension on purpose, to access static vars
#include "receiver.h"
#include <gtest/gtest.h>

TEST(receiver,digit_to_int_helper)
{
  EXPECT_EQ(0, digit_to_int('0'));
  EXPECT_EQ(8, digit_to_int('8'));
}

TEST(receiver,digits_to_int_helper)
{
  EXPECT_EQ(0, digits_to_int(0,0,0));
  EXPECT_EQ(123, digits_to_int(1,2,3));
}

TEST(receiver,checksum_validator)
{
  uint8_t buffer[] = "/00000\\";
  EXPECT_EQ(true, checksum_valid(buffer));
  buffer[5] = '5';
  EXPECT_EQ(false, checksum_valid(buffer));
  buffer[1] = '1';
  buffer[2] = '1';
  buffer[3] = '1';
  buffer[4] = '1';
  buffer[5] = '4';
  EXPECT_EQ(true, checksum_valid(buffer));
  buffer[1] = '3';
  buffer[2] = '2';
  buffer[3] = '2';
  buffer[4] = '2';
  buffer[5] = '9';
  EXPECT_EQ(true, checksum_valid(buffer));
}
