/*
 *  Scheduling Simulator: stats.h
 *  Author: Manuel Rojas
 */

#ifndef STATS_H
#define STATS_H

class Statistics 
    {
      // contains various statistics

      public:

      ///create and initialize statistics
      Statistics();
      ~Statistics();


      void AddToEntered(); // increment a counter that tells how many jobs
			  // were entered

      void AddToFinished(double used) ; // a job finished; add to all the counters as needed


      void AddToStarved() ; // a job may have starved

      void Report();   // report on this run
      void SumReport(); // summary for all runs

      // reset some counters
      void Reset();

      // increment all sums
      void DoSums();


      private:
      int JobsEntered;  // for this run
      int JobsFinished; // for this run
      double UsedCPU;   // for this run
      int JobsStarved;  // for this run

      int SumEntered ;  // for all runs
      int SumFinished ; // for all runs
      double SumCPU ;  // for all runs
      int SumStarved;  // for all runs


      int NumberOfRuns ; // how many runs
  
};



#endif

