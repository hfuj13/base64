// The MIT License (MIT)
//
// Copyright (C) 2016 hfuj13@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <cassert>
#include <cstdint>

#include <algorithm>
#include <array>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace hf {
constexpr char Prefix[] = "hf::";

std::string b64encode(const void* src_data, size_t src_data_sz);

/// Base64 encoder
///
/// @param [in] src_data: Source data
/// @retval Base64 encoded string
///
template<size_t N> std::string b64encode(const std::array<uint8_t, N>&src_data)
{
  return b64encode(&src_data[0], src_data.size());
}
inline std::string b64encode(const std::vector<uint8_t>& src_data)
{
  return b64encode(&src_data[0], src_data.size());
}
inline std::string b64encode(const std::string& src_data)
{
  return b64encode(&src_data[0], src_data.size());
}

/// Base64 encoder
///
/// @param [in] src_data: Source data
/// @param [in] src_data_sz: Source data size. Bytes
/// @retval Base64 encoded string
///
inline std::string b64encode(const void* src_data, size_t src_data_sz)
{
  /// Base64 character set
  static constexpr char B64chs[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  assert(src_data != nullptr);
  assert(src_data_sz >= 0);

  std::string dst;
  if (src_data_sz <= 0) {
    return dst;
  }

  const uint8_t* src_ptr = static_cast<const uint8_t*>(src_data);
  for (size_t rest_sz = src_data_sz; rest_sz > 0; src_ptr += 3) {
    dst += B64chs[src_ptr[0] >> 2 & 0x3F];
    dst += B64chs[((src_ptr[0] & 0x03) << 4) | (--rest_sz > 0 ? src_ptr[1] >> 4 : 0)];
    dst += rest_sz > 0 ? B64chs[((src_ptr[1] & 0x0F) << 2) | (--rest_sz > 0 ? (src_ptr[2] >> 6) : 0)] : '=';
    dst += rest_sz > 0 ? B64chs[src_ptr[2] & 0x3F] : '=';
    if (rest_sz > 0) {
      rest_sz--;
    }
  }
  return dst;
}

/// Base64 decoder
///
/// @param [in] src: Base64 encoded string
/// @retval Base64 decoded byte data
/// @exception std::invalid_argument
///
inline std::vector<uint8_t> b64decode(const std::string& src)
{
  if (src.size() % 4 != 0) {
    std::ostringstream oss;
    oss << __FILE__ << ":" << __LINE__ << ' '
        << Prefix
        << __func__ << "(src=\"" << src << "\") "
        << "src.size() must be a multiple of 4."
        ;
    throw std::invalid_argument(oss.str());
  }

  constexpr int BLOCK_SZ = 4;
  std::vector<uint8_t> dst;
  for (size_t i = 0; i < src.size(); i += BLOCK_SZ) {
    const char* ptr = &src[i];
    std::array<uint8_t, 3> tmp;
    uint8_t value[BLOCK_SZ] = {0};
    int j = 0;
    for (; j < BLOCK_SZ; ++j) {
      if (std::isupper(ptr[j])) {
        value[j] = ptr[j] - 65;
      }
      else if (std::islower(ptr[j])) {
        value[j] = ptr[j] - 71;
      }
      else if (std::isdigit(ptr[j])) {
        value[j] = ptr[j] + 4;
      }
      else if (ptr[j] == '+') {
        value[j] = ptr[j] + 19;
      }
      else if (ptr[j] == '/') {
        value[j] = ptr[j] + 16;
      }
      else if (ptr[j] == '=') {
        break;
      }
      else {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << ' '
            << Prefix
            << __func__ << "(src=\"" << src << "\") "
            << "The src has illegal character. (" << ptr[j] << ')'
            ;
        throw std::invalid_argument(oss.str());
      }
    }
    tmp[0] = value[0] << 2 | value[1] >> 4;
    tmp[1] = value[1] << 4 | value[2] >> 2;
    tmp[2] = value[2] << 6 | value[3];
    std::copy(std::begin(tmp), std::begin(tmp) + j - 1, std::back_inserter(dst));
  }
  return dst;
}

} // namespace hf
