/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"

using namespace std;


/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  //parse flags
  FlagOptions options;
  if (!parse_flags(argc, argv, options)){
    cerr << "Flag parsing failed" << endl;
    return EXIT_FAILURE;
  }

  //initialize input file
  fstream in (options.filename, fstream::in);

  //create the simulation
  Simulation sim = Simulation(options);

  //initialize the simulation with file stream
  sim.init(in);

  //run the simulation
  sim.run();

  //close the file stream
  in.close();
  return EXIT_SUCCESS;
}
