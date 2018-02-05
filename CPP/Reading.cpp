#define nnodes 3472620

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <cstring>
#include "Structures.cpp"
#include "BinarySearch.cpp"

//#include "QuickSort.cpp"



unsigned long nodeIndex=0;
node *nodes;



int main() {

	if((nodes = (node*)malloc(nnodes*sizeof(node))) ==NULL){
    	std::cerr << "Cannot allocate enough memory.\n" << std::endl;
		return 1;
	}
	
	std::ifstream in("cataluna.csv");

  	if(!in) {
    	std::cerr << "Cannot open input file.\n" << std::endl;
    	return 1;
  	}

	size_t pos=0;
	unsigned char field_splitter=0;
//	std::string node1, node2, node3=0;

	std::string str;
	std::string delimiter = "|";

	std::string token_type;
	std::string token_id;
	std::string token_name;

	std::string token_info;

	while (std::getline(in, str)) {
		// output the line
		token_type= "";
		//std::cout << str << std::endl;
		if((pos=str.find(delimiter)) != std::string::npos){

			token_type = str.substr(0, pos);	
			str.erase(0, pos + delimiter.length());	
			
			pos=str.find(delimiter);
			token_id = str.substr(0, pos);
			str.erase(0, pos + delimiter.length());	

			pos=str.find(delimiter);
			token_name = str.substr(0, pos);
			str.erase(0, pos + delimiter.length());	

			if(token_type.compare("node")==0){

				(*(nodes+nodeIndex)).id=std::stoul(token_id, nullptr, 10);
				std::strcpy ((*(nodes+nodeIndex)).name, token_name.c_str());

				for (field_splitter=0; field_splitter <6; field_splitter++){
					pos=str.find(delimiter);
					str.erase(0, pos + delimiter.length());
				}
				
				pos=str.find(delimiter);
				token_info = str.substr(0, pos);
				str.erase(0, pos + delimiter.length());
				(*(nodes+nodeIndex)).lat=std::stod(token_info, nullptr);

				pos=str.find(delimiter);
				token_info = str.substr(0, pos);
				str.erase(0, pos + delimiter.length());	
				(*(nodes+nodeIndex)).lon=std::stod(token_info, nullptr);

				nodeIndex++;

			}
			else if (token_type.compare("way")==0){

			}
			else{
//				std::cout<< 1 << std::endl;
			}
			//std::cout << token_id << std::endl;
		}		 
		// now we loop back and get the next line in 'str'
	}
	printf("%lu", binarySearch(nodes, 0, nodeIndex-1, 1543294778));
 	in.close();
 	free(nodes);

  	return 0;
}
