#include "BoardArray1D.h"

namespace GTU_PKGZ{

	BoardArray1D::BoardArray1D():BoardArray1D(3,3){};

	BoardArray1D::BoardArray1D(int rowInput,int columnInput):AbstractBoard(rowInput,columnInput),Board(nullptr){
		setSize(rowInput,columnInput);
		reset();
	}

	BoardArray1D::BoardArray1D(const BoardArray1D& other):AbstractBoard(other),Board(nullptr){
		increaseTotalBoard();
		setSize(other.getRowSize(),getColumnSize());

		for(int i=0; i<getRowSize()*getColumnSize() ; i++){
			Board[i]=other.Board[i];
		}
		reset();
	}
	
	BoardArray1D::~BoardArray1D(){
		delete [] Board;
	}

	void BoardArray1D::setSize(int rowInput,int columnInput){
		AbstractBoard::setSize(rowInput,columnInput);
		if(Board != nullptr)
			delete [] Board;

		Board = new int[rowInput*columnInput];
	}

	int& BoardArray1D::operator()(int row,int column){
		if( !isCellValid(row,column))
			exit(1);
		return Board[getColumnSize()*row + column];
	}

	const int& BoardArray1D::operator()(int row,int column)const{
		if( !isCellValid(row,column))
			exit(1);
		return Board[getColumnSize()*row + column];
	}

	const BoardArray1D& BoardArray1D::operator=(const BoardArray1D& other){
		if(this == &other)
			return *this;

		delete [] Board;
		Board = nullptr;
		AbstractBoard::operator=(other);
		setSize(getRowSize(),getColumnSize());

		for(int i=0; i<getRowSize()*getColumnSize() ; i++){
			Board[i]=other.Board[i];
		}
		
		return *this;
	}
}