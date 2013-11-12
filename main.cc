#include <iostream>
#include <stdlib.h>
#include "Simulation.h"
using namespace std;

#define TRUE (1==1)
#define FALSE (1==0)

int main(int argc, char *argv[])
{  

	char *d;      /* a character pointer */
	char tempstr[20];  /* a temporary string */

	int j; /* a counter */
	int argnbr;
	Simulation Sim;


	// set up defaults
	int Select = 1; // Round Robin
	
	double ENDTIME = 3600.0;	/* run for 3600 seconds default */
	double UARIVE = 50.0;		/* average interarrival time default 50 sec */
	double USERVE = 20.0;		/* average service time default 20 sec */
	double CLOCKTICK = 1.0;         /* length of a clock tick */

	int ITERATIONS = 1;	/* default number of runs */
	bool SHOWPARMS = TRUE;	/* do show parameters at first of run */
	bool SHOWQUEUE = FALSE;	/* do not show the job queue after each tick */
	bool SHOWEACH = FALSE;	/* do not show statistics of each iteration */
	bool SHOWEVENTS = FALSE;	/* show event list each time it changes */


	/* skip the first argument, since it is meaningless */
	argc--;
	argv++;

	/* now process the remaining arguments until there are no more */

	argnbr = 0;         /* number of non-switch arguments */
	while (argc > 0 ) {
		d = argv[0];
		if (*d == '-') {
			/* its a switch */
			d++;     /* skip the '-' */
			while (*d != '\0') {
			     switch(*d) {
				case 'a': /* interarrival time */
				case 'A': /* either of form -nXXX
						or of form -n XXX */

					if (*(d+1) != '\0') {
						j = 0;
						d++;
						while (*d != '\0') {
							tempstr[j] = *d;
							j++;
							d++;
						}
						tempstr[j] = '\0';
						UARIVE = atof(tempstr);
						d--;
					}
					else {
						argc--;
						argv++;
						UARIVE = atof(argv[0]);
					}
					break;

			     case 'c': /* length of clock tick */
			     case 'C': /* either of form -nXXX
						or of form -n XXX */

					if (*(d+1) != '\0') {
						j = 0;
						d++;
						while (*d != '\0') {
							tempstr[j] = *d;
							j++;
							d++;
						}
						tempstr[j] = '\0';
						CLOCKTICK = atof(tempstr);
						d--;
					}
					else {
						argc--;
						argv++;
						CLOCKTICK = atof(argv[0]);
					}
					break;


				case 'e':
				case 'E':  /* show event list */
					SHOWEVENTS = !SHOWEVENTS;
					break;


				case 'j':
				case 'J':  /* select scheduling algorithm */

					if (*(d+1) != '\0') {
						j = 0;
						d++;
						while (*d != '\0') {
							tempstr[j] = *d;
							j++;
							d++;
						}
						tempstr[j] = '\0';
						Select = atoi(tempstr);
						d--;
					}
					else {
						argc--;
						argv++;
						Select = atoi(argv[0]);
					}
					break;


				case 'n': /* number of iterations */
				case 'N': /* either of form -nXXX
						or of form -n XXX */

					if (*(d+1) != '\0') {
						j = 0;
						d++;
						while (*d != '\0') {
							tempstr[j] = *d;
							j++;
							d++;
						}
						tempstr[j] = '\0';
						ITERATIONS = atoi(tempstr);
						d--;
					}
					else {
						argc--;
						argv++;
						ITERATIONS = atoi(argv[0]);
					}
					break;

			     case 'p':
				/* don't show parameters */
				      SHOWPARMS = false;
				      break;
					
					
				case 'q':
				case 'Q':  /* show job queue */
					SHOWQUEUE = !SHOWQUEUE;
					break;

				case 's':  /* service time */
				case 'S': /* either of form -nXXX
						or of form -n XXX */

					if (*(d+1) != '\0') {
						j = 0;
						d++;
						while (*d != '\0') {
							tempstr[j] = *d;
							j++;
							d++;
						}
						tempstr[j] = '\0';
						USERVE = atof(tempstr);
						d--;
					}
					else {
						argc--;
						argv++;
						USERVE = atof(argv[0]);
					}
					break;

				case 't':  /* end time */
				case 'T': /* either of form -nXXX
						or of form -n XXX */

					if (*(d+1) != '\0') {
						j = 0;
						d++;
						while (*d != '\0') {
							tempstr[j] = *d;
							j++;
							d++;
						}
						tempstr[j] = '\0';
						ENDTIME = atof(tempstr);
						d--;
					}
					else {
						argc--;
						argv++;
						ENDTIME = atof(argv[0]);
					}
					break;
				
				case 'v':  /* show stats each iteration */
				case 'V':
					SHOWEACH = !SHOWEACH;
					break;




			     default :  
			       cout << "unknown switch " << *d << endl;
			       
			     case 'h':
			       cout << "usage: a.out "  << " [options]" << endl;
			       cout << "options == " << endl;
			       cout << "\t-a #\tinterarrival time" << endl;
			       cout << "\t-e  \tshow event queue" << endl;
			       cout << "\t-h  \tshow this help" << endl;
			       cout << "\t-j #\tselect scheduling algorithm [1 ...]" << endl;
                               cout << "\t       1 -- First Come First Served" << endl;
			       cout << "\t       2 -- Round Robin" << endl;
			       cout << "\t       3 -- Shortest Job First " << endl;
			       cout << "\t       4 -- Longest Job First " << endl;
			       cout << "\t       5 -- Shortest Job Remaining " << endl;
			       cout << "\t       6 -- Longest Job Remaining" << endl;
			       cout << "\t-n #\tnumber of iterations" << endl;
			       cout << "\t-p  \tdo not show parameters" << endl;
			       cout << "\t-q  \tshow job queue" << endl;
			       cout << "\t-s #\tservice time" << endl;
			       cout << "\t-t #\tending time" << endl;
			       cout << "\t-v  \tshow stats each iteration" << endl;
				  exit(0);
				  break;

				}  /* end of switch */

				d++;    /* move to next character */

			} /* of while */

		}

		else {

			/* its not a switch */
		  cerr << "unknown command line argument" << argv[0] << endl;
			exit(1);


		}

		/* move to next argument */

		argc--;

		argv++;

	}  /* of while */




	if (SHOWQUEUE)
	  Sim.ShowJobQueue();

	if (SHOWEACH)
	  Sim.ShowEachIteration();

	if (SHOWEVENTS)
	  Sim.ShowEventQueue();

	if (SHOWPARMS) {
	  cout << "===============================" << endl;
	  switch(Select) {
	  case 1: cout << "First Come First Served ";
            break;
	  case 2: cout << "Round Robin Algorithm  " ;
	    break;
	  case 3:
	    cout << "Shortest Job First Algorithm ";
	    break;
	  case 4:
	    cout << "Longest Job First Algorithm ";
	    break;
	  case 5:
	    cout << "Shortest Job Remaining Algorithm ";
	    break;
	  case 6:
	    cout << "Longest Job Remaining Algorithm ";
	    break;
	  }
	  cout << "Parameters: " << endl;
	  cout << "    Service Time: " << USERVE << endl;
	  cout << "    Interarrival Time: " << UARIVE << endl;
	  cout << "    S/A Ratio : " << USERVE/UARIVE << endl;
	  cout << "    Simulation length:  " << ENDTIME << endl;
	  cout << "    Clock Tick: " << CLOCKTICK << endl;
	  //	  cout << "    Iterations: " << ITERATIONS << endl;
	  cout << endl;
	}
	
	  
	
	
	Sim.dosim(Select,ITERATIONS,UARIVE,USERVE,ENDTIME,CLOCKTICK);

} /* of main */




