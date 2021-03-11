#include"AbstractBoard.h"

using namespace GTU_PKGZ;


namespace { 
/* Unnamed namespace for helper functions */
	bool isCellOneOfTheBlankSpaces(const AbstractBoard& board1 , const AbstractBoard& board2 , int row , int column);
	bool isBlankSpacesConsecutive(int rowDistance , int columnDistance);
	bool isSizesOfBoardsSame(const AbstractBoard& board1, const AbstractBoard& board2);
	bool isMoveBetweenTwoBoardsValid(const AbstractBoard& board1 , const AbstractBoard& board2);
}

namespace GTU_PKGZ{
	bool isSequanceGoToSolituon(const AbstractBoard* const arrayOfBoards[], int size){
	/* Takes an array of AbstractBoard pointers and returns true */ 
	/*if the array contains a valid sequence of moves for a solution */
		if(!arrayOfBoards[size-1]->isSolved())
			return false;

		for(int i=0 ; i < size-1 ; i++){
			if( !isMoveBetweenTwoBoardsValid(*arrayOfBoards[i],*arrayOfBoards[i+1])){
				return false;
			}
		}
		return true;
	}
}


namespace {
/* Unnamed namespace for helper functions */
	bool isCellOneOfTheBlankSpaces(const AbstractBoard& board1 , const AbstractBoard& board2 , int row , int column){
		return ((row==board1.getCurrentRow() && column==board1.getCurrentColumn()) || (row==board2.getCurrentRow() && column==board2.getCurrentColumn()));
	}

	bool isBlankSpacesConsecutive(int rowDistance , int columnDistance){
		return (((rowDistance==-1 || rowDistance==1) && columnDistance==0) || ((columnDistance==-1 || columnDistance==1) && rowDistance==0));
	}

	bool isSizesOfBoardsSame(const AbstractBoard& board1, const AbstractBoard& board2){
		return (board1.getRowSize() == board2.getRowSize() && board1.getColumnSize() == board2.getColumnSize());
	}


	bool isMoveBetweenTwoBoardsValid(const AbstractBoard& board1 , const AbstractBoard& board2){
		if (!isSizesOfBoardsSame(board1,board2))
			return false;

		int rowDistance = board1.getCurrentRow() - board2.getCurrentRow();
		int columnDistance = board1.getCurrentColumn() - board2.getCurrentColumn();

		if( !isBlankSpacesConsecutive(rowDistance,columnDistance))
			return false;

		for(int row=0; row<board1.getRowSize(); row++){
			for(int column=0; column<board1.getColumnSize(); column++){
				if( !isCellOneOfTheBlankSpaces(board1,board2,row,column) && board1.operator()(row,column) != board2.operator()(row,column))
					return false;
			}
		}
		return true;
	}

}