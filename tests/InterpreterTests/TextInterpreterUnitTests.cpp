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

#include <gmock/gmock.h>

#include "Interpreter/IInterpreter.hpp"
#include "Interpreter/TextInterpreter.hpp"
#include "Log/Debug.hpp"

#include "mocks/MockIStorage.hpp"

#include <memory>
#include <numeric>
#include <sstream>

using testing::_;
using testing::Return;
using testing::Invoke;

class TextInterpreterMFixture: public testing::Test
{
protected:
  TextInterpreterMFixture()
  {
    DEBUG(testing::UnitTest::GetInstance()->current_test_info()->name() << " BEGIN");
    mock_storage_.reset(new storage::MockIStorage);
    sut_.reset(new interpreter::TextInterpreter(mock_storage_));
  }
  ~TextInterpreterMFixture()
  {
    DEBUG(testing::UnitTest::GetInstance()->current_test_info()->name() << " END with "
      << testing::UnitTest::GetInstance()->current_test_info()->result()->Passed());
  }

  std::shared_ptr<storage::MockIStorage> mock_storage_;
  std::unique_ptr<interpreter::IInterpreter> sut_;
};

TEST_F(TextInterpreterMFixture, returnFalseIfCorruptedData)
{
  std::stringstream data;
  data << "xxx\n" << "yyy\n" << "zzz\n";
  EXPECT_CALL(*mock_storage_, store(_)).Times(0);
  ASSERT_FALSE(sut_->interpret(data));
}

TEST_F(TextInterpreterMFixture, returnTrueAndStoreReduceResult)
{
  std::stringstream data;
  std::vector<float> numbers({1.1, 2.2, 3.3, 4.4, 5.5, 6.6});
  data << "START\n";
  for (auto n : numbers)
  {
    data << n << std::endl;
  }
  data << "REDUCE\n";
  data << "END";
  float expected_result = std::accumulate(numbers.begin(), numbers.end(), 0);
  EXPECT_CALL(*mock_storage_, store(expected_result)).WillOnce(Return(true));
  ASSERT_TRUE(sut_->interpret(data));
}

TEST_F(TextInterpreterMFixture, returnTrueAndStoreBothOperResults)
{
  std::stringstream data;
  float a(0.1), b(-0.1), c(6.9), d(9.6);
  data << "START\n";
  data << a << std::endl;
  data << b << std::endl;
  data << "ADD\n";
  data << c << std::endl;
  data << d << std::endl;
  data << "SUB\n";
  data << "END";
  std::vector<float> results;
  EXPECT_CALL(*mock_storage_, store(_)).WillRepeatedly(Invoke(
    [&results](float f)
    {
      results.push_back(f);
      return true;
    }));
  ASSERT_TRUE(sut_->interpret(data));
  ASSERT_EQ(2, results.size());
  ASSERT_FLOAT_EQ(a+b, results[0]);
  ASSERT_FLOAT_EQ(c-d, results[1]);
}
