#include <iterator>
#include <iostream>
#include "process.h"

/*------STRN*--------*/
void srtn(list<process>& processes, int& totalJobs, bool verbose,bool sc_version, bool detail) {

	int switching_costs;
	if (sc_version) switching_costs = 5;	

	list<process> readyQ, waitQ, finished;

	int time = 0, complete = 0, idle = 0;

	list <process> :: iterator it; 
	processes.sort();
	process temp;
	process running;

	bool cpu_idle = true;
	bool preempt = false;
	
	while (complete < totalJobs) {

        for (it = waitQ.begin(); it != waitQ.end(); ++it) it->ioList.front()--;

		while (!processes.empty()) {
		    if (processes.front().arrivalT <= time) {
		        temp = processes.front();              
		        readyQ.push_back(temp);
		        if (verbose) cout << "Time " << time << ": Process "
		            << temp.p_id << ": arrived -> readyQ.\n";
		        processes.pop_front();
		        preempt = true; // delta from sjf
		        continue;
		    } else break;
		} // above loop: push processes into ready queue from new arriving processes



		if (preempt == true) { // delta from sjf

			if (cpu_idle) {
				if (!readyQ.empty()) { 
					readyQ.sort(comp_by_cpu_remain); // delta from sjf   
					if (sc_version) if (running.p_id != readyQ.front().p_id) switching_costs = 5; // v2 
					running = readyQ.front();readyQ.pop_front(); //if idle and a process is ready 
					if (verbose) cout << "Time " << time << ": Process "
						<< running.p_id << ": readyQ -> running.\n";
					cpu_idle = false;
				} // else readyQ is empty 
				else idle++; 
			} // if cpu_idle 

			else { // if preempt and cpu not idle:
				if (!readyQ.empty()) { 
					readyQ.push_front(running); // delta from sjf
					if (verbose) cout << "Time " << time << ": Process "
						<< running.p_id << ": running -> readyQ. Preemption attempt.\n";					
					readyQ.sort(comp_by_cpu_remain); // delta from sjf    
					running = readyQ.front();readyQ.pop_front(); //if idle and a process is ready 
					if (verbose) cout << "Time " << time << ": Process "
						<< running.p_id << ": readyQ -> running.\n";
					cpu_idle = false;
			  	}
			}
			preempt = false;
		} // if (preempt == true)

		else // if no preemption request same as sjf 

		if (cpu_idle) {
		  if (!readyQ.empty()) { 
		  	readyQ.sort(comp_by_cpu_remain); // delta from sjf 
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
			--running.cpuList.front();//no interrupt, current process burst decreasing;
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
					running.finishT = time;
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
				preempt = true; // delta from sjf
				continue;
			} else break;
		} // above loop: push processes from waitQ -> readyQ
	 
    } // end of top while loop
    if(detail) details(finished,totalJobs);
    summary(time,idle);
} // end of sjf