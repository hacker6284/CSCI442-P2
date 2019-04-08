/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"

using namespace std;


void Simulation::run() {
  // TODO: implement me
}

void Simulation::init(std::istream& in) {
  // Set up all the data in the simulation
  int num_processes;
  int process_id;
  string process_file;

  in >> numProcesses;

  for (int i = 0; i < num_processes; i++){
    in >> process_id;
    in >> process_file;

    
  }
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  // TODO: implement me
  return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  // TODO: implement me
}
