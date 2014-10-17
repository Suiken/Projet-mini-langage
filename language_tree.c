#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language_tree.h"
#include <string.h>

# define PRINTTAB 2

Node* createNode(int type) {
	Node* newnode = (Node *) malloc(sizeof(Node));
	newnode->type = type;
	newnode->children = NULL;
	return newnode;
}

Node* nodeChildren(Node* father, Node *child1, Node *child2) { 
	father->children = (Node **) malloc(sizeof(Node*) * 2);
	father->children[0] = child1;
	father->children[1] = child2;
	return father;
}

const char* node2String(Node *node) {	
	char *res;
	switch ( node->type ) {
	case NTEMPTY:    return "NTEMPTY";
	case NTINSTLIST: return "NTINSTLIST";

	case NTDECL: return "NTDECL"; 
	case NTPRIN: return "NTPRIN";

	case NTAFFI:
		res = (char*)malloc(sizeof(char)*32);
		sprintf(res, "NTAFFI -> %s", node->var);
		return res;

	case NTNUM:
		res = (char *)malloc(sizeof(char) * 32);
		sprintf(res, "NTNUM -> %f", node->val);
		return res;
	
	case NTVAR:
		res = (char *)malloc(sizeof(char) * 32);
		sprintf(res, "NTVAR -> %s", node->var);
		return res;

	case NTTYPE:
		res = (char*)malloc(sizeof(char)*32);
		sprintf(res, "NTTYPE -> %s", node->var);
		return res;

	case NTBOOL:
		res = (char*)malloc(sizeof(char)*32);
		sprintf(res, "NTBOOL -> %s", node->var);
		return res;

	case NTPLUS:  return "NTPLUS";
	case NTMIN:   return "NTMIN";
	case NTMULT:  return "NTMULT";
	case NTDIV:   return "NTDIV";
	case NTPOW:   return "NTPOW";
	case NTMOD:	return "NTMOD";

	case NTEGAL: return "NTEGAL";

	case NTEG_EG: return "NTEG_EG";
	case NTSUP: return "NTSUP";
	case NTSUP_EG: return "NTSUP_EG";
	case NTINF: return "NTINF";
	case NTINF_EG: return "NTINF_EG";

	case NTIF: return "NTIF";
	case NTWHILE: return "NTWHILE";
	
	default: return "UNK";
	};
}

const char* makeSpaces(int depth, int fdepth) {
	int nbspaces = depth * PRINTTAB;	
	char *spaces = (char *)malloc(sizeof(char) * nbspaces);
	if (depth == fdepth)		
		memset(spaces, ' ', nbspaces);
	else {
		int midspaces = fdepth * PRINTTAB;
		int endline = (depth - fdepth) * PRINTTAB - 1;
		memset(spaces, ' ', midspaces);
		spaces[midspaces] = '\\';
		char *tmpline =  (char *)malloc(sizeof(char) * endline);
		memset(tmpline, '_', endline);
		strcat(spaces, tmpline);
		free(tmpline);
	}
	return spaces;
}


void printGraphRec(Node *node, int depth, int fdepth) {
	printf("%s%s\n", makeSpaces(depth, fdepth), node2String(node));
	
	// Hack : No children only if null or number 
	if ((node->children != NULL) &&
		(node->type != NTNUM) &&
		(node->type != NTVAR) &&
		(node->type != NTTYPE) &&
		(node->type != NTBOOL) &&
		(node->type != NTAFFI)) {
		printGraphRec(node->children[0], depth + 1, depth);
		printGraphRec(node->children[1], depth + 1, depth);
	}
}

void printGraph(Node *root) {
	printGraphRec(root, 0, 0);
}

Variable* createVariable(char *name){
	Variable *var = (Variable*) malloc(sizeof(Variable));
	var->name = name;
	return var;
}

Variable* declareVariableWithoutValue(char *type, char *name){
	if(strcmp(type, "reel") || strcmp(type, "booleen")){
		Variable *var = createVariable(name);
		var->type_name = type;
		return var;
	}else{
		printf("Type '%s' non reconnu", type);
		exit(0);
	}
}

ListVariables* createListVariables(){
	ListVariables *variables = (ListVariables*) malloc(sizeof(ListVariables));
	variables->max = 100;
	variables->names = (Variable*) malloc(variables->max*sizeof(Variable));
	variables->length = 0;
	return variables;
}

//On cherche ici la valeur d'une variable
double searchVariable(ListVariables *variables, char *name){
	int i = 0;
	while(i < variables->length){
		if(strcmp(variables->names[i].name, name) == 0){
			return variables->names[i].type.reel;
		}else{
			i++;
		}
	}
	printf("Variable non initialisée\n");
	exit(0);
}

ListVariables* addVariable(ListVariables *vars, char *name, char *type){
	int i = 0;
	while(i < vars->length){
		if(strcmp(vars->names[i].name, name) == 0){
			printf("Variable déjà existante\n");
			exit(0);
		}else{
			i++;
		}
	}
	vars->names[vars->length] = *declareVariableWithoutValue(type, name);
	vars->length++;
	//printf("Variable %s initialisée en type %s\n", vars->names[vars->length-1].name, vars->names[vars->length-1].type_name);
	return vars;
}

ListVariables* valueToVariable(ListVariables *vars, char* name, double value){
	int i = 0, trouve = 0;
	while(i < vars->length && trouve == 0){
		if(strcmp(vars->names[i].name, name) == 0){
			if(strcmp(vars->names[i].type_name, "reel") == 0){
				vars->names[i].type.reel = value;
			}else if(strcmp(vars->names[i].type_name, "booleen") == 0){
				if(value == 1.0 || value == 0.0){
					vars->names[i].type.reel = value;
				}else{
					printf("Type de la valeur incompatible avec le type de la variable\n");
					exit(0);
				}
			}else{
				printf("Type de la valeur incompatible avec le type de la variable\n");
				exit(0);
			}
			trouve = 1;
		}else{
			i++;
		}
	}
	if(trouve == 0){
		printf("Variable %s non initialisée\n", name);
		exit(0);
		/*vars->names[vars->length].name = name;
		vars->names[vars->length].type.reel = value;
		vars->length = vars->length+1;*/
	}
	//printf("%s vaut %f\n", vars->names[i].name, vars->names[i].type.reel);
	return vars;
}