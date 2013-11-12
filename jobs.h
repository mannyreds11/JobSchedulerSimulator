/*
 *  Scheduling Simulator: jobs.h
 *  Author: Manuel Rojas
 */

#ifndef JOB_H
#define JOB_H


class Job 
    {
      public:
      Job();

      // move current job pointer to the next appropriate job
      // according to the selection algorithm specified by N
      void GetJob(int N);

      // Job List is empty
      bool JobEmpty();

      // No current job exits if this is true
      bool CurJobNull();

      // for debugging
      void printJobList(double thistime);

      // to show the jobs left in the queue at the end of the job
      void LeftInQueue() ;

      // add a new job to the job queue
      void NewJob ( double atTime, double needTime);

      // give the current job a CPU burst
      void Burst(double BurstLength);

      // reset the counters and empty the job queue for the next iteration
      void Reset();

      // This stuff is to house calls to Statistics

      void Report();
      void DoSums();
      void SumReport();
		
      private:
      typedef struct JobNode {
	      int JobNumber;
	      double TimeEntered;
	      double TimeNeeded;
	      double TimeLeft;
	      struct JobNode *next;  /* the next Job */
      } *JOBNODE;


      // pointer to the the front of the job list
	JOBNODE JobFront;

      // pointer to the back of the job list
	JOBNODE JobBack;

	// pointer to the current job
      JOBNODE CurrentJob;
      // pointer to the next job
      JOBNODE NextJob;

      // Bad design of C++ forces these to be here
      void FCFS();  
      void RR();
      void SJF();
      void LJF();
      void SJR();
      void LJR();

};

#endif




