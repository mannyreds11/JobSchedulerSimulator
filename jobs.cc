/*
 *  Scheduling Simulator: jobs.cc
 *  Author: Manuel Rojas
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "jobs.h"
#include "stats.h"

using namespace std;

Statistics S;

#define TRUE (1==1)
#define FALSE (1==0)

static int jobnbr = 0;

void Job::Report() 
    {
    S.Report();
    }

void Job::DoSums() 
    {
      // we need to find all the starved jobs
      struct JobNode *temp;
      temp = JobFront;
      while (temp != NULL) 
		      {
			      if (temp->TimeNeeded == temp->TimeLeft) 
				      {
				      S.AddToStarved();
				      }
			      temp = temp->next;
		      }
      S.DoSums();
    }

void Job::SumReport() {	S.SumReport(); }

// First Come First Served
void Job::FCFS ()
		{
		  JOBNODE temp, FirstJob;

		  temp = JobFront;
		  FirstJob = JobFront;
  
		  while (temp != NULL)
				  {
				    if (temp->TimeEntered < FirstJob->TimeEntered)
						  {
						  FirstJob = temp;
						  }
				    temp = temp->next;
				  }
  
		  CurrentJob = FirstJob;
		  NextJob = CurrentJob;
		}
   

// Round Robin
void Job::RR ()
		{
		  NextJob = CurrentJob;
	  
		  if (NextJob == NULL)
			  NextJob = JobFront;
	  
		  else if (NextJob == JobBack)
						  NextJob = JobFront;
	  
		  else
			    {
			      NextJob = NextJob->next;
			    }
		  CurrentJob = NextJob;
		}
 

//Shortest Job First -- not pre-premptive
void Job::SJF() 
		{
		  JOBNODE temp, shortest;

		  if (CurrentJob != NULL)
		    {
		      NextJob = CurrentJob;
		    }
		  else	{
			  temp = JobFront;
			  shortest = JobFront;
			  
			  while (temp != NULL)
						{
						  if (temp->TimeNeeded < shortest->TimeNeeded)
								{
							shortest = temp;
								}
							temp = temp->next;
						}
			  
			  CurrentJob = shortest;
			  NextJob = CurrentJob;
			}
		}

// Longest Job First -- non-premptive
void Job::LJF() 
    {
      JOBNODE temp, largest;
      
      if (CurrentJob != NULL)
	{
	  NextJob = CurrentJob;
	}

      else
	  {
	    temp = JobFront;
	    largest = JobFront;                    
	    while (temp != NULL)
		  {    
		    if (temp->TimeEntered > largest->TimeNeeded)
		      {
			largest = temp;
		      }
		    temp = temp->next;
		  }
	    CurrentJob = largest;
	    NextJob = CurrentJob;  
	  } 
    }


// SJF - pre-emptive
void Job::SJR() 
    {
      JOBNODE temp, shortest;
      temp = JobFront;
      shortest = JobFront;

      while(temp != NULL)
	    {
	      if (temp->TimeLeft < shortest->TimeLeft)
		{
		  shortest = temp;
		}
	      temp = temp->next;
	    }

      CurrentJob = shortest;
      NextJob = CurrentJob;
    }


// LJF - pre-emptive
void Job::LJR() 
    {
      JOBNODE temp, largest;

      temp = JobFront;
      largest = JobFront;

      while (temp != NULL)
	    {
	      if (temp->TimeLeft > largest->TimeLeft)
		{
		 largest = temp;
		}
	      temp = temp->next;
	    }

      CurrentJob = largest;
      NextJob = CurrentJob;
    }


Job::Job()
    {
      JobFront = NULL;
      JobBack = NULL;
      CurrentJob = NULL;
      NextJob = NULL;
    }

// move current job pointer to the next appropriate job
// according to the selection algorithm specified by N
void Job::GetJob(int N) 
    {
      switch (N)
	    {
	      case 1:
		      FCFS();
		      break;
	      case 2:
		      RR ();
		      break;
	      case 3:
		      SJF ();
		      break;
	      case 4:
		      LJF ();
		      break;
	      case 5:
		      SJR ();
		      break;
	      case 6:
		      LJR ();
		      break;
	      default:
		      cerr <<  "Unknown Algorithm" << endl;
		      exit (1);
	    }
    }




// Job List is empty
bool Job::JobEmpty() { return (JobFront == NULL); }

// No current job exits if this is true
bool Job::CurJobNull() { return (CurrentJob == NULL); }



// for debugging
void Job::printJobList(double thistime) 
    {
      struct JobNode *temp;
      temp = JobFront;
      if (temp != NULL) 
	{
	  cout << "-----------------------" << endl;
	  cout << "Job Number   Time Entered  TimeNeeded TimeLeft  % complete -- current: " << thistime << endl;
	  while (temp != NULL) 
	      {
		if (CurrentJob == temp)
			printf("->");
		else
		    printf("  ");

		    printf("%10d  %10.2f %10.2f %10.2f  %10.2f%%\n",
			    temp->JobNumber,
			    temp->TimeEntered,
			    temp->TimeNeeded,
			    temp->TimeLeft,
			    100.0 - 100.0*(temp->TimeLeft/temp->TimeNeeded)
			  );
		temp = temp->next;
	      }
	}
    }

// for debugging
void Job::LeftInQueue() 
    {
      struct JobNode *temp;
      int starved = 0;
      temp = JobFront;
	
      if (temp != NULL) 
	{
	  cout << "Jobs Remaining in Job Queue:" << endl;
	  cout << "Job Number   Time Entered  TimeNeeded TimeLeft  % complete  "  << endl;
	  while (temp != NULL) 
		{
		  printf("%10d  %10.2f %10.2f %10.2f  %10.2f%%",
			  temp->JobNumber,
			  temp->TimeEntered,
			  temp->TimeNeeded,
			  temp->TimeLeft,
			  100.0 - 100.0*(temp->TimeLeft/temp->TimeNeeded)
			);
		  if (temp->TimeNeeded == temp->TimeLeft) 
			  {
			    starved++;
			    printf(" <-- Starved Job ?");
			  }
		  printf("\n");
		  temp = temp->next;
		}
	  printf("Number of possibly starved jobs: %d\n",starved);
	} 
    }

  
// add a new job to the job queue
void Job::NewJob ( double atTime, double needTime) 
		{
		  struct JobNode *addthis = new struct JobNode;
		  //   addthis = new struct JobNode;
		  addthis->JobNumber = jobnbr++;
		  addthis-> TimeEntered = atTime;
		  addthis->TimeNeeded = needTime;
		  addthis->TimeLeft = needTime;
		  addthis->next = NULL;

		  S.AddToEntered();

		  // add this job to the back of the job queue
		  // the job queue may be empty
		  if (JobFront == NULL) 
		    {
			    JobFront = addthis;
			    JobBack = addthis;
			    // should I set CurrentJob to this also ?  Hmm.
			    CurrentJob = addthis;
			    NextJob = CurrentJob;
		    }
		  else 
		      { // add to the back of the list
			      JobBack->next = addthis;
			      JobBack = addthis;
		      }	
		}

// give the current job a CPU burst  
void Job::Burst(double BurstLength) 
    {
      // give it a shot -- but check to be sure it isn't NULL!

      CurrentJob->TimeLeft = CurrentJob->TimeLeft - BurstLength;


      // note that this may finish the job, so we need to check if we need to
      // remove it from the job queue and if so we must goose the stats

      if (CurrentJob->TimeLeft <= 0.0) 
	{
	  // find the pointer before the current job

	  // do the stats
	  S.AddToFinished(CurrentJob->TimeNeeded);

	  JOBNODE temp;

	  if (JobFront == CurrentJob) 
	    {  // CurrentJob is at the front of the list
	      JobFront = JobFront->next;
	      if (JobFront == NULL)
		JobBack = NULL;
	    }
  
	  else 
	      { // find the CurrentJob  -- it's not the front job
		temp = JobFront;
		while ((temp->next)  != CurrentJob) 
		      {
			temp = temp->next;
		      }	 

		// temp->next should be at CurrentJob

		// if this is JobBack, we could need to be careful
		if (CurrentJob == JobBack) 
		  {
		    temp->next = NULL;
		    JobBack = temp;
		  }
		else // just skip around it
				temp->next = CurrentJob->next;    
	      }
		  
	  // these next to make the simulator find another job
	  CurrentJob = NULL;
	  NextJob = NULL;   
	}
    }
  

void Job::Reset() 
    {
      jobnbr = 0;
      S.Reset();
      JOBNODE temp, temp1;
      temp = JobFront;
      while (temp != NULL) 
	  {
	    temp1 = temp;
	    temp = temp->next;
	    delete temp1;
	  }
      JobFront = NULL;
      JobBack = NULL;
    }

