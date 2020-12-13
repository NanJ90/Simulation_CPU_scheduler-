#include <iterator>
#include <iostream>
#include "process.h"

/*------FCFS*--------*/
void fcfs(list<process>& processes, int& totalJobs, bool verbose, bool sc_version) { 

	int switching_costs;
	if (sc_version) switching_costs = 5;

	string algName = "First come first serve";

	list<process> readyQ, waitQ, finished;

	int time = 0, complete = 0, idle = 0;

	list <process> :: iterator it; 
	processes.sort();
	process temp;
	process running;

	bool cpu_idle = true;
	
	while (complete < totalJobs) {

        for (it = waitQ.begin(); it != waitQ.end(); ++it) it->ioList.front()--;

		while (!processes.empty()) {
		    if (processes.front().arrivalT <= time) {
		        temp = processes.front();                
		        readyQ.push_back(temp);
		        if (verbose) cout << "Time " << time << ": Process "
		            << temp.p_id << ": arrived -> readyQ.\n";
		        processes.pop_front();
		        continue;
		    } else break;
		} // above loop: push processes into ready queue from new arriving processes

		if (cpu_idle) {
		  if (!readyQ.empty()) { 
		  	if (sc_version) if (running.p_id != readyQ.front().p_id) switching_costs = 5; // v2
		    running = readyQ.front();readyQ.pop_front(); //if idle and a process is ready 
		    if (verbose) cout << "Time " << time << ": Process "
		    	<< running.p_id << ": readyQ -> running.\n";
		    cpu_idle = false;
		  }
          else idle++; 
		} // if cpu_idle 

        time++;

		if (!cpu_idle) {
			if (switching_costs && sc_version) { // v2
				switching_costs--;
			} else
			//no interrupt, current process burst decreasing;
			--running.cpuList.front();
			if (running.cpuList.front() == 0) {
				cpu_idle = true;
				if (verbose) cout << "\nTime " << time 
					<< ": Process " << running.p_id 
					<< ": A cpu burst finished.\n";
				running.cpuList.pop_front();
				if (running.ioList.empty()) {
					if (verbose) cout << "Time " << time 
						<< ": Process " << running.p_id 
						<< ": is complete.\n";
					finished.push_back(running); complete++;
				} else {
					if (verbose) cout << "Time " << time 
						<< ": Process " << running.p_id 
						<< ": running -> waitQ.\n";
					waitQ.push_back(running);					
				}
			} // if (running.cpuList.front() == 0) 
		}// if (!cpu_idle)

       
		waitQ.sort(comp_by_io_remain);

		
		while (!waitQ.empty()) {
			if (waitQ.front().ioList.front() == 0) {
				if (verbose) cout << "Time " << time 
					<< ": Process " << waitQ.front().p_id 
					<< ": waitQ -> readyQ.\n";
				temp = waitQ.front();
				waitQ.pop_front();
				temp.ioList.pop_front();
				readyQ.push_back(temp);
				continue;
			} else break;
		} // above loop: push processes from waitQ -> readyQ
	 
    } // end of top while loop
} // end of fcfs