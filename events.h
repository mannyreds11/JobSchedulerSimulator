/*
 *  Scheduling Simulator: events.h
 *  Author: Manuel Rojas
 */

#ifndef EVENT_H
#define EVENT_H
#include <iostream>

class Event 
    {
      public:

      Event();
      ~Event();

      void ScheduleEvent (char eventtype, double eventtime) ;
      bool EventListEmpty() ;
      char GetEventType();
      double GetEventTime();
      void PrintEvents() ;
      void RemoveEvent();
      void Reset();

      private:

      struct EVENT 
	    {
	      char etype;  /* type of event */
	      double etime;  /* time of event */
	      struct EVENT *next;  /* the next event */
	    } *EventPtr ;
    };
	

#endif


