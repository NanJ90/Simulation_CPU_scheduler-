#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include <iterator>
//#include <bits/stdc++.h>
#include "functions.h"

using namespace std;


const string stauts[] = { "new", "read","wait","run","execute" }; // 0 1 2 3 4

struct process {
    int p_id;
    int numOfCPU;
    int arrivalT;
    int finishT;
    int serviceT;
    int tatT;
    int cpu_position;
    int io_position;
    int cpu_burst;
    int io_burst;
    bool running = false;
    list<int> cpuList;
    list<int> ioList;
};

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
        if(verbose) cout<<"Process "<<p1.p_id<<" is arrived at "<<p1.arrivalT<<" with "<<p1.numOfCPU<<endl;
        
        for(int j =0;j<p1.numOfCPU;j++){
            if(j == p1.numOfCPU-1) {//for last cpu burst and no io burst
                infile >> cnum >> cpu;
            }
            else{
                infile >> cnum >> cpu >> io;
                p1.ioList.push_back(io);
            }
            p1.cpuList.push_back(cpu);
        }
        p1.cpu_position = 0;
        p1.io_position = 0;
        processes.push_back(p1);
    }
    infile.close();

}
bool operator<(process const & lhs, process const & rhs) {return lhs.arrivalT < rhs.arrivalT;}
/*------FCFS*--------*/
void fcfs(list<process>& processes, int& totalJobs, bool verbose){
    string algName = "First come first serve";

    list<process> readyQ, waitQ;
    int time = 0, complete = 0, idle =0;
    //bool cpu_idle;

    list <process> :: iterator it; 
    processes.sort();
    process temp;
    
    while(complete != totalJobs){

      while(!processes.empty()) {
        if (processes.front().arrivalT <= time) {
          temp = processes.front();
          readyQ.push_back(temp);
          if (verbose) cout << "At time: " << time << ", pushed process "
            << temp.p_id << " into readyQ.\n";
          processes.pop_front();
          continue;
        } else break;
      } // above loop: push processes into ready queue from new arriving processes

      time++;

      if(readyQ.front().cpu_burst == 0 && readyQ.front().io_burst == 0){

            int *cpuBurst =&readyQ.front().cpu_burst, *ioBurst = &readyQ.front().io_burst;
            list<int> *cpuList = &readyQ.front().cpuList;
            list<int> *ioList = &readyQ.front().ioList;
            
            if(cpuList->empty() && ioList->empty()) {//once complete a process execution
                complete++;
                process *p;
                p = &readyQ.front();
                p->finishT = time;
                //processes.push_back(*p);//push back to processes list
                if (verbose) cout<<"process "<<p->p_id<<" at "<<time<<" has completed."<<endl<<endl;
                readyQ.pop_front();
                continue;
            };
            //if process is ready to execute
            if(!readyQ.front().running) {
                readyQ.front().running= true;
                if (verbose) cout<<"at time "<<time-1<<" process "<<readyQ.front().p_id<<" is runnning"<<endl;
                *cpuBurst = cpuList->front()-1;
                cpuList->pop_front();
            }
            else{// finish one cpu burst and move to waiting queue
                readyQ.front().running = false;
                if (verbose) cout<<"at time "<<time<<" process "<<readyQ.front().p_id<<" is start to wait"<<endl;
                *ioBurst = ioList->front();
                ioList->pop_front();
                waitQ.push_back(readyQ.front());
                readyQ.pop_front();
            }
            
        }
        
        if(!readyQ.empty() && readyQ.front().running){
            readyQ.front().cpu_burst--;
        }
        //else idle++;
        if(!waitQ.empty()){
            for(auto it = waitQ.begin(); it !=waitQ.end();it++){
                if(it->io_burst == 0) {
                    readyQ.push_back(*it);
                    waitQ.pop_front();
                }
                it->io_burst--;
            }
        }
        if(readyQ.empty()) idle++;
       //if(!readyQ.front().running &&)
       
    }
//    summary(algName,current,idletime);
}
//void display() {
//    cout << "The is process has  " << p_id << " " << numOfCPU << " " << arrivalT << endl;
//    cout << "process " << p_id << "has cpu and io " << endl;
//    for (int i = 0; i < numOfCPU; i++) {
//        cout << cpuList[i].burstT << " " << ioList[i].burstT << endl;
//    }
//}

//struct compareArrival
//{
//    inline bool operator() (const process& p1, const process& p2)
//    {
//        return (p1.arrivalT < p2.arrivalT);
//    }
//};
//
//bool compareJobsT(process a, process b) {
//    if(a.arrivalT == b.arrivalT)
//    { return a.cpuList[a.currentC].burstT < b.cpuList[b.currentC].burstT;}
//    return a.arrivalT < b.arrivalT;
//};
//bool compareJobsTio(process a, process b) {
//    if (a.status == 2 && b.status == 2){
//        if(a.iotime == b.iotime)
//        { return a.cpuList[a.currentC].burstT < b.cpuList[b.currentC].burstT;}
//        else return a.iotime < b.iotime;
//    }
//    return 0;
//};
//void summary(string alg,int cur,int idle);
//void fcfs(vector<process>, int);
//void sjf(vector<process>, int);

int main(int argc, char** argv) {

    bool verbose = false;
    bool detail_output = false;

    bool FCFS = false;
    bool SJF = false;
    bool SRTN = false;
    bool RR = false;
    int totalJobs = 0;
    check_arguments(verbose, detail_output, argc, argv, FCFS, SJF, SRTN, RR);
    list<process> processes;
    load_file(totalJobs,processes,verbose);
//    for(auto it = processes.begin(); it!=processes.end();it++){ //print out each process
//        cout<<"Process "<<it->p_id<<endl;
//        for(auto j = it->cpuList.begin();j!=it->cpuList.end();j++){
//            cout<<"cpu "<<*j<<endl;
//        }
//    }

    fcfs(processes, totalJobs, verbose);
//    sjf(processes,totalJobs);
//    /*------SRTN------*/
//    vector<process> ready;
//    ready = processes;
//    int current=0, idleT=0, mins = INT_MAX, complete = 0, shortest = 0;
//    while(complete != totalJobs){
//        for(int i = 0;i< totalJobs;i++){
//            if(processes[i].arrivalT <= current){
//                //mins = processes[i].cpuList[processes[i].currentC].burstT;
//                shortest = i;
//                //ready.push_back(processes[i]);
//            }
//            ready[shortest].cputime = processes[i].cpuList[processes[i].currentC].burstT-current;
//            if(ready[shortest].cpuList[ready[shortest].currentC].finish == true && ready[shortest].ioList[ready[shortest].currentC].isio == true){
//                ready[shortest].iotime = ready[shortest].ioList[ready[shortest].currentC].burstT-current;
//
//            }
//            mins = ready[shortest].cpuList[ready[shortest].currentC].remainT;
//            if(mins == 0) mins = INT_MAX;
//            current++;
//
//        }
//
//    }
   
    return 0;
}
//void summary(string alg,int current, int idletime){
//    double cpuUtilization=0.0;
//    cpuUtilization =static_cast<double>(current-idletime)/static_cast<double>(current)*100.0;
//    cout<<alg<<endl;
//    cout<<"Total time required is " << current << " time units"<<endl;
//    cout<< "the cpu utilization is "<< (int)cpuUtilization<<"%"<<endl<<endl;
//}

///*------SJF*--------*/
//void sjf(vector<process>processes, int totalJobs){
//    string algName = "Shortest Job First";
//    vector<process> readyQ, executeArr;
//    readyQ = processes;
//    //sorting by cpu time if they arrive at the same time
//    sort(readyQ.begin(), readyQ.end(), compareJobsT);
//    for (int i = 0; i < totalJobs; i++) {
//        readyQ[i].status = 1;
//    }
//    int cTime = readyQ[0].arrivalT;
//    int iTime = readyQ[0].arrivalT;
//    int current = 0;
//    int idletime = 0;
//
//    while (readyQ[0].status == 1 && !readyQ.empty()) {
//        //checking unarrival process
//        if(readyQ[0].arrivalT > current) {
//            idletime += readyQ[0].arrivalT- cTime;
//            cTime = readyQ[0].arrivalT;
//            readyQ[0].status=1;
//        }
//        //sort(readyQ.begin(), readyQ.end(),compareJobsT);
//        int i = readyQ[0].currentC;
//        readyQ[0].status = 3; //running
//        //update cpu time, io time and current time;
//        cTime += readyQ[0].cpuList[i].burstT;
//        current = cTime;
//        iTime = current + readyQ[0].ioList[i].burstT;
//        readyQ[0].cputime = cTime;
//        readyQ[0].iotime = iTime;
//        readyQ[0].status = 2;
//        i++; //update cpu counter in a process
//        readyQ[0].currentC = i;
//
//        if (readyQ[0].currentC == readyQ[0].numOfCPU) {//process completed
//            readyQ[0].status = 4; //prcess completed
//            readyQ[0].finishT = current;
//            readyQ[0].tatT = readyQ[0].finishT - readyQ[0].arrivalT;
//            readyQ[0].wait = readyQ[0].tatT - readyQ[0].serviceT-readyQ[0].iotimeB;
//            executeArr.push_back(readyQ[0]);
//
//            readyQ.erase(readyQ.begin());
//            sort(readyQ.begin(), readyQ.end(), compareJobsTio);
//            readyQ[0].status = 1;
//            if(cTime < readyQ[0].iotime) {
//                cTime = readyQ[0].iotime;
//                idletime+=readyQ[0].iotime - current;
//            }
//            continue;
//        }
//        if (cTime < readyQ[1].iotime) {
//            sort(readyQ.begin(), readyQ.end(), compareJobsTio);//if io same shortest job first.
//            //overheadsCount++;
//            idletime += readyQ[0].iotime - current;
//            cTime = readyQ[0].iotime;
//            readyQ[0].status = 1;
//            //readyQ[0].idle = true;
//
//        }
//        else {
//            readyQ[1].status = 1;
//            rotate(readyQ.begin(), readyQ.begin() + 1, readyQ.end());
//            //overheadsCount++;
//        }
//
//    }
//    summary(algName,current, idletime);
//}

// void check_arguments(bool& v, bool& d, int argc, char** argv,
//    bool& FCFS, bool& SJF, bool& SRTN, bool& RR) {

//    string argument;

//    for (int i = 1; i < argc; ++i) {
//        if (argv[i][0] == '-') {
//            if (argv[i][1] == 'v') {
//                v = true;
//            }
//        if (argv[i][1] == 'd') {
//                d = true;
//            }
//        }
//        argument = argv[i];
//        if (argument == "FCFS" || argument == "fcfs") {FCFS = true;}
//        if (argument == "SJF"  || argument == "sjf")  {SJF = true;}
//        if (argument == "SRTN" || argument == "srtn") {SRTN = true;}
//        if (argument == "RR"   || argument == "rr")   {RR = true;}
//    }
//    if (
//        FCFS == false &&
//        SJF == false &&
//        SRTN == false &&
//        RR == false
//        ) {
//        FCFS = true;
//        SJF = true;
//        SRTN = true;
//        RR = true;
//        // if all false, assume user is unfamiliar
//        // and want to see all output
//    }
// }

//void detail(){
//    //calculate TAT and cpu utilization and idle time
//    int totalTat = 0, totalWait=0;
//
////    for(int i = 0;i<totalJobs;i++){
////        totalTat += executeArr[i].tatT;
////        totalWait += executeArr[i].wait;
////    }
////
////    cout << "the average tat is " <<totalTat/totalJobs<<endl;
////    cout << "the average wait is " <<totalWait/totalJobs<<endl;
//
//}
