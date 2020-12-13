#include <iterator>
#include <iostream>
#include "process.h"

/*-------RR---------*/
void rr(list<process>& processes, int& totalJobs, bool verbose){
    string algName = "Round Robin";

    list<process> readyQ, waitQ, finished;

    int time = 0, complete = 0, idle =0;
    int tq = 10;
    int counter = 0;
    list <process> :: iterator it;
    processes.sort();
    process temp;
    process running;

    bool cpu_idle = true;
     while(complete != totalJobs){
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
            running = readyQ.front(); readyQ.pop_front(); //if idle and a process is ready
            tq=10;
            if (verbose) cout << "Time " << time << ": Process "
                << running.p_id << ": readyQ -> running.\n";
            cpu_idle = false;
          }
          else idle++;
        } // if cpu_idle
         if(readyQ.front().arrivalT == time){
             if(!cpu_idle) readyQ.push_back(running);
             running = readyQ.front(); readyQ.pop_front();
             tq=10;
             if (verbose) cout << "Time " << time << ": Process "
                << running.p_id << ": readyQ -> running.\n";
             //cout<<"At " << time<< " process " <<running.p_id<<" interrupt."<<endl;
             //continue;
         }

        time++;
        if(tq==0){
             if(!readyQ.empty()){
                 readyQ.push_back(running);
                 running = readyQ.front(); readyQ.pop_front();
                 if (verbose) cout << "Time " << time << ": Process "
                << running.p_id << ": readyQ -> running.\n";
             }
             tq=10;
            }
        if (!cpu_idle) {
            --running.cpuList.front();
            --tq;
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
        }
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
    }
    // if (!cpu_idle)

}