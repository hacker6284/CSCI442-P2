/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "frame/frame.h"
#include "virtual_address/virtual_address.h"
#include "physical_address/physical_address.h"
#include "flag_parser/flag_parser.h"
#include <cstdlib>
#include <queue>
#include <string>
#include <map>


/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:

  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 1 << 9;

// PUBLIC API METHODS
public:

  Simulation(FlagOptions& options);

  /**
   * Runs the simulation.
   */
  void run();

  /**
  * Initialize the simulation
  */
  void init(std::istream& in);

// PRIVATE METHODS
private:

  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char perform_memory_access(const VirtualAddress& address);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handle_page_fault(Process* process, size_t page);

// INSTANCE VARIABLES
private:

  std::queue<VirtualAddress> addresses;
  std::map<int, Process *> process_table;
  std::vector<Frame> frames;
  FlagOptions options;
  int time = 0;

  std::string message = "";
};
