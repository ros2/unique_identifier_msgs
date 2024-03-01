// Copyright 2024 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>

#include "unique_identifier_msgs/msg/uuid.hpp"

#include "unique_identifier_msgs/uuid_conversion.hpp"

using unique_identifier_msgs::msg::UUID;

TEST(UUID, toAndFromMessage)
{
  std::string s("da7c242f-2efe-5175-9961-49cc621b80b9");
  uuid_t x;
  uuid_parse(s.c_str(), x);
  UUID msg = unique_identifier_msgs::toMsg(x);
  uuid_t y;
  unique_identifier_msgs::fromMsg(msg, y);
  EXPECT_EQ(uuid_compare(x, y), 0);
}

TEST(UUID, randomMessage)
{
  UUID x = unique_identifier_msgs::fromRandom();
  UUID y = unique_identifier_msgs::fromRandom();
  EXPECT_NE(x, y);
}

TEST(UUID, toHexString)
{
  std::string s("da7c242f-2efe-5175-9961-49cc621b80b9");
  uuid_t x;
  uuid_parse(s.c_str(), x);
  std::string uuid_s = unique_identifier_msgs::toHexString(x);
  EXPECT_EQ(s, uuid_s);
}

// Run all the tests that were declared with TEST()
int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
