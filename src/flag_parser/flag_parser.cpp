/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>

using namespace std;

bool isNum(std::string line){
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
  bool found_filename = false;
  //Check flags

  for (int i = 1; i < argc; i++){
    if (argv[i][0] == '-'){
      if (argv[i][1] == '-'){
        //double dash
        if (strcmp(argv[i], "--verbose") == 0){
          flags.verbose = true;
        } else if (strcmp(argv[i], "--help") == 0){
          print_usage();
          exit(0);
        } else if (strcmp(argv[i], "--strategy") == 0){
          if (argc > i + 1){
            if (strcmp(argv[i + 1], "LRU") == 0){
              flags.strategy = ReplacementStrategy::LRU;
            } else if (strcmp(argv[i + 1], "FIFO") == 0){
              flags.strategy = ReplacementStrategy::FIFO;
            } else {
              cout << "Unknown strategy: " << argv[i+1] << endl;
              return false;
            }
            i++;
          } else {
            cout << "Incorrect number of arguments 0" << endl;
            return false;
          }
        } else if (strcmp(argv[i], "--max-frames") == 0){
          if (argc > i + 1){
            if (isNum(string(argv[i + 1]))){
              int num = stoi(argv[i + 1]);
              if (num > 0) {
                flags.max_frames = num;
              } else {
                return false;
              }
            } else {
              return false;
            }
            i++;
          } else {
            cout << "Incorrect number of arguments 1" << endl;
            return false;
          }
        }
      } else {
        //single dash
        bool frames_flag = false;
        bool strategy_flag = false;
        for (int j = 1; j < strlen(argv[i]); j++){
          if (argv[i][j] == 'v'){
            flags.verbose = true;
          } else if (argv[i][j] == 'h'){
            print_usage();
            exit(0);
          } else if (argv[i][j] == 's'){
            strategy_flag = true;
            if (!frames_flag){
              if (strcmp(argv[i + 1], "LRU") == 0){
                flags.strategy = ReplacementStrategy::LRU;
              } else if (strcmp(argv[i + 1], "FIFO") == 0){
                flags.strategy = ReplacementStrategy::FIFO;
              } else {
                cout << "Unknown strategy: " << argv[i+1] << endl;
                return false;
              }
            } else {
              cout << "Can't have f and s frames together" << endl;
              return false;
            }
          } else if (argv[i][j] == 'f'){
            frames_flag = true;
            if (!strategy_flag){
              if (argc > i + 1){
                if (isNum(string(argv[i + 1]))){
                  int num = stoi(argv[i + 1]);
                  if (num > 0) {
                    flags.max_frames = num;
                  } else {
                    return false;
                  }
                }
              } else {
                cout << "Incorrect number of arguments 2" << endl;
                return false;
              }
            } else {
              cout << "Incorrect number of arguments 3" << endl;
              return false;
            }
          } else {
            cout << "Can't have f and s frames together" << endl;
            return false;
          }
        }
        if (strategy_flag || frames_flag){
          i++;
        }
      }
    } else {
      flags.filename = argv[i];
      found_filename = true;
    }
  }
  return (found_filename);
}
