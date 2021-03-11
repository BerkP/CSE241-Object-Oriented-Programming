#include "BoardVector.h"

namespace GTU_PKGZ{

	BoardVector::BoardVector():BoardVector(3,3){};
	//default constructer

	BoardVector::BoardVector(int rowInput , int columnInput):AbstractBoard(rowInput,columnInput){
		setSize(rowInput,columnInput);
		reset();
	}

	void BoardVector::setSize(int rowInput,int columnInput){
		AbstractBoard::setSize(rowInput,columnInput);
		boardVec.resize(rowInput);
		for(int i=0; i < rowInput; i++){
			boardVec[i].resize(columnInput);
		}
		reset();
	}

	int& BoardVector::operator()(int row,int column){
		if( !isCellValid(row,column))
			exit(1);
		return boardVec[row][column];
	}

	const int& BoardVector::operator()(int row,int column)const{
		if( !isCellValid(row,column))
			exit(1);
		return boardVec[row][column];
	}
}