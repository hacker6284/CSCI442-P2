/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
  size_t count = 0;
  for (Row r: rows){
    count += r.present;
  }
  return count;
}


size_t PageTable::get_oldest_page() const {
  size_t early_time = -1;
  size_t early_row = -1;

  for (size_t i = 0; i < rows.size(); i++){
    if (rows[i].present && early_row == -1){
      early_time = rows[i].loaded_at;
      early_row = i;
    }
    if (rows[i].present && rows[i].loaded_at < early_time){
      early_time = rows[i].loaded_at;
      early_row = i;
    }
  }
  return early_row;
}


size_t PageTable::get_least_recently_used_page() const {
  size_t early_time = -1;
  size_t early_row = -1;

  for (size_t i = 0; i < rows.size(); i++){
    if (rows[i].present && early_row == -1){
      early_time = rows[i].last_accessed_at;
      early_row = i;
    }
    if (rows[i].present && rows[i].last_accessed_at < early_time){
      early_time = rows[i].last_accessed_at;
      early_row = i;
    }
  }
  return early_row;
}
