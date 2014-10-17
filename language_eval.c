#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <setjmp.h>
#include "language_tree.h"
#include <string.h>




 

int valeur[26] = {0};
ListVariables *variables;

int printDepth = 0;
int funcDepth = 0;

double evalExpr(Node *node) {
	switch ( node->type ) {
		case NTEMPTY:  return 0.0;
		
		case NTNUM: return node->val;
		case NTVAR:
			return searchVariable(variables, node->var);

		case NTDECL:
			return evalExpr(node->children[0]);

		case NTBOOL:
			if(strcmp(node->var, "vrai") == 0){
				return 1.0;
			}else if(strcmp(node->var, "faux") == 0){
				return 0.0;
			}else{
				return -1.0;
			}

		case NTPLUS: return evalExpr(node->children[0])
			+ evalExpr(node->children[1]);
		case NTMIN: return evalExpr(node->children[0])
			- evalExpr(node->children[1]);
		case NTMULT: return evalExpr(node->children[0])
			* evalExpr(node->children[1]);
		case NTDIV: return evalExpr(node->children[0])
			/ evalExpr(node->children[1]);
		case NTPOW: return pow(evalExpr(node->children[0]),
			evalExpr(node->children[1]));
		case NTMOD: return (int)(evalExpr(node->children[0]))
			% (int)(evalExpr(node->children[1]));

		case NTEGAL:
			return evalExpr(node->children[1]);

		case NTEG_EG:
			if(evalExpr(node->children[0]) == evalExpr(node->children[1])){
				return 1;
			}
			return 0;
		case NTSUP:
			if(evalExpr(node->children[0]) > evalExpr(node->children[1])){
				return 1;
			}
			return 0;
		case NTSUP_EG:
			if(evalExpr(node->children[0]) >= evalExpr(node->children[1])){
				return 1;
			}
			return 0;
		case NTINF:
			if(evalExpr(node->children[0]) < evalExpr(node->children[1])){
				return 1;
			}
			return 0;
		case NTINF_EG:
			if(evalExpr(node->children[0]) <= evalExpr(node->children[1])){
				return 1;
			}
			return 0;

		default: 
			printf("Error in evalExpr ... Wrong node type: %s\n", node2String(node));
			exit(1);
	};
}


void evalInst(Node* node) {
	double val;
	switch ( node->type ) {
	case NTEMPTY: return;
	case NTNUM: 
		//printf("%f\n", evalExpr(node));
		return;

	case NTINSTLIST:
		evalInst(node->children[0]);
		evalInst(node->children[1]);
		return;

	case NTDECL:
		variables = addVariable(variables, node->children[0]->var, node->children[1]->var);
		return;
	
	case NTPRIN:
		printf("%f\n", evalExpr(node->children[1]));
		return;

	case NTPLUS:
	case NTMIN:
	case NTMULT:
	case NTDIV:
	case NTPOW:
	case NTMOD:
	case NTEG_EG:
	case NTINF:
	case NTINF_EG:
	case NTSUP:
	case NTSUP_EG:
		//printf("%f\n", evalExpr(node));
		return;
	case NTEGAL:
		variables = valueToVariable(variables, node->children[0]->var, evalExpr(node->children[1]));
		return;

	case NTIF:
		if(evalExpr(node->children[0])){
			evalInst(node->children[1]);
		}
		return;
	case NTWHILE:
		while(evalExpr(node->children[0]) > 0){
			evalInst(node->children[1]);
		}
		return;
	 
	default:
		printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
		exit (1);
	};
}

void eval(Node *node) {
	if(variables == NULL){
		variables = createListVariables();
	}
	evalInst(node);
}