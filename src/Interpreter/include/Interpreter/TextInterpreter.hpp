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

#include "Interpreter/IInterpreter.hpp"
#include "Storage/IStorage.hpp"

#include <istream>
#include <memory>
#include <vector>

namespace interpreter
{

/**
 * Interface to Interpreter which allows to analyze incoming data
 * and can take appropriate action
 *
 * For exercise simplicity let's imagine that input data has the form:
 * START
 * [ARG1
 * [ARG2 ...
 * ARGX ...]
 * OPER] ... 
 * END
 * and that the result of each OPER must be stored
 */
class TextInterpreter: public IInterpreter
{
public:
  explicit TextInterpreter(std::shared_ptr<storage::IStorage> storage);
  ~TextInterpreter() override;
  bool interpret(std::istream& input) override;

private:
  float add(const std::vector<float>& args);
  float sub(const std::vector<float>& args);
  float reduce(const std::vector<float>& args);
  std::shared_ptr<storage::IStorage> storage_;
};

}  // namespace storage
