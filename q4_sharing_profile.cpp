#include<iostream>
#include<math.h>
#include<assert.h>
#include <bits/stdc++.h> 
#include <string>
#include <fstream>
#include<stdio.h>
using namespace std;

unordered_map<unsigned long long , vector<int>> block_hash;
unsigned long long oneshare, twoshare, threeshare, fourshare, fiveshare, sixshare, sevenshare,eightshare;
void count_sharers(){
	oneshare=twoshare=threeshare=fourshare=fiveshare=sixshare=sevenshare=eightshare=0;
	for(auto it = block_hash.begin(); it!=block_hash.end(); ++it){
		switch((*it).second.size()){
			case 1: oneshare++; break;
			case 2: twoshare++; break;
			case 3: threeshare++; break;
			case 4: fourshare++; break;
			case 5: fiveshare++; break;
			case 6: sixshare++; break;
			case 7: sevenshare++; break;
			case 8: eightshare++; break;
			default: cout<<"Hey there is some problem in the switch";
		}
		
		// debugging
		// cout<<(*it).second.size()<<endl;
		// if((*it).second.size() == 8){cout<<"yes 8"<<endl;}
	}
}

void sharing_profile(int tid , unsigned long long memoryAddress){
	// cout<<tid<<"    "<<memoryAddress<<endl;
	unsigned long long blocknumber = memoryAddress/64;
	if(block_hash[blocknumber].size() == 0){
		block_hash[blocknumber].push_back(tid);
	}
	else{
		int flag =1;
		for (int i=0; i<block_hash[blocknumber].size();i++){
			if(block_hash[blocknumber][i] == tid){
				flag = 0;
				break;
			}
		}
		if(flag){
			block_hash[blocknumber].push_back(tid);
		}
	}
}


/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
int main(int argc, char * argv[])
{
	char inputname[100];
	sprintf(inputname,"input/thread_memory_trace.txt");
	FILE *tracefile = fopen(inputname, "r");
    	assert(tracefile != NULL);
    	unsigned long long *addr;
		int *tid_read;
    	
    	while(fscanf(tracefile, "%d", tid_read) ){
			fscanf(tracefile, "%llu", addr);
    	// for(int i=0;i<108800;i++){    //debug
			int tid = *tid_read;
    		unsigned long long memoryAddress = *addr;
    		sharing_profile(tid, memoryAddress);
    		
    	}
    	//closing the file fp
	fclose(tracefile);
	printf("\nDone reading file!\n");
	//calling function which counts the sharers
	count_sharers();
	
	cout<<"Sharers Information of the "<<endl;
	cout<<"oneshare: "<<oneshare<<endl;
	cout<<"twoshare: "<<twoshare<<endl;
	cout<<"threeshare: "<<threeshare<<endl;
	cout<<"fourshare: "<<fourshare<<endl;
	cout<<"fiveshare: "<<fiveshare<<endl;
	cout<<"sixshare: "<<sixshare<<endl;
	cout<<"sevenshare: "<<sevenshare<<endl;
	cout<<"eightshare: "<<eightshare<<endl;
	
	
	// cout<<oneshare<<endl;
	// cout<<twoshare<<endl;
	// cout<<threeshare<<endl;
	// cout<<fourshare<<endl;
	// cout<<fiveshare<<endl;
	// cout<<sixshare<<endl;
	// cout<<sevenshare<<endl;
	// cout<<eightshare<<endl;
	
    return 0;
}
