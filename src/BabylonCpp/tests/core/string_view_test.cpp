/*
Copyright 2017 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <babylon/core/hash.h>
#include <babylon/core/string_view.h>

#include <sstream>
#include <unordered_map>

TEST(TestStringView, DefaultCtor)
{
  using namespace BABYLON;

  string_view str;
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(nullptr, str.data());
  EXPECT_EQ("", str);
}

TEST(TestStringView, CstrCtor)
{
  using namespace BABYLON;

  const char* cstr = "abc";
  string_view str(cstr);
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_FALSE(str.empty());
  EXPECT_EQ('b', str[1]);
  EXPECT_EQ(cstr, str.data());
  EXPECT_EQ("abc", str);
}

TEST(TestStringView, CstrLenCtor)
{
  using namespace BABYLON;

  const char* cstr = "Hello World";
  string_view str(cstr, 5);
  EXPECT_EQ(5u, str.size());
  EXPECT_EQ(5u, str.length());
  EXPECT_FALSE(str.empty());
  EXPECT_EQ('H', str[0]);
  EXPECT_EQ(cstr, str.data());
  EXPECT_EQ("Hello", str);
}

TEST(TestStringView, StringCtor)
{
  using namespace BABYLON;

  std::string string = "Blah";
  string_view str(string);
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_FALSE(str.empty());
  EXPECT_EQ('h', str[3]);
  EXPECT_EQ(string.data(), str.data());
  EXPECT_EQ("Blah", str);
}

TEST(TestStringView, Iteration)
{
  using namespace BABYLON;

  std::string out;
  for (char c : string_view("Thing")) {
    out += c;
  }
  EXPECT_EQ("Thing", out);
}

TEST(TestStringView, ToString)
{
  using namespace BABYLON;

  string_view str;
  EXPECT_EQ(std::string(""), str.to_string());
  str = "abc";
  EXPECT_EQ(std::string("abc"), str.to_string());
  std::string string = static_cast<std::string>(str);
  EXPECT_EQ(std::string("abc"), string);
}

TEST(TestStringView, SubStr)
{
  using namespace BABYLON;

  string_view str;
  EXPECT_EQ("", str.substr(1, 3));
  str = "Moar COFFEE!!!";
  EXPECT_EQ("COFFEE", str.substr(5, 6));
  str = "eat cake";
  EXPECT_EQ("cake", str.substr(4));
}

TEST(TestStringView, Compare)
{
  using namespace BABYLON;

  string_view str = "def";
  EXPECT_EQ(-1, str.compare("ghi"));
  EXPECT_EQ(1, str.compare("abc"));
  EXPECT_EQ(-1, str.compare("defg"));
  EXPECT_EQ(1, str.compare("de"));
  EXPECT_EQ(0, str.compare("def"));
  EXPECT_TRUE(str == "def");
  EXPECT_FALSE(str == "abc");
  EXPECT_TRUE(str != "abc");
  EXPECT_FALSE(str != "def");
  EXPECT_TRUE(str < "ghi");
  EXPECT_FALSE(str < "def");
  EXPECT_TRUE(str <= "def");
  EXPECT_FALSE(str <= "abc");
  EXPECT_TRUE(str > "abc");
  EXPECT_FALSE(str > "def");
  EXPECT_TRUE(str >= "def");
  EXPECT_FALSE(str >= "ghi");
}

TEST(TestStringView, Ostream)
{
  using namespace BABYLON;

  std::stringstream o;
  string_view str = "jumble";
  o << "bumble" << string_view() << " " << str;
  EXPECT_EQ("bumble jumble", o.str());
}

TEST(TestStringView, Hash)
{
  using namespace BABYLON;

  const char* test1 = "IAmAClass";
  string_view test2 = "IAmAClass";
  std::unordered_map<string_view, int, Hasher<string_view>> map;
  map[test2] = 5;
  EXPECT_EQ(map[test2], 5);
  EXPECT_EQ(map[test1], 5);
}
