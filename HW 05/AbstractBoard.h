#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include<iostream>
#include<fstream>

using namespace std;

namespace GTU_PKGZ{
	class AbstractBoard{
	public:
		AbstractBoard(int  , int );
		/* Constructer for abstract class. Sets privete datas*/
		virtual ~AbstractBoard(){};
		/* Destructor */
		void print()const;
		/* Prints the board on screen */
		void readFromFile(ifstream& );
		/*Reads the board from the file given as function parameter */
		void writeToFile(ofstream& );
		/* Writes the board to the file given as function parameter */
		virtual void setSize(int  , int );
		/*Sets the board size to given values. The values are given as parameters  */
		void reset();
		/*Resets the board to the solution. */
		bool move(char );
		/*Makes a move according to the given char parameter */
		bool isSolved()const;
		/*Returns true if the board is a solution */
		virtual int& operator()(int ,int ) =0;
		virtual const int& operator()(int ,int )const =0;
		/* Takes two indexes and returns the corresponding cell content*/
		bool operator==(const AbstractBoard&) const;
		/* Two boards are equal, if the boards are the same*/
		static int NumberOfBoards();
		char lastMove()const;
		int numberOfMoves()const;

		bool isCellValid(const int& ,const int&)const;
		int getRowSize()const;
		int getColumnSize()const;
		int getCurrentRow()const;
		int getCurrentColumn()const;
		void setLastMove(char);
		static void increaseTotalBoard();

	private:
		void setSizeFromFile(ifstream& inputFile);
		int stringToBoardCell(string str)const;

		bool isCellANumber(const int&)const;
		bool isCellADigit(const int&)const;
		bool isCellAForbiddenCell(const int&)const;
		void resetTotalMove();
		void resetLastMove();
		void swapNumbers(int &,int&);
		bool isMoveUnvalid(const int&, const int&)const;

	private:
		int totalRow;
		int totalColumn;
		int currentRow;
		int currentColumn;
		char lastMoveChar;
		int totalMove;
		static int totalBoard;
		static const int BLANK_SPACE = -1 ,
				 		 FORBIDDEN_CELL = -2;
		/*Constants to use as cell contents */		 		 
	};
}


#endif

