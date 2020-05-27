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

#include <gtest/gtest.h>

#include "Storage/IStorage.hpp"
#include "Storage/MySimpleStorage.hpp"
#include "Log/Debug.hpp"

#include <exception>
#include <limits>
#include <memory>

#define MAX_KNOWN_CAPACITY 10

class MySimpleStorageFixture: public testing::Test
{
protected:
  MySimpleStorageFixture()
  {
    DEBUG(testing::UnitTest::GetInstance()->current_test_info()->name() << " BEGIN");
    sut_.reset(new storage::MySimpleStorage);
  }
  ~MySimpleStorageFixture()
  {
    DEBUG(testing::UnitTest::GetInstance()->current_test_info()->name() << " END with "
      << testing::UnitTest::GetInstance()->current_test_info()->result()->Passed());
  }

  std::unique_ptr<storage::IStorage> sut_;
};

TEST_F(MySimpleStorageFixture, returnTrueOnSuccessfullItemStorage)
{
  ASSERT_TRUE(sut_->store(1.1));
  ASSERT_TRUE(sut_->store(2.2));
  ASSERT_TRUE(sut_->store(-1.1));
  ASSERT_TRUE(sut_->store(0));
  ASSERT_TRUE(sut_->store(std::numeric_limits<float>::infinity()));
}

TEST_F(MySimpleStorageFixture, returnFalseWhenStoringExistingElement)
{
  ASSERT_TRUE(sut_->store(1.1));
  ASSERT_FALSE(sut_->store(1.1));
  ASSERT_TRUE(sut_->store(0.2));
  ASSERT_TRUE(sut_->store(0.3));
  ASSERT_TRUE(sut_->store(0.4));
  ASSERT_FALSE(sut_->store(0.2));
  ASSERT_FALSE(sut_->store(0.3));
  ASSERT_FALSE(sut_->store(0.4));
  ASSERT_FALSE(sut_->store(0.2));
  sut_->fetchFirst();
  ASSERT_TRUE(sut_->store(1.1));
  ASSERT_FALSE(sut_->store(1.1));
}

TEST_F(MySimpleStorageFixture, returnFalseWhenStoringMoreThanMaxCapacity)
{
  float element(69.9);
  for (size_t i = 0; i < MAX_KNOWN_CAPACITY; i++)
  {
    ASSERT_TRUE(sut_->store(element)) << "i = " << i;
    element += 0.1;
  }
  ASSERT_FALSE(sut_->store(element));
}

TEST_F(MySimpleStorageFixture, returnCorrectStorageSize)
{
  float element(1.1);
  ASSERT_EQ(0, sut_->size());
  sut_->store(element);
  ASSERT_EQ(1, sut_->size());
  sut_->store(element);
  ASSERT_EQ(1, sut_->size());
  for (size_t i = 0; i < MAX_KNOWN_CAPACITY*2; i++)
  {
    sut_->store(element);
    element += 0.5;
  }
  ASSERT_EQ(MAX_KNOWN_CAPACITY, sut_->size());
  sut_->fetchFirst();
  ASSERT_EQ(MAX_KNOWN_CAPACITY-1, sut_->size());
  sut_->fetchLast();
  ASSERT_EQ(MAX_KNOWN_CAPACITY-2, sut_->size());
  for (size_t i = 0; i < MAX_KNOWN_CAPACITY*2; i++)
  {
    try
    {
      sut_->fetchLast();
    }
    catch (const std::exception& e) {}
  }
  ASSERT_EQ(0, sut_->size());
}

TEST_F(MySimpleStorageFixture, returnCorrectFirstElementsOrThrowIfEmpty)
{
  ASSERT_THROW(sut_->fetchFirst(), std::runtime_error);
  float one(0.1);
  float two(0.2);
  float three(0.3);
  ASSERT_TRUE(sut_->store(one));
  ASSERT_FALSE(sut_->store(one));
  ASSERT_TRUE(sut_->store(two));
  ASSERT_TRUE(sut_->store(three));
  ASSERT_EQ(one, sut_->fetchFirst());
  ASSERT_EQ(two, sut_->fetchFirst());
  ASSERT_EQ(three, sut_->fetchFirst());
  ASSERT_THROW(sut_->fetchFirst(), std::runtime_error);
}

TEST_F(MySimpleStorageFixture, returnCorrectLastElementsOrThrowIfEmpty)
{
  ASSERT_THROW(sut_->fetchLast(), std::runtime_error);
  float one(0.1);
  float two(0.2);
  float three(0.3);
  ASSERT_TRUE(sut_->store(one));
  ASSERT_FALSE(sut_->store(one));
  ASSERT_TRUE(sut_->store(two));
  ASSERT_TRUE(sut_->store(three));
  ASSERT_EQ(three, sut_->fetchLast());
  ASSERT_EQ(two, sut_->fetchLast());
  ASSERT_EQ(one, sut_->fetchLast());
  ASSERT_THROW(sut_->fetchLast(), std::runtime_error);
}
