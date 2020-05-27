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

#include <cstddef>

namespace storage
{

/**
 * Interface for Storage utility allowing to save unique elements in the order of arrival
 */
class IStorage
{
public:
  virtual ~IStorage() = default;
  /**
   * Saves the element `item`
   * \param item the element to be stored
   * \return true on success, false on failure (you might explain possible failure reasons)
   */
  virtual bool store(float item) = 0;
  /**
   * \return number of elements currently stored
   */
  virtual size_t size() = 0;
  /**
   * Removes the first element from the storage and returns it
   * \return first stored element
   * \throw std::runtime_error if the Storage is empty or some other problem occurs
   */
  virtual float fetchFirst() = 0;
  /**
   * Removes the last element from the storage and returns it
   * \return last stored element
   * \throw std::runtime_error if the Storage is empty or some other problem occurs
   */
  virtual float fetchLast() = 0;
};

}  // namespace storage
