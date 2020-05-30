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
#pragma once

#include <istream>

namespace interpreter
{

/**
 * Interface to Interpreter which allows to analyze incoming data
 * and can take appropriate action
 */
class IInterpreter
{
public:
  virtual ~IInterpreter() = default;
  /**
   * Reads the data from input stream and takes the action dependent on the data
   * analysis result
   * \param input data stream, input correctness verification is impl defined
   * \return true on successful data interpretation, false if the data is corrupted,
   * or other error occurred
   */
  virtual bool interpret(std::istream& input) = 0;
};

}  // namespace storage
