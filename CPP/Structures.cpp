typedef struct {
	unsigned long id;          // Node identification
	char name[184];
	double lat, lon;           // Node position
	unsigned short nsucc=0;      // Number of node successors; i. e. length of successors
	unsigned long *successors;
} node;


void set_Maximum_node_Descendant_N(unsigned short comp, unsigned short *counter){
	if(comp> (*counter)){
		(*counter)=comp;					
	}
}

