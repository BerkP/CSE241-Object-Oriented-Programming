#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include"AbstractBoard.h"


namespace GTU_PKGZ{
	bool isSequanceGoToSolituon(const AbstractBoard* const arrayOfBoards[], int size);
	/* Takes an array of AbstractBoard pointers and returns true */ 
	/*if the array contains a valid sequence of moves for a solution */
}

#endif