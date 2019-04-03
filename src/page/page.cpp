/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  char *bytestream = new char [PAGE_SIZE];

  in.read(bytestream, PAGE_SIZE);

  int count = in.gcount();

  if (count == 0) return NULL;

  vector<char> new_bytes;

  for (int i = 0; i < count; i++){
    new_bytes.push_back(bytestream[i]);
  }
  return new Page(new_bytes);
}


size_t Page::size() const {
  return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  if (bytes.size() > 0 && offset < bytes.size()) return true;
  return false;
}


char Page::get_byte_at_offset(size_t offset) {
  return bytes.at(offset);
}
