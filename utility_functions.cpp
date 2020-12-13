#include <string>
#include <fstream>
#include <iostream>
#include "process.h"
using namespace std;

bool operator<(process const & lhs, process const & rhs) {
    return lhs.arrivalT < rhs.arrivalT;
}
bool comp_by_io_remain(process const & lhs, process const & rhs) {
    return lhs.ioList.front() < rhs.ioList.front();
}
bool comp_by_cpu_burst(process const & lhs, process const & rhs) {
    return lhs.cpu_burst < rhs.cpu_burst;
}
bool comp_by_cpu_remain(process const & lhs, process const & rhs) {
    return lhs.cpuList.front() < rhs.cpuList.front();
}

void load_file(int& totalJobs,list<process>& processes, bool verbose) {
    int id, arrival, numbers=0;
    int overheads; 
    ifstream infile;
    infile.open("exampleData.txt");

    infile >> totalJobs >> overheads;
    if (verbose) cout << "Number of processes and overheads " << totalJobs << " " << overheads << endl;

    int cnum, cpu, io;

    for(int i =0;i<totalJobs;i++){
        process p1;
        infile >> id >> arrival >> numbers;
        p1.p_id = id;
        p1.arrivalT = arrival;
        p1.numOfCPU = numbers;
        p1.totalCPUBurst = 0;

        if(verbose) cout<<"From input file: Read process "<<p1.p_id
            <<" that arrives at "<<p1.arrivalT
            <<" with "<<p1.numOfCPU
            <<" bursts.\n";
        
        for(int j =0;j<p1.numOfCPU;j++){
            if(j == p1.numOfCPU-1) {//for last cpu burst and no io burst
                infile >> cnum >> cpu;
            }
            else{
                infile >> cnum >> cpu >> io;
                p1.ioList.push_back(io);
            }
            p1.totalCPUBurst += cpu;          
            p1.cpuList.push_back(cpu);
        }
        //p1.cpu_position = 0;
        //p1.io_position = 0;
        processes.push_back(p1);
    }
    cout << endl;
    infile.close();
} // end of load_file()

void check_arguments(bool& v, bool& d, int argc, char** argv,
   bool& FCFS, bool& SJF, bool& SRTN, bool& RR,int&tq) {

   string argument;

   for (int i = 1; i < argc; ++i) {
       if (argv[i][0] == '-') {
           if (argv[i][1] == 'v') {
               v = true;
           }
       if (argv[i][1] == 'd') {
               d = true;
           }
       }
       argument = argv[i];
       if (argument == "FCFS" || argument == "fcfs") {FCFS = true;}
       if (argument == "SJF"  || argument == "sjf")  {SJF = true;}
       if (argument == "SRTN" || argument == "srtn") {SRTN = true;}
       if (argument == "RR10"   || argument == "rr10" ||
           argument == "RR50"   || argument == "rr50" ||
           argument == "RR100"   || argument == "rr100")   {
        tq = stoi(argument.substr(2));
        //cout << "time quantumn initialize "<<tq<<endl<<endl;
        //printf("time quantumn initialize%i\n",tq);
        RR = true;
      }
   }
   if (
       FCFS == false &&
       SJF == false &&
       SRTN == false &&
       RR == false
       ) {
       FCFS = false;
       SJF = false;
       SRTN = false;
       RR = true;
       // if all false, assume user is unfamiliar
       // and want to see all output
   }
}