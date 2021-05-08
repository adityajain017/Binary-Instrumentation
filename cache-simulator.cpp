#include<iostream>
#include<math.h>
#include<assert.h>
#include <bits/stdc++.h> 
#include <string>
#include <fstream>
using namespace std;
#define BLOCK_SIZE 64
#define L2_TOTAL_SETS 1024 

// char programname[100];
//Defining L2 Cache as a 2D-Array
unsigned long long l2cache[L2_TOTAL_SETS][16];

//Defining counters for number of hits and misses.
unsigned long long l2access_counter, l2_hit, l2_miss;



//Globals for finding distances
vector<unsigned long long> blocktrace;
unordered_map<unsigned long long, vector<int>> block_hash;
// maps block number to the index of the next index of the vector of block_hash
unordered_map<unsigned long long,int> index_map;

//Class to Implement LRU ---------------------------------------------------------------------------------------------
class Lru
{     list <int> lines2;
     unordered_map<int, list<int>> sets2; 
     public :
       void init2();
       void lru2Update(int set,int way);
       int lru2GetLine(int set);
      
}lru;

//method for initializing LRU for L2 cache  
void Lru :: init2()
{
   for(int i = 0;i<1024;i++) 
    {  for(int j=0;j<16;j++)
       {
          lines2.push_back(j);
       } 
      sets2.insert(make_pair(i,lines2));
     lines2.clear();
   }
}

//method for updating L2 cache on a hit
void Lru::lru2Update(int set,int way)
{
     sets2.at(set).remove(way);
     sets2.at(set).push_front(way);  

}

//method for updating L2 cache on a miss
int Lru::lru2GetLine(int set)
{  int way;
   way=sets2.at(set).back();
   sets2.at(set).pop_back();
   sets2.at(set).push_front(way);
   return way;
   
}
// End of LRU -----------------------------------------------------------------------------------------------------------

// function to initialize the global variables.
void init(){
    l2access_counter = l2_hit = l2_miss = 0;
    
    //initializing the L2 Cache with 0 value
    for(int index =0; index< L2_TOTAL_SETS; index++){
        for( int line =0 ; line < 16; line++){
            l2cache[index][line] = 0;
        }
    }
}
// Initialization function for distance calculation
void init_blocktrace(unsigned long long memoryAddress){
	static unsigned long long indexoftrace=0;
	unsigned long long blocknumber;
	blocknumber = memoryAddress/64;
	blocktrace.push_back(blocknumber);
	block_hash[blocknumber].push_back(indexoftrace);
	indexoftrace++;
}

// Function to calculate cumulative density function for cache miss trace 
// function which calculates the cumulative density function
void calculate_cdf(vector<int> distance){
	map<unsigned long long,float> cdf;
	float N = distance.size();
	ofstream fout;
	char outputfilename[100];
	sprintf(outputfilename,"cdf_q3.csv");
	fout.open(outputfilename);
	
	fout<<"log10(d)"<<", "<<"F(d)"<<"\n";
	sort(distance.begin(),distance.end());
	for (unsigned long long index =0; index <distance.size()-1; index++){
		if(distance[index] != distance[index + 1]){
			
			if(distance[index]==1)
			cout<<index+1<<endl;
		       float d = log10(distance[index]);
		       float probability = (float)(index +1)/N; 
		       fout<<d<<", "<<probability<<"\n";
		       
		}

	}
	fout.close();
	cout<<"Output File generated: "<<outputfilename<<endl;
}


// Function for calculating distances of cache miss memory trace
void calculate_distance(){
	vector<int> distance;
	for(unsigned long long index =0; index<blocktrace.size(); index++){
		unsigned long long block = blocktrace[index];
		if(block_hash[block][0] == index){

			index_map[block] = 1;
		}
		else{
			distance.push_back(block_hash[block][index_map[block]] - block_hash[block][index_map[block]-1]);
			index_map[block] +=1;
		}
	}
	
	
	//Calling function which calculates the cumulative density function
	calculate_cdf(distance);
	

}

// function to implement single level Cache
void l2_cache(unsigned long long address){
    //Caculating block number and index of the referenced address
    unsigned long long block_number;
    block_number = address / BLOCK_SIZE;
    int address_index = int(block_number % 1024);
    
    //Checking l2 cache hit or miss
    int flag_hit = 0;
     for( int line =0 ; line<16 ; line++){
        if(block_number == (l2cache[address_index][line]/BLOCK_SIZE)) { 
            flag_hit =1;
            //incrementing l2 cache hit count
            l2_hit++;
            //updating lru data structure for block hit
            lru.lru2Update(address_index,line);
            break;
        }
    }
    
    // Calling L3 cache in case of a L2 miss
    if(!flag_hit){
        l2_miss++;
		
		//Calling init_blocktrace function for passing this miss memoryAddress for calculation of distance
		init_blocktrace(address);
        
               //getting line which needs to be replaced with the new block from l3 cache
		int replace_line = lru.lru2GetLine(address_index);
		
		//Inserting new block in l2 cache
		l2cache[address_index][replace_line] = address;
		lru.lru2Update(address_index, replace_line);
    }
    
}

// Main function of program.
int main(int argc, char **argv){
	
	lru.init2();	
	char inputname[100];

	sprintf(inputname,"input/thread_memory_trace.txt");
	FILE *tracefile = fopen(inputname, "r");
    assert(tracefile != NULL);
    unsigned long long *addr;
	int *tid_read;
	init();
	unsigned long long memoryAddress;
    while(fscanf(tracefile, "%d", tid_read)){
		fscanf(tracefile, "%llu", addr);
		memoryAddress = *addr;
		l2access_counter++;
		l2_cache(memoryAddress);

    }
    
        //closing the file fp
	fclose(tracefile);
	printf("\nDone reading file!\n");
	//Clsing miss_tracefile
	// fclose(miss_trace_file);
	//Calling the calculate_distance function for calculation of distances for cache missed traces.
	calculate_distance();
	
// Printing output 
cout<<"Results: "<<endl;
cout<<"L2 accesses: "<<l2access_counter<<endl;
cout<<"l2_hit: "<<l2_hit<<endl;
cout<<"l2_miss: "<< l2_miss<<endl;


return 0; 
}
