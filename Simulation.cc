/*
 *  Scheduling Simulator: Simulation.cc
 *  Author: Manuel Rojas
 */

#include <iostream>
#include <stdlib.h>
#include "Simulation.h"
#include "events.h"
#include "jobs.h"
#include "random.h"

using namespace std;

Event E;
Job J;
Random R;

int AlgorithmNbr;
double InterArrival;
double ServiceTime;
static double currenttime;
static double CLOCKTICK;
static double finishtime;


bool SHOWQUEUE = false;
bool SHOWEVENTS = false;
bool SHOWEACH = false;


// call to show the job queue after each event 
void Simulation::ShowJobQueue() { SHOWQUEUE = true; }


// call to show the event queue after each event 
void Simulation::ShowEventQueue() { SHOWEVENTS = true; }

// call to show stats after each iteration
void Simulation::ShowEachIteration() { SHOWEACH = true; }

Simulation::~Simulation(){ }

void tick() 
    {  
      /* a clock tick happens */
      double newtime;

      /* schedule the next clock tick */
      newtime = currenttime + CLOCKTICK;

      if (newtime <= finishtime) 
	E.ScheduleEvent('t',newtime);

      /* switch contexts */
      J.GetJob(AlgorithmNbr);
      if ( !J.CurJobNull() ) 
	{
	  /* give this job a time burst */
	  J.Burst(CLOCKTICK);
	}
    }

void arrive() 
    {  
      /* a job enters the job queue */
      double newtime;
      double newneeded;

      /* we first be sure the next job arrival is scheduled */
      newtime = currenttime + R.rnexp(InterArrival);
      E.ScheduleEvent('a',newtime);

      /* now enter this job into the job queue */
      newneeded = R.rnexp(ServiceTime);
      J.NewJob(currenttime ,newneeded);
    }


Simulation::Simulation() 
      {
	float newtime, newneeded;
	currenttime = 0.0;
	newtime = currenttime + R.rnexp(InterArrival);
	newneeded = R.rnexp(ServiceTime);

	/* we first be sure the first job arrival is scheduled */
	E.ScheduleEvent('a',newtime);
	E.ScheduleEvent('t',newtime);
      }


void Simulation::dosim (int Select,
	int ITERATIONS,
	double UARIVE,
	double USERVE,
	double ENDTIME,
	double ticks)
	{
	  CLOCKTICK = ticks;
	  AlgorithmNbr = Select;
	  InterArrival = UARIVE;
	  ServiceTime = USERVE;
	  finishtime = ENDTIME;
	  /* all of the variables have been initialized, and it
		    is time to start a simulation */
	  char etype;
	  int i;

	  for (i = 0; i < ITERATIONS; i++) 
	      {
		      E.Reset();
		      J.Reset();
		      /* we first be sure the first job arrival is scheduled */
		      currenttime = 0.0;
		      double newtime;
		      double newneeded;
		      newtime = currenttime + R.rnexp(InterArrival);
		      newneeded = R.rnexp(ServiceTime);
		      E.ScheduleEvent('a',newtime);
		      E.ScheduleEvent('t',newtime);

		while (currenttime <= ENDTIME) 
		    {
		      if (!E.EventListEmpty()) 
			{
			  etype = E.GetEventType();
			  currenttime = E.GetEventTime();
			  E.RemoveEvent();
			  if (currenttime > ENDTIME) 
				  {
					  // we're done!
				  break;
				  }

			  if (etype == 'a') 
				  {
					  arrive();
				  }

			  else if (etype == 't')
							  tick();
			  else 
			      {
				cerr <<  "error in event queue of type" << etype << endl;
				exit(1);
			      }			  
			}
			
		      else 
			  {
			    cerr << "event list is empty!!" << endl;
			    exit(1);
			  }
		      if (SHOWQUEUE)
			      J.printJobList(currenttime);

		      if  (SHOWEVENTS)
			      E.PrintEvents();
		    }
		    if (SHOWEACH) 
		      {
			J.Report();
			J.LeftInQueue();
		      }
		    J.DoSums();
	    } /* end of iterations list */

	    cout << "Service/Interarrival Ratio: " << ServiceTime/InterArrival << endl;
	    J.SumReport();
	}








