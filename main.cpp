//Development Environment: MacOS Mojave 10.14 with clang++ Also works on ITU SSH Servers
//To compile: g++ -std=c++11  HW1.cpp -pthread
//To run example: ./a.out 1000 640

#include<iostream>
#include<thread>
#include<unistd.h>
#include<vector>

using namespace std;

int Prime(int n,int min, int max, int count){
	for(int i=min;i<max;i++){
		if(n%i==0){
			count++;
			return count;
		}
	}
	return count;
}
int main(int argc, char** argv){
    int max,min;
	vector<int> num;
    for(int k=1;k<argc;k++){
        num.push_back(stoi(argv[k]));
    }
	cout << "Master : Started."<<endl;
    
	for(int i=1;i<argc;i++){
		pid_t Slave = fork();

		if(Slave == 0){
			int count = 0;
			std :: thread thr[num.size()*4];
            cout<<"Slave "<< i << ": started. Number :" << argv[i] << endl;
			
			for(int j=0;j<4;j++){
				if(j==0){
					min = 2;
					max = stoi(argv[i])/8;
					cout<<"Thread" << i << "." << j+1 << ": testing " << min << "-" <<max << endl;
				}
				if(j==1){
					min = stoi(argv[i])/8;
					max = stoi(argv[i])/4;
					cout<<"Thread" << i << "." << j+1 << ": testing " << min << "-" <<max << endl;
				}
				if(j==2){
					min = stoi(argv[i])/4;
					max = 3*stoi(argv[i])/8;
					cout<<"Thread" << i << "." << j+1 << ": testing " << min << "-" <<max << endl;

				}
				if(j==3){
					min = 3*stoi(argv[i])/8;
					max = stoi(argv[i])/2;
					cout<<"Thread" << i << "." << j+1 << ": testing " << min << "-" <<max << endl;

				}
				count = Prime(stoi(argv[i]),min,max,count);
				thr[j] = thread(Prime,stoi(argv[i]),min,max,count);
				thr[j].join();
			
			}
			if(count == 0){
				cout << "Slave " << i << ": done." << argv[i] << " is a prime number." << endl;
			}
			else if(count != 0){
			    cout << "Slave " << i << ": done." << argv[i] << " is not a prime number." << endl;
			}
    
			exit(0);
		}
		cout << "Master : Done." << endl;
	}
}
