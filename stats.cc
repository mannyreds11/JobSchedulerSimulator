/*
 *  Scheduling Simulator: stats.cc
 *  Author: Manuel Rojas
 */

#include <iostream>
#include "stats.h"

using namespace std;

Statistics::Statistics() 
      {
	JobsEntered = 0;
	JobsFinished = 0;
	UsedCPU = 0.0;

	SumEntered = 0;
	SumFinished = 0;
	SumCPU = 0.0;
      }

Statistics::~Statistics() { }
  
void Statistics::AddToStarved() { JobsStarved++; }

void Statistics::AddToEntered() { JobsEntered++; }

void Statistics::AddToFinished(double used) 
    { 
      JobsFinished++;
      UsedCPU = UsedCPU + used;
    }

void Statistics::Report() 
    {
      cout << " ------------ " << endl;
      cout << "For this iteration" << endl;
      cout << "     Jobs Entered:  " << JobsEntered << endl;
      cout << "     Jobs Finished:  " << JobsFinished << endl;
      cout << "     Jobs Starved : " << JobsStarved << endl;
      cout << "     Completion Percentage: " << 100.0 *((float)JobsFinished)/((float) JobsEntered) << endl;
      cout << "     Completed Jobs Used CPU seconds:  " << UsedCPU << endl; 
    }

void Statistics::DoSums() 
    {
      SumEntered = SumEntered + JobsEntered;
      SumFinished = SumFinished + JobsFinished;
      SumStarved = SumStarved + JobsStarved;
      SumCPU = SumCPU + UsedCPU;
    }

void Statistics::Reset() 
    {
      // reset for next run
      NumberOfRuns++;
      JobsEntered = 0;
      JobsFinished = 0;
      JobsStarved = 0;
      UsedCPU = 0.0;
    }

    
void Statistics::SumReport() 
    {
      //  cout << " ---------------------------------- " << endl;
      //  cout << "After " << NumberOfRuns  << " Runs of the Simulation" << endl;
      //  cout << "     Total Jobs Entered: " << SumEntered << endl;
      //  cout << "     Total Jobs Finished: " << SumFinished << endl;
      //  cout << "     Total CPU seconds used for completed jobs: " << SumCPU << endl;
      //  cout << " -- " << endl;
      cout << "Averages for " << NumberOfRuns;
      if (NumberOfRuns == 1 )
	cout << " iteration:" << endl;
      else
	cout << " iterations:" << endl;
      cout << "      Number of Jobs Entered:   " << SumEntered/NumberOfRuns << endl;
      cout << "      Number of Jobs Completed: " << SumFinished/NumberOfRuns << endl;
      cout << "      Percentage of Jobs Completed:  " << 100.0 * ((float)SumFinished)/((float)SumEntered) << endl;
      cout << "      Number of Starved Jobs: " << SumStarved/NumberOfRuns << endl;
      cout << "      CPU seconds used for completed jobs: " << SumCPU/NumberOfRuns << endl;
    }






