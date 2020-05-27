/*
 * MIT License
 * 
 * Copyright (c) 2020 Pawel Ptasznik
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include "Storage/MySimpleStorage.hpp"

#include <algorithm>
#include <stdexcept>

namespace storage
{

MySimpleStorage::MySimpleStorage(): max_capacity_(10), storage_()
{
}

MySimpleStorage::~MySimpleStorage()
{
}

bool MySimpleStorage::store(float item)
{
  if (storage_.size() >= max_capacity_) return false;
  if (std::find(storage_.begin(), storage_.end(), item) != storage_.end()) return false;
  storage_.push_back(item);
  return true;
}

size_t MySimpleStorage::size()
{
  return storage_.size();
}

float MySimpleStorage::fetchFirst()
{
  if (storage_.empty()) throw std::runtime_error("fetchFirst on empty Storage");
  float result = storage_.front();
  storage_.pop_front();
  return result;
}

float MySimpleStorage::fetchLast()
{
  if (storage_.empty()) throw std::runtime_error("fetchLast on empty Storage");
  float result = storage_.back();
  storage_.pop_back();
  return result;
}

}  // namespace storage
