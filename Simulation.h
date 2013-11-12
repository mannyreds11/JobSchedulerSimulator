/*
 *  Scheduling Simulator: Simulation.h
 *  Author: Manuel Rojas
 */

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation 
		{
		  public:
		  Simulation();
		  ~Simulation();
  

		  void dosim(int Select,
		  int ITERATIONS,
		  double UARIVE,
		  double USERV,
		  double ENDTIME,
		  double ticks);

		  // Set Display parameters
  
		  void ShowJobQueue(); // call to show the job queue after each event
		  void ShowEventQueue(); // call to show the event queue after each event
		  void ShowEachIteration(); // call to show stats after each iteration
		}; 

#endif


