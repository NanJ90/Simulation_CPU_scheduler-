// g++ exp_dist.cpp && ./a.out 50 > data.txt && sort -h data.txt > sorted_data.txt && cat sorted_data.txt

#include <math.h>
#include <time.h>   
#include <string>
#include <iostream> 
using namespace std;

const int HOW_WIDE_APART = 10;

int main(int argc, char** argv) { 

	string guitar = argv[1];
  int i_dec = stoi (guitar);
	// cout << i_dec << endl;

	srand( (unsigned)time( NULL ) );
	double lambda = 0.02;
	double u;

	for (int i = 0; i < i_dec; i++) {
		cout << (int)(rand()%(i_dec*HOW_WIDE_APART)) << " ";   // uniform dist
		u = (double)rand()/RAND_MAX;
		cout << (int)(log(1-u)/(-lambda)) << endl; // exponential dist
	}
}