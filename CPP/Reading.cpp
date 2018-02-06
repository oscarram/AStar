#define nnodes 3472620
#define nmembers 30
//#define nnodes 20

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <cstring>
#include <climits>
#include "Structures.cpp"
#include "BinarySearch.cpp"

//#include "QuickSort.cpp"



unsigned long nodeIndex=0;
node *nodes;



int main() {
//	printf("%lu", ULONG_MAX);


	if((nodes = (node*)malloc(nnodes*(sizeof(node)+ sizeof(unsigned long)*nmembers)))==NULL){
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
	std::string node1, node2, node3;

	unsigned int indexForNodes, indexForSuccesors;
	unsigned long binary_search_result, idwaymember;
	unsigned long connections[5306];
	unsigned long connectionsID[5306];
	unsigned short nodemembercounter=0;
	std::string str;
	std::string delimiter = "|";

	std::string token_type;
	std::string token_id;
	std::string token_name;
	std::string token_oneway;

	std::string token_info;
	bool problem_flag=0;
	
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
/**********************************************************************************************************************/
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
/**********************************************************************************************************************/
			else if (token_type.compare("way")==0){

				for (field_splitter=0; field_splitter < 4; field_splitter++){
					pos=str.find(delimiter);
					str.erase(0, pos + delimiter.length());
				}

				pos=str.find(delimiter);
				token_oneway=str.substr(0, pos);;
				str.erase(0, pos + delimiter.length());
//				std::cout<<token_oneway<<std::endl;

				pos=str.find(delimiter);
				str.erase(0, pos + delimiter.length());

				indexForNodes=0;

				while((pos=str.find(delimiter))!=std::string::npos){
					token_info=str.substr(0,pos);
					str.erase(0, pos + delimiter.length());					
					std::cout<<token_info<<std::endl;
					idwaymember=std::stoul(token_info,nullptr, 10);
					binary_search_result=binarySearch(nodes, 0, nodeIndex-1, idwaymember);
					if (binary_search_result<nodeIndex){
						connectionsID[indexForNodes]=idwaymember;
						connections[indexForNodes]=binary_search_result;
						indexForNodes++;
					}					
				}

				token_info=str;

				idwaymember=std::stoul(token_info,nullptr, 10);
				binary_search_result=binarySearch(nodes, 0, nodeIndex-1, idwaymember);
				if (binary_search_result<nodeIndex){
					connectionsID[indexForNodes]=idwaymember;
					connections[indexForNodes]=binary_search_result;
					indexForNodes++;
				}
				
				std::cout<<token_id<<std::endl;
				std::cout<<indexForNodes<<std::endl;
	/**********************************************************************************************************************/
				if(indexForNodes>=2){				
					if(token_oneway.compare("oneway")==0){
						//std::cout<<token_oneway<<std::endl;
						for(indexForSuccesors=0; indexForSuccesors<indexForNodes-1; indexForSuccesors++){
							nodes[connections[indexForSuccesors]].successors[nodes[(connections[indexForSuccesors])].nsucc]=connections[indexForSuccesors+1];
							nodes[connections[indexForSuccesors]].nsucc = nodes[connections[indexForSuccesors]].nsucc+1;
							set_Maximum_node_Descendant_N(nodes[connections[indexForSuccesors]].nsucc, &nodemembercounter);
						}
					}
					else {
						for(indexForSuccesors=0; indexForSuccesors<indexForNodes-1; indexForSuccesors++){
							nodes[connections[indexForSuccesors]].successors[nodes[(connections[indexForSuccesors])].nsucc]=connections[indexForSuccesors+1];
							nodes[connections[indexForSuccesors+1]].successors[nodes[(connections[indexForSuccesors+1])].nsucc]=connections[indexForSuccesors];
							nodes[connections[indexForSuccesors]].nsucc = nodes[connections[indexForSuccesors]].nsucc+1;
							nodes[connections[indexForSuccesors+1]].nsucc = nodes[connections[indexForSuccesors+1]].nsucc+1;
							set_Maximum_node_Descendant_N(nodes[connections[indexForSuccesors]].nsucc, &nodemembercounter);
							set_Maximum_node_Descendant_N(nodes[connections[indexForSuccesors+1]].nsucc, &nodemembercounter);
						}
					}
				}
	/**********************************************************************************************************************/
			}
/**********************************************************************************************************************/
			else{
//				std::cout<< 1 << std::endl;
			}
			//std::cout << token_id << std::endl;
		}		 
		// now we loop back and get the next line in 'str'
	}
//	printf("%lu\n", binarySearch(nodes, 0, nodeIndex-1, 1543089000));
//	printf("%d\n", nodes[binarySearch(nodes, 0, nodeIndex-1, 1543089000)].nsucc);
//	printf("%lu\n", binarySearch(nodes, 0, nodeIndex-1, 8774492));
//	printf("%d\n", nodes[binarySearch(nodes, 0, nodeIndex-1, 8774492)].nsucc);
//	printf("%hu\n", nodemembercounter);
 	in.close();
 	free(nodes);
  	return 0;
}
