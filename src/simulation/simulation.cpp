/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

Simulation::Simulation(FlagOptions& options){
  this->options = options;
  //constructor
}

void Simulation::run() {
  // print each virtual address in the queue
  while (!addresses.empty()){
    //try to perform memory access
    //check that memory address exists
    VirtualAddress address = addresses.front();
    if (!process_table[address.process_id]->is_valid_page(address.page)){
      cerr << "Segmentation Fault" << endl;
      exit(11);
    }
    //if verbose, print the virtual address
    if (options.verbose){
      cout << address << endl;
    }
    //perform the memory access
    message += perform_memory_access(address);

    addresses.pop();
    time++;
  }

  cout << endl << "DONE!" << endl << endl;

  int total_mem_accesses = 0;
  int total_page_faults = 0;
  int free_frames_remaining = NUM_FRAMES;

  for (auto p: process_table){
    cout
    << "Process " << right << setw(3) << p.first << ":  "
    << "ACCESSES: " << left << setw(7) << p.second->memory_accesses
    << "FAULTS: " << setw(7) << p.second->page_faults
    << "FAULT RATE: " << setw(9) << fixed << setprecision(2) << p.second->get_fault_percent()
    << "RSS: " << p.second->get_rss()
    << endl;

    total_mem_accesses += p.second->memory_accesses;
    total_page_faults += p.second->page_faults;
    free_frames_remaining -= p.second->get_rss();
  }

  cout << endl;
  cout << "Total memory accesses: " << setw(15) << right << total_mem_accesses << endl;
  cout << "Total page faults: " << setw(19) << right << total_page_faults << endl;
  cout << "Free frames remaining: " << setw(15) << right << free_frames_remaining << endl;

  cout << "Message: " << message << endl;

}

void Simulation::init(std::istream& in) {
  // Set up all the data in the simulation
  int num_processes;
  in >> num_processes;

  int pid;
  string filename;
  for (int i = 0; i < num_processes; i++){
    in >> pid;
    //initialize new file stream
    in >> filename;
    fstream process_in (filename, fstream::in);
    process_table[pid] = Process::read_from_input(process_in);
    process_in.close();
  }

  int process_id;
  string virtual_address;
  while (!in.eof()){
    process_id = -1;
    in >> process_id;
    in >> virtual_address;
    if (process_id != -1){
      addresses.push(VirtualAddress::from_string(process_id, virtual_address));
    }
  }
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  Process *process = process_table[address.process_id];
  //update memory access counter
  process->memory_accesses++;

  //see if the address is already in virtual memory
  if (process->page_table.rows.at(address.page).present){
    if (options.verbose){
      cout << "  -> IN MEMORY" << endl;
    }
    process->page_table.rows.at(address.page).last_accessed_at = this->time;
  } else {
    handle_page_fault(process, address.page);
  }

  //print physical address and resident set size if verbose
  if (options.verbose){
    cout << "  -> physical address ";
    cout << PhysicalAddress(process->page_table.rows.at(address.page).frame, address.offset) << endl;
    cout << "  -> RSS: " << process->get_rss() << endl << endl;
  }

  if (process->pages.at(address.page)->is_valid_offset(address.offset)){
    return process->pages.at(address.page)->get_byte_at_offset(address.offset);
  } else {
    return 0;
  }
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  //update page fault counter
  process->page_faults++;
  if (options.verbose){
    cout << "  -> PAGE FAULT" << endl;
  }

  //see if there are empty slots
  int frame_num;
  if (process->get_rss() < options.max_frames && frames.size() < NUM_FRAMES){
    frame_num = frames.size();
    frames.push_back(Frame());
  } else {
    //need to swap according to the algorithm
    if (options.strategy == ReplacementStrategy::FIFO){
      //need to swap out oldest
      frame_num = process->page_table.rows.at(process->page_table.get_oldest_page()).frame;
      process->page_table.rows.at(process->page_table.get_oldest_page()).present = false;
    } else {
      //need to swap out least recently accessed
      frame_num = process->page_table.rows.at(process->page_table.get_least_recently_used_page()).frame;
      process->page_table.rows.at(process->page_table.get_least_recently_used_page()).present = false;
    }
  }
  //update page in frame
  frames.at(frame_num).set_page(process, page);
  process->page_table.rows.at(page).present = true;
  process->page_table.rows.at(page).last_accessed_at = time;
  process->page_table.rows.at(page).loaded_at = time;
  process->page_table.rows.at(page).frame = frame_num;
}
