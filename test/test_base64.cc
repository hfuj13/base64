#include "gtest/gtest.h"

#include "base64.hpp"

/// Refer to RFC4648 Section.10 Test Vectors
///

TEST(Base64, ENCODE)
{
  {
    std::string src_data("");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("");
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("f");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("Zg==");
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("fo");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("Zm8=");
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("foo");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("Zm9v");
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("foob");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("Zm9vYg==");
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("fooba");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("Zm9vYmE=");
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("foobar");
    auto actual = hf::b64encode(&src_data[0]);
    std::string expected("Zm9vYmFy");
    ASSERT_EQ(expected, actual);
  }
}

TEST(Base64, DECODE)
{
  {
    std::string src_data("");
    std::vector<uint8_t> actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected;
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("Zg==");
    auto actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected{'f'};
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("Zm8=");
    auto actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected{'f', 'o'};
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("Zm9v");
    auto actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected{'f', 'o', 'o'};
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("Zm9vYg==");
    auto actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected{'f', 'o', 'o', 'b'};
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("Zm9vYmE=");
    auto actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected{'f', 'o', 'o', 'b', 'a'};
    ASSERT_EQ(expected, actual);
  }

  {
    std::string src_data("Zm9vYmFy");
    auto actual = hf::b64decode(src_data);
    std::vector<uint8_t> expected{'f', 'o', 'o', 'b', 'a', 'r'};
    ASSERT_EQ(expected, actual);
  }
}
