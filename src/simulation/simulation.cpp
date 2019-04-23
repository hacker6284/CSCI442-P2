/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include <iostream>
#include <fstream>

using namespace std;

Simulation::Simulation(FlagOptions& options){
  this->options = options;
  //constructor
}

void Simulation::run() {

  // print all of the processes in the process table
  for (auto p: process_table){
    cout << "Process " << p.first << ": " << p.second->size()  << " bytes"<< endl;
  }

  // print each virtual address in the queue
  while (!addresses.empty()){
    //try to perform memory access

    //check that memory address exists
    VirtualAddress address = addresses.front();
    if (!process_table[address.process_id]->is_valid_page(address.page)){
      cerr << "Segmentation Fault" << endl;
      exit(11);
    }

    //perform the memory access
    perform_memory_access(address);


    addresses.pop();
    time++;
  }
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
  //see if the address is already in virtual memory
  Process *process = process_table[address.process_id];
  if (process->page_table.rows.at(address.page).present){
    process->page_table.rows.at(address.page).access_time = this->time;
  } else {
    handle_page_fault(process, address.page);
  }


  if (process->pages.at(address.page)->is_valid_offset(address.offset)){
    return process->pages.at(address.page)->get_byte_at_offset(address.offset);
  } else {
    return 0;
  }
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  // TODO: implement me
}
