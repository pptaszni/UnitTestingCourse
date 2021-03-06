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

#include "Interpreter/TextInterpreter.hpp"
#include "Storage/IStorage.hpp"
#include "Log/Debug.hpp"

#include <algorithm>
#include <numeric>
#include <istream>
#include <memory>
#include <string>

namespace interpreter
{

TextInterpreter::TextInterpreter(std::shared_ptr<storage::IStorage> storage):
  storage_(storage)
{
}

TextInterpreter::~TextInterpreter()
{
}

bool TextInterpreter::interpret(std::istream& input)
{
  std::string line;
  std::getline(input, line);
  if (line != "START")
  {
    DEBUG("Corrupted data start: " << line);
    return false;
  }
  std::vector<float> args;
  while (line != "END")
  {
    std::getline(input, line);
    if (line == "ADD")
    {
      storage_->store(add(args));
      args.clear();
    }
    else if (line == "SUB")
    {
      storage_->store(sub(args));
      args.clear();
    }
    else if (line == "REDUCE")
    {
      storage_->store(reduce(args));
      args.clear();
    }
    else if (line == "END") break;
    else
    {
      try
      {
        args.push_back(std::stof(line));
      }
      catch (const std::exception& e)
      {
        DEBUG("Failed to parse arg: " << e.what());
        return false;
      }
    }
  }
  return true;
}

float TextInterpreter::add(const std::vector<float>& args)
{
  return args[0]+args[1];
}

float TextInterpreter::sub(const std::vector<float>& args)
{
  return args[0]-args[1];
}

float TextInterpreter::reduce(const std::vector<float>& args)
{
  return std::accumulate(args.begin(), args.end(), 0);
}

}  // namespace storage
