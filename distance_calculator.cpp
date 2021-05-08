#include<iostream>
#include<math.h>
#include<assert.h>
#include <bits/stdc++.h> 
#include <string>
#include <fstream>
#include<stdio.h>
using namespace std;
unsigned long long  size =0;
// char programname[100];
vector<unsigned long long> blocktrace;
unordered_map<unsigned long long, vector<int>> block_hash;
// maps block number to the index of the next index of the vector of block_hash
unordered_map<unsigned long long,int> index_map;

// void debug(){
		// for(int i =0; i<block_hash[0].size(); i++)
			// cout<<block_hash[0][i]<<" ";
// }

// function which calculates the cumulative density function
void calculate_cdf(vector<int> distance){
	map<unsigned long long,float> cdf;
	float N = distance.size();
	ofstream fout;
	char outputfilename[100];
	sprintf(outputfilename,"cdf_q2.csv");
	fout.open(outputfilename);
	
	fout<<"log10(d)"<<", "<<"F(d)"<<"\n";
	sort(distance.begin(),distance.end());
	for (unsigned long long index =0; index <distance.size()-1; index++){
		if(distance[index] != distance[index + 1]){
			// cout<<index<<endl;
			//cdf[distance[index]] = (float)(index +1)/N;
		       float d = log10(distance[index]);
		       float probability = (float)(index +1)/N; 
		       fout<<d<<", "<<probability<<"\n";
		       
		}
			// cout<<"calculating  "<<index<<endl;
	}
	fout.close();
	
	// //Dumping the cdf in cdf_q2_prog#.txt file
	// sprintf(outputfilename,"cdf_q2_%s.txt",programname);
	// FILE *cdf_file = fopen(outputfilename, "w");
	// for(auto it = cdf.begin(); it!= cdf.end(); ++it){
		// float d = log10((*it).first);
		// float probability = (*it).second;
		// fprintf(cdf_file,"%f    %f\n",d ,probability);
	// }
	
	//Dumping the cdf in cdf_q2_prog#.csv file
	/*ofstream fout;
	sprintf(outputfilename,"cdf_q2.txt");
	fout.open(outputfilename);
	fout<<"log10(d)"<<", "<<"F(d)"<<"\n";
	for(auto it = cdf.begin(); it!= cdf.end(); ++it){
		float d = log10((*it).first);
		float probability = (*it).second;
		fout<<d<<", "<<probability<<"\n";
	}
	fout.close();*/
	cout<<"Output File generated: "<<outputfilename<<endl;
}

// Function which calculates the distances
void calculate_distance(){
	// int distance[blocktrace.size()];
	vector<int> distance, actual_distance;
	for(unsigned long long index =0; index<blocktrace.size(); index++){
		unsigned long long block = blocktrace[index];
		if(block_hash[block][0] == index){
			// distance[index] = 0;
			//distance.push_back(0);
			index_map[block] = 1;
		}
		else{
			// distance[index] = block_hash[block][index_map[block]] - block_hash[block][index_map[block]-1];
			distance.push_back(block_hash[block][index_map[block]] - block_hash[block][index_map[block]-1]);
			index_map[block] +=1;
		}
	}
	
	// Dumping results into access_distance.txt
	// FILE *access_distancefile = fopen("access_distance.txt", "w");
	/*for(unsigned long long index =0; index<blocktrace.size(); index++){
		if(distance[index]){
			// fprintf(access_distancefile,"%d\n", distance[index]);
			actual_distance.push_back(distance[index]);
		}
		
		cout<<"Removing 0 "<<index<<endl;
	}*/
	
	//Calling function which calculates the cumulative density function
	//calculate_cdf(actual_distance);
         calculate_cdf(distance);
	// debug();
}
// Initialization function
void init(unsigned long long memoryAddress){
	static unsigned long long indexoftrace=0;
	unsigned long long blocknumber;
	blocknumber = memoryAddress/64;
	blocktrace.push_back(blocknumber);
	block_hash[blocknumber].push_back(indexoftrace);
	indexoftrace++;
}



/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
int main(int argc, char * argv[])
{
	char inputname[100];
	// sprintf(programname,"%s",argv[1]);
	sprintf(inputname,"input/thread_memory_trace.txt");
	FILE *tracefile = fopen(inputname, "r");
    	assert(tracefile != NULL);
    	unsigned long long *addr;
		int *tid_read;
    	
    	int i =0;
    	while(fscanf(tracefile, "%d", tid_read)){
		fscanf(tracefile, "%llu", addr);
    		unsigned long long memoryAddress = *addr;
    		init(memoryAddress);
    		// cout<<i++<<endl;
    		
    	}
    	//cout<<"Total size of trace is "<<size<<endl;
    	//cout<<"block trace size "<<blocktrace.size()<<endl;
    	//closing the file fp
	fclose(tracefile);
	printf("\nDone reading file!\n");
	//calling function which calculate the distances
	calculate_distance();
	
	
    return 0;
}
