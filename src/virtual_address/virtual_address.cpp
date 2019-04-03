/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  // set the page
  int pageNum = int(((bitset<ADDRESS_BITS>(address) & bitset<ADDRESS_BITS>(PAGE_BITMASK)) >> OFFSET_BITS).to_ulong());
  // set the offset
  int offsetNum = int((bitset<ADDRESS_BITS>(address) & bitset<ADDRESS_BITS>(OFFSET_BITMASK)).to_ulong());
  return VirtualAddress(process_id, pageNum, offsetNum);
}


string VirtualAddress::to_string() const {
  return bitset<PAGE_BITS>(page).to_string() + bitset<OFFSET_BITS>(offset).to_string();
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  out
    << "PID " << address.process_id << " @ "
    << address.to_string()
    << " [page: " << address.page
    << "; offset: " << address.offset << "]"
    ;
  return out;
}
