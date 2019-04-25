# CSCI 442 Project 2

A simulation of a trival OS memory manager.

## Author: Zach Mills

## Contents:

1. *README.md* - This Readme
2. *makefile* - Makefile for the project
3. *src/* - Source directory containing header and code files
4. *googletest/* - directory containing code for google tests
5. *inputs/* - directory containing input files and process source files
6. *inputs/sim_belady* - input file demonstrating Belady's Anomaly

## Unusual / Interesting Features:

Nothing to speak of

## Approximate Time Spent on Project:

**20 Hours**

## Belady's Anomaly

**Belady's Anomaly** is a phenomenon in computer storage wherein certain memory access patterns can cause an increase in page faults with more frames available. It happens when using a *First-In-First-Out* page replacement strategy, when swapping out a page due to space restrictions early on ultimately becomes a valuable decision, as that page is not referenced as soon as other pages.

Using the input file *sim_belady* from the inputs folder, you can see Belady's anomaly in action by running the following two commands:

`./mem-sim -v -f 3 inputs/sim_belady`
`./mem-sim -v -f 4 inputs/sim_belady`

You can see that running the simulation with a smaller number of frames will, in this case, lead to an increased number of page faults. This occurs because certain pages are accessed more often than other pages, and changing the time that the first swap occurs also changes which pages are chosen to be swapped. If a page which is accessed more frequently is unluckily chosen to be swapped because of an additional free frame at the beginning, the overall number of page faults will increase.
