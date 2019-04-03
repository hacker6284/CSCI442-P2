/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"

using namespace std;


string PhysicalAddress::to_string() const {
  //the fist 10 bits should be the frame, the last 6 bits should be the offset
  return bitset<FRAME_BITS>(frame).to_string() + bitset<OFFSET_BITS>(offset).to_string();
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  // should print the string conversion
  out
    << address.to_string()
    << " [frame: " << address.frame
    << "; offset: " << address.offset << "]"
    ;
  return out;
}
