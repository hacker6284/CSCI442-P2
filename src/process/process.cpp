/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  vector<Page *> new_pages;
  int num_bytes = 0;

  while (!in.eof()){
    new_pages.push_back(Page::read_from_input(in));
    num_bytes += in.gcount();
  }
  return new Process(num_bytes, new_pages);
}


size_t Process::size() const {
  return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  if (index < pages.size()) return true;
  return false;
}


size_t Process::get_rss() const {
  // TODO: implement me
  return 0;
}


double Process::get_fault_percent() const {
  // TODO: implement me
  return 0.0;
}
