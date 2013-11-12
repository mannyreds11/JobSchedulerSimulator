/*
 *  Scheduling Simulator: events.cc
 *  Author: Manuel Rojas
 */

#include <iostream>
#include "events.h"
using namespace std;

Event::Event() { EventPtr = NULL; }


Event::~Event() { }

void Event::Reset() 
    {
      EVENT *temp, *temp1;
      temp = EventPtr;
      while (temp != NULL) 
			      {
				      temp1 = temp;
				      temp = temp->next;
				      delete temp1;
			      }
      EventPtr = NULL;
    }

bool Event::EventListEmpty(){ return (EventPtr == NULL); }

char Event::GetEventType() { return (EventPtr->etype); }

double Event::GetEventTime() { return (EventPtr->etime); }

void Event::PrintEvents()
    {
      struct EVENT *temp;
      temp = EventPtr;
      while (temp != NULL) 
	  {
		  cout << temp->etype << " at time " << temp->etime << endl;
		  temp = temp->next;
	  }
    }

void Event::ScheduleEvent (char eventtype, double eventtime)
    {
      // This has to add the event to the event list, which is ordered by eventtime
      struct EVENT *temp, *addthis, *old;

      addthis = new struct EVENT;
      addthis->etype = eventtype;
      addthis->etime = eventtime;
      addthis->next = NULL;

      if (EventPtr == NULL)  // the list is empty so ...
	  EventPtr = addthis;
      
      else 
	  { // list is not empty
		  // it goes at the first, in the middle, or at the end
	    if (eventtime < EventPtr->etime) 
	      { // first of list
		      addthis->next = EventPtr;
		      EventPtr = addthis;
	      }
	    else 
		{ 
		  // either in middle or at end
		  // find out where
		  temp = EventPtr;
		  while ((temp != NULL) && (eventtime >= temp->etime)) 
			{
				old = temp;
				temp = temp->next;
			}

		  if (temp == NULL) 
			  {  
				  old->next = addthis; // add to end of list
			  }

		  else 
				  { // add to middle of list
					  addthis->next = temp;
					  temp->next = addthis;
				  }
		}  // of middle or at end
	   }
    }

void Event::RemoveEvent() 
    {
      // This has to remove only the first event.
      // If we believe the hype, just moving the last reference off of the
      // node will delete it.
      EventPtr = EventPtr->next;
    }
 
