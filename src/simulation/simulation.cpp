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

Simulation::Simulation(){
  //constructor
}

void Simulation::run() {

  for (auto p: process_table){
    cout << "Process " << p.first << " size: " << p.second->size() << endl;
  }

  while (!addresses.empty()){
    cout << "Address: " << addresses.front() << endl;
    addresses.pop();
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
    in >> process_id;
    in >> virtual_address;

    addresses.push(VirtualAddress::from_string(process_id, virtual_address));
  }
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  // TODO: implement me
  return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  // TODO: implement me
}
