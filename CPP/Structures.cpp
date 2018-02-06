typedef struct {
	unsigned long id;          // Node identification
	char name[184];
	double lat, lon;           // Node position
	unsigned short nsucc=0;      // Number of node successors; i. e. length of successors
	unsigned long offset;
} node;

typedef struct {
	unsigned long source;
	unsigned long destination;
 	double weight;
} connection;


typedef char Queue;
enum whichQueue {NONE, OPEN, CLOSED};

typedef struct {
	double g, h;
	unsigned long parent;
	Queue whq;
} AStarStatus;

void set_Maximum_node_Descendant_N(unsigned short comp, unsigned short *counter){
	if(comp> (*counter)){
		(*counter)=comp;					
	}
}

