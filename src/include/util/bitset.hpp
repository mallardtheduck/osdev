#ifndef _BITSET_HPP
#define _BITSET_HPP

/*
 * Copyright (c) 2016 drali. All rights reserved.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the author be held liable for any damages arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
 *  2. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 *  3. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 */

//ALTERED FOR BT/OS KERNEL COMPATIBILITY!

// #include <cstring>  // for memcpy
// #include <ostream>

class BitSet {
 public:
  // Empty bit set
  BitSet() = default;

  // Allocated, but no bits set
  BitSet(const size_t size) {
    allocated_ = (size >> 3) + 1;
    bits_ = new unsigned char[allocated_];
    size_ = size;
  }

  ~BitSet() {
    if (bits_ != nullptr) {
      delete [] bits_;
      bits_ = nullptr;
    }
  }

  BitSet(const BitSet& rhs) : allocated_(rhs.allocated_), size_(rhs.size_) {
    if (allocated_ != 0) {
      bits_ = new unsigned char[allocated_];
      memcpy(bits_, rhs.bits_, (size_ >> 3) + 1);
    }
  }

  BitSet& operator=(const BitSet& rhs) {
    if (this != &rhs) {
      allocated_ = rhs.allocated_;
      size_ = rhs.size_;
      bits_ = new unsigned char[allocated_];
      memcpy(bits_, rhs.bits_, (size_ >> 3) + 1);
    }
    return *this;
  }

  BitSet(BitSet&& rhs) {
    if (this == &rhs) { return; }
    allocated_ = rhs.allocated_;
    bits_ = rhs.bits_;
    size_ = rhs.size_;
    rhs.allocated_ = 0;
    rhs.bits_ = nullptr;
    rhs.size_ = 0;
  }

  BitSet& operator=(BitSet&& rhs) {
    if (this == &rhs) { return  *this; }
    allocated_ = rhs.allocated_;
    bits_ = rhs.bits_;
    size_ = rhs.size_;
    rhs.allocated_ = 0;
    rhs.bits_ = nullptr;
    rhs.size_ = 0;
    return *this;
  }

  void Set(const size_t position) {
    bits_[position >> 3] |= (1 << (position & 0x7));
  }
  
  void UnSet(const size_t position) {
    bits_[position >> 3] &= ~(1 << (position & 0x7));
  }
  
  void Set(const size_t position, bool value) {
    if(value) Set(position);
    else UnSet(position);
  }

  // Returns number of bits
  size_t GetSize() const {
    return size_;
  }

  bool IsSet(const size_t position) const {
    return (bits_[position >> 3] & (1 << (position & 0x7))) != 0;
  }
  
  unsigned char *GetBits(){
  	return bits_;
  }
  
  void SetBits(void *data, size_t size){
  	if(size == size_) memcpy(bits_, data, (size_ >> 3) + 1);
  }

  //friend std::ostream& operator<<(std::ostream& out, const BitSet& bit_set) {
  //  for (size_t i = 0; i < bit_set.size_; ++i) {
  //    out << bit_set.IsSet(i);
  //  }
  //  out << std::endl;
  //  return out;
  //}

 private:
  unsigned char* bits_ = nullptr;

  // Bytes allocated
  size_t allocated_ = 0;

  // Number of bits
  size_t size_ = 0;
};

#endif