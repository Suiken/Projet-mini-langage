#ifndef MINIPSEUDTREE
# define MINIPSEUDTREE

enum NodeType {
	NTEMPTY 	= 0,
	NTINSTLIST 	= 1,
	
	NTDECL 		= 11,
	NTAFFI 		= 12,
	NTPRIN 		= 13,

	NTTYPE 		= 101,
	NTBOOL 		= 102, 

	NTNUM   	= 201,
	NTVAR		= 202,

	NTPLUS  	= 321,
	NTMIN   	= 322,
	NTMULT  	= 323,
	NTDIV   	= 324,
	NTPOW   	= 325,
	NTMOD		= 326,

	NTEGAL		= 401,
	
	NTSUP		= 501,
	NTINF		= 502,
	NTSUP_EG	= 503,
	NTINF_EG	= 504,
	NTEG_EG		= 505,

	NTIF		= 601,
	NTWHILE		= 602

};
   
typedef struct Node {
	enum NodeType type;
	union { 
		double val;
		char* var;
		struct Node** children;
	} ;
} Node;

typedef struct Variable{
	char *name;
	char* type_name;
	union{
		double reel;
		int booleen;
	} type;
} Variable;

typedef struct ListVariables{
	Variable *names;
	int length;
	int max;
} ListVariables;

Node* createNode(int type);

Node* nodeChildren(Node* father, Node *child1, Node *child2);

const char* node2String(Node *node);

void printGraph(Node *root);

Variable* createVariable(char *name);

ListVariables* addVariable(ListVariables *vars, char *name, char *type);

//Variable* declareVariable(char *type, Node *name);

Variable* declareVariableWithoutValue(char *type, char *name);

ListVariables* createListVariables();

double searchVariable(ListVariables *variables, char *nom);

ListVariables* valueToVariable(ListVariables *vars, char* name, double value);

#endif