//
//  input.cpp
//  
//
//  Created by Nan  on 12/3/20.
//
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std;

int numOfprocess = 50, overheads =5;
int totalNumofCPUBurst = numOfprocess * 20;
int main(){
    int counter  =0;
    
    srand (time(NULL));
    double lambda = 0.02;
    double u;
    ofstream outStream;
    outStream.open("inData.txt");
    outStream<< numOfprocess <<" "<<overheads<<endl;
    
    for(int i = 1; i <=numOfprocess;++i ){
        
        int  cpuNum, cpuBurst, ioBurst, arrivalTime;
        
        u = (double)rand()/RAND_MAX;//generate a random arrival time each process
        
        if(counter <= totalNumofCPUBurst){//checking numbers of cpu burst
            cpuNum = rand()% 20 + 1;
            arrivalTime = (int)(log(1-u)/(-lambda));
            outStream<<i<<" "<<arrivalTime<<" " <<cpuNum<<endl;
            for(int j=1;j<=cpuNum;j++){
                cpuBurst = rand() % 495 + 5;
                outStream<<j<<" "<<cpuBurst;
                if(j != cpuNum){
                    ioBurst =rand()% 970 + 30;
                    outStream<<" "<<ioBurst<<endl;
                }
                counter++;
            }
        }
    outStream << endl<<endl;
    }
    
    outStream.close();
    
    return 0;
}
