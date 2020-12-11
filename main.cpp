#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include "functions.h"

using namespace std;

// void check_arguments(bool&, bool&, int, char**, bool&, bool&, bool&, bool&);

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
    int *cpuList;
    int *ioList;
};


void load_file(bool verbose) {
    int id, arrival, numbers=0;
    int totalJobs,overheads;
    ifstream infile;
    infile.open("exampleData.txt");

    infile >> totalJobs >> overheads;
    if (verbose) cout << "Number of processes and overheads " << totalJobs << " " << overheads << endl;
    
    queue <process> processes;

    int cnum, cpu, io; string line;

    for(int i =0;i<totalJobs;i++){
        process p1;
        infile >> id >> arrival >> numbers;
        p1.p_id = id;
        p1.arrivalT = arrival;
        p1.numOfCPU = numbers;
        p1.cpuList = new int[p1.numOfCPU];
        p1.ioList = new int[p1.numOfCPU-1];
        if(verbose) cout<<"Process "<<p1.p_id<<" is arrived at "<<p1.arrivalT<<" with "<<p1.numOfCPU<<endl;
        for(int i = 0; i< p1.numOfCPU;i++) {// initialize cpu burst array
            p1.cpuList[i] = 0;
        }
        for(int i = 0; i< p1.numOfCPU-1;i++) {// initialize io burst array
            p1.ioList[i] = 0;
        }
        
        for(int j =0;j<p1.numOfCPU;j++){
            if(j == p1.numOfCPU-1) {//for last cpu burst and no io burst
                infile >> cnum >> cpu;
                p1.ioList[j] = 0;
            }
            else{
                infile >> cnum >> cpu >> io;
                p1.ioList[j] = io;
            }
            p1.cpuList[j] = cpu;
        }
        p1.cpu_position = 0;
        p1.io_position = 0;
        processes.push(p1);
    }
    infile.close();
//    while(!processes.empty()){//testing processes adding to the queue
//        int i = 0;
//        while (i < processes.front().numOfCPU){
//            cout << processes.front().cpuList[i]<<endl;
//            i++;
//        }
//        processes.pop();
//    }
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

    check_arguments(verbose, detail_output, argc, argv, FCFS, SJF, SRTN, RR);

    int totalJobs=0, overheads=0;
    int id, arrival, numbers=0;
    load_file(verbose);
    

//    fcfs(processes,totalJobs);
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
/*------FCFS*--------*/
//void fcfs(vector<process>processes, int totalJobs){ //nesting loops
//    string algName = "First come first serve";
//    //sorting process in processes by arrvial time in ready Q
//    vector<process> readyQ, executeArr;
//    readyQ = processes;
//    sort(readyQ.begin(), readyQ.end(), compareArrival());
//
//    for (int i = 0; i < totalJobs; i++) {
//        readyQ[i].status = 1;
//    }
//    int cTime = readyQ[0].arrivalT;
//    int iTime = readyQ[0].arrivalT;
//    int current = 0;
//    int idletime = 0;
//    //int overheadsCount = 0;
//    while (readyQ[0].status == 1 && !readyQ.empty()) {//io burst and empty conflicts
//        //if(readyQ[0].currentC == readyQ[0].numOfCPU) continue;
//        if(readyQ[0].arrivalT > current) {
//            idletime += readyQ[0].arrivalT- cTime;
//            cTime = readyQ[0].arrivalT;
//        }
//
//        int i = readyQ[0].currentC;
//        readyQ[0].status = 3;
//        cTime += readyQ[0].cpuList[i].burstT;
//        current = cTime;
//        iTime = current + readyQ[0].ioList[i].burstT;
//        readyQ[0].cputime = cTime;
//        readyQ[0].iotime = iTime;
//        readyQ[0].status = 2;
//
//        i++; //update cpu counter in a process
//        readyQ[0].currentC = i;
//        if (readyQ[0].currentC == readyQ[0].numOfCPU) {//process completed
//            readyQ[0].status = 4; //prcess completed
//            readyQ[0].finishT = current;
//            readyQ[0].tatT = readyQ[0].finishT - readyQ[0].arrivalT;
//            readyQ[0].wait = readyQ[0].tatT - readyQ[0].serviceT-readyQ[0].iotimeB;
//            executeArr.push_back(readyQ[0]);
//
//            readyQ.erase(readyQ.begin());
//            sort(readyQ.begin(), readyQ.end(),compareJobsTio);
//            readyQ[0].status = 1;
//            if(cTime < readyQ[0].iotime) {
//                cTime = readyQ[0].iotime;
//                idletime+=readyQ[0].iotime - current;
//            }
//            continue;
//        }
//        if (cTime < readyQ[1].iotime) {
//            sort(readyQ.begin(), readyQ.end(), compareJobsTio);
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
//    }
//    summary(algName,current,idletime);
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
