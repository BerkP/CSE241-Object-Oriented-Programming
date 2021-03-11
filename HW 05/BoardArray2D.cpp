#include "BoardArray2D.h"

namespace GTU_PKGZ{

	BoardArray2D::BoardArray2D():BoardArray2D(3,3){}
	//default constructer

	BoardArray2D::BoardArray2D(int rowInput, int columnInput):AbstractBoard(rowInput,columnInput),Board(nullptr){
		setSize(rowInput,columnInput);
		reset();
	}

	BoardArray2D::BoardArray2D(const BoardArray2D& other):AbstractBoard(other),Board(nullptr){
		increaseTotalBoard();
		this->setSize(getRowSize(),getColumnSize());
		for(int i=0; i < getRowSize(); i++){
			for(int j=0; j< getColumnSize(); j++){
				Board[i][j] = other.Board[i][j];
			}
		}
	}


	BoardArray2D::~BoardArray2D(){
		emptyBoard();
	}

	const BoardArray2D& BoardArray2D::operator=(const BoardArray2D& other){
		if(this == &other)
			return *this;

		emptyBoard();
		AbstractBoard::operator=(other);
		setSize(getRowSize(),getColumnSize());

		for(int i=0; i < getRowSize(); i++){
			for(int j=0; j< getColumnSize(); j++){
				Board[i][j] = other.Board[i][j];
			}
		}
		
		return *this;
	}

	void BoardArray2D::emptyBoard(){
			for(int i=0; i < getRowSize(); i++){
				delete [] Board[i];
			}
			delete [] Board;
			Board = nullptr;
	}

	void BoardArray2D::setSize(int rowInput,int columnInput){
		AbstractBoard::setSize(rowInput,columnInput);
		if(Board != nullptr){
			delete [] Board;
		}

		Board = new int*[rowInput];
		for(int i=0; i < rowInput; i++){
			Board[i] = new int[columnInput];
		}
		reset();
	}

	int& BoardArray2D::operator()(int row,int column){
		if( !isCellValid(row,column))
			exit(1);
		return Board[row][column];
	}

	const int& BoardArray2D::operator()(int row,int column)const{
		if( !isCellValid(row,column))
			exit(1);
		return Board[row][column];
	}
}