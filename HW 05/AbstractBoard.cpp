#include <cmath>  // using pow()
#include "AbstractBoard.h"

namespace GTU_PKGZ{

	int AbstractBoard::totalBoard=0; 

	AbstractBoard::AbstractBoard(int rowInput , int columnInput):lastMoveChar('S'),totalMove(0){
			increaseTotalBoard();
			setSize(rowInput,columnInput);
	}

	void AbstractBoard::readFromFile(ifstream& inputFile){
		setSizeFromFile(inputFile);
		string str;

		for(int i=0 ; i < getRowSize() ; i++ ){							// loop for initialize the board according to game size 
			for(int j=0 ; j < getColumnSize() ; j++){
				inputFile >> str;
				this->operator()(i,j) = stringToBoardCell(str);
				if(this->operator()(i,j) == BLANK_SPACE){
					currentRow=i;
					currentColumn=j;
				}
			}
		}

	}

	void AbstractBoard::writeToFile(ofstream& outputFile){
		for(int i=0 ; i < totalRow ; i++){
			for(int j=0 ; j < totalColumn ; j++){
				if(isCellANumber(this->operator()(i,j))){		//checking for blank space or forbidden cell
					if ( isCellADigit(this->operator()(i,j))) 	//checking for one digit intiger. if it is put a '0' before it to look '01'
						outputFile << "0";
					outputFile << this->operator()(i,j)<< " " ;
				}	
				else if(isCellAForbiddenCell(this->operator()(i,j)))
					outputFile << "00 "; 
				else 
					outputFile << "bb " ;
			}
			outputFile << endl; 
		}

	}




	void AbstractBoard::setSizeFromFile(ifstream& inputFile){
		string str;
		int rowCounter =0,columnCounter=1;

		getline(inputFile,str);		
		for(int i=0 ; str[i] != '\0' ; i++){  					
			if(str[i] == ' ' && str[i+1] !=' ' && str[i+1] !='\0' ){	//progressing on line to find column size
				columnCounter++;
			}
		}
		while(!inputFile.eof()){
			rowCounter++;
			getline(inputFile,str);
		}	
		setSize(rowCounter,columnCounter);
		inputFile.clear();												// returning to the beginning of file
		inputFile.seekg(0, ios::beg);
	}

	void AbstractBoard::setSize(int rowInput , int columnInput){
		totalRow=rowInput;
		totalColumn=columnInput;
	}

	bool AbstractBoard::move(char moveOperator){
		auto moveStatus = true;  										//initiliazing the flag as false
		int postMoveRow = currentRow , 
			postMoveColumn = currentColumn;
		switch(moveOperator){
			case 'U':
			case 'u':
				postMoveRow -= 1;
				break;
			case 'D':
			case 'd':
				postMoveRow += 1;
				break;
			case 'R':
			case 'r':
				postMoveColumn += 1;
				break;
			case 'L':
			case 'l':
				postMoveColumn -= 1;
				break;			
		}
		if( isMoveUnvalid(postMoveRow,postMoveColumn) ){
			moveStatus = false;
		}
		if(moveStatus != false){
			swapNumbers(this->operator()(currentRow,currentColumn) , this->operator()(postMoveRow,postMoveColumn));
			currentRow = postMoveRow; 
			currentColumn = postMoveColumn;
			setLastMove(moveOperator);
			totalMove++;
		}
		return moveStatus;
	}

	void AbstractBoard::swapNumbers(int& numberOne , int& numberTwo){
		int backupNumber;
		backupNumber = numberOne ;
		numberOne = numberTwo ; 
		numberTwo = backupNumber;
	}

	void AbstractBoard::reset(){
		int counter = 1 ;							
		for(int i=0 ; i < totalRow ; i++ ){				// loop for initialize the board according to game size 
			for(int j=0 ; j < totalColumn ; j++){
				if(!isCellAForbiddenCell(this->operator()(i,j))){
					this->operator()(i,j)= counter;
					counter++;
				}
			}
		}
		currentRow = totalRow-1;
		currentColumn = totalColumn-1;
		this->operator()(currentRow,currentColumn) = BLANK_SPACE;
		resetLastMove();
		resetTotalMove();
	}

	bool AbstractBoard::isSolved()const{
		bool solvedStatus = true; 																							//setting true at start. if it is not i t will change later
		int counter = 1 ;
		for(int i=0 ; i < getRowSize() ; i++){		
			for(int j=0 ; j < getColumnSize() ; j++){
				if( this->operator()(i,j) != FORBIDDEN_CELL ){																// skipping the forbidden places
					if( this->operator()(getRowSize()-1,getColumnSize()-1) != BLANK_SPACE) 									// first of all checking right down corner. if its not -1(blank space) return as game is not finished
						solvedStatus = false; 
					else if ( !( i == (getRowSize()-1) && j == (getColumnSize()-1) ) && this->operator()(i,j) != counter )	// checking non-forbidden places in order with counter
						solvedStatus = false;
					counter++ ; 
				}
			}
		}
		return solvedStatus;
	}

	bool AbstractBoard::operator==(const AbstractBoard& other)const{
		if(getRowSize() != other.getRowSize() && getColumnSize() != other.getColumnSize())
			return false;

		for(int i=0 ; i < totalRow ; i++){
			for(int j=0 ; j < totalColumn ; j++){
				if(this->operator()(i,j) != other.operator()(i,j)){
					return false;
				}
			} 
		}
		return true;
	}

	void AbstractBoard::print()const{
		for(int i=0 ; i < totalRow ; i++){
			for(int j=0 ; j < totalColumn ; j++){
				if(isCellANumber(this->operator()(i,j))){		//checking for blank space or forbidden cell
					if ( isCellADigit(this->operator()(i,j))) 	//checking for one digit intiger. if it is put a '0' before it to look '01'
						cout << "0";
					cout << this->operator()(i,j)<< " " ;
				}	
				else if(isCellAForbiddenCell(this->operator()(i,j)))
					cout << "00 "; 
				else 
					cout << "bb " ;
			}
			cout << endl; 
		}
	}

	void AbstractBoard::setLastMove(char moveOperator){
		lastMoveChar=moveOperator;
	}

	bool AbstractBoard::isCellValid(const int& row,const int& column)const{
		return row < getRowSize() && row >= 0 && column < getColumnSize() && column >= 0;
	}

	bool AbstractBoard::isMoveUnvalid(const int& postMoveRow , const int& postMoveColumn)const{
		return postMoveRow > getRowSize()-1 || postMoveRow < 0 || postMoveColumn > getColumnSize()-1 || postMoveColumn < 0 
				|| isCellAForbiddenCell(this->operator()(postMoveRow,postMoveColumn));
	}

	bool AbstractBoard::isCellANumber(const int& cellIndex)const{
		return (cellIndex != BLANK_SPACE  && cellIndex != FORBIDDEN_CELL);
	}

	bool AbstractBoard::isCellADigit(const int& cellIndex)const{
		return (cellIndex < 10 && cellIndex > -1);
	}

	bool AbstractBoard::isCellAForbiddenCell(const int& cellIndex)const{
		return (cellIndex == FORBIDDEN_CELL);
	}

	int AbstractBoard::getRowSize()const{
		return totalRow;
	}

	int AbstractBoard::getColumnSize()const{
		return totalColumn;
	}
	int AbstractBoard::getCurrentRow()const{
		return currentRow;
	}
	int AbstractBoard::getCurrentColumn()const{
		return currentColumn;
	}

	void AbstractBoard::resetLastMove(){
		lastMoveChar = 'S';
	}

	void AbstractBoard::resetTotalMove(){
		totalMove = 0;
	}

	void AbstractBoard::increaseTotalBoard(){
		totalBoard++;
	}

	int AbstractBoard::NumberOfBoards(){
		return totalBoard;
	}

	char AbstractBoard::lastMove()const{
		return lastMoveChar;
	}

	int AbstractBoard::numberOfMoves()const{
		return totalMove;
	}

	int AbstractBoard::stringToBoardCell(string str)const{
		int input_intiger = 0 , counter;	
		for( counter = 0 ; str[counter] != '\0' ; counter++){
			if( str[counter] < '0' || str[counter] > '9' )				//checking that is character a digit
				return BLANK_SPACE;  									// BLANK_SPACE means this string cannot be converted to intiger because its sth like bb	
		}
		for( int i = 0 ; str[i] != '\0' ; i++){
			input_intiger += (str[i] - '0') * pow( 10 , counter -1 ); 	// multiplying the digits with power of ten
			counter--;
		}
		if(input_intiger == 0) 	return FORBIDDEN_CELL;
		else					return input_intiger;
	}

}