#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>
#include"NPuzzle.h"



void NPuzzle::printReport()const{			// prints the current board situation
	auto solvedStatus = boardObj.isSolved();
	cout << endl << boardObj.numberOfMoves() << " move has been done!" << endl
		 << "Puzzle is " ;
	if(solvedStatus == true)
		cout << "Solved!" << endl << endl;
	else 
		cout << "not solved yet!" << endl << endl;
}

void NPuzzle::writeToFile(string fileName){	//prints the current board to file
	ofstream sourceFile;
	do{	
		sourceFile.open(fileName);
		if(sourceFile.fail()){  
			cout << "Input file connot found! Try again!" << endl;
			cin >> fileName;
		}	
	}while( sourceFile.fail() );		// checking valid input file
	boardObj.writeToFile(*this,sourceFile);
	sourceFile.close();
}

void NPuzzle::Board::writeToFile(const NPuzzle& gameBoard , ostream& sourceFile){
	sourceFile << gameBoard; 			//sending current game object to ostream object
}	

istream& operator>>(istream& sourceFile , NPuzzle& gameBoard){
	int inputIntiger , numberOfRow=0 , numberOfCOlumn=0;
	string inputString;
	char s;		// char for detecting ' ' or '\n'
	gameBoard.boardObj.resetBoardVec();
	vector<int> rowVec;
	sourceFile >> inputString; 		// first input is outside of the loop because of use of .eof() .
	sourceFile.get(s);				// geting a char to know end of line
	while(!sourceFile.eof()){
		inputIntiger = NPuzzle::stringCheckerAndConverter(inputString);  	// checking that is string convertable to int  and if it is convert. if itsn returns -1 as nonintiger
		if (inputIntiger == -1 ){									//checking if input is string(bb or smth else)
			if(inputString == "bb"){
				rowVec.push_back(-1);
				gameBoard.boardObj.setCurrentRow(numberOfRow);
				gameBoard.boardObj.setCurrentColumn(numberOfCOlumn);
			}
		}
		else if(inputIntiger == 0)									//checking for '0'. if it is '0', it means forbidden cell
			rowVec.push_back(-2);
		else{
			rowVec.push_back(inputIntiger); // placing the number into the board
		}
		numberOfCOlumn++; 										// after each input in a row
		if(s == '\n'){
			numberOfRow++;										// after end of line increasing the totalRow
			gameBoard.boardObj.setTotalRow(numberOfRow);		// total row will be return as last totalRow
			gameBoard.boardObj.setTotalColumn(numberOfCOlumn);// total column will be return as last totalRow
			numberOfCOlumn = 0;									// reseting number of column after end of line
			gameBoard.boardObj.pushVec(rowVec);					// pushing readed row to board					
			rowVec.clear();										// reseting the row vec to read the next line
		} 
		sourceFile >> inputString;								//geting input for next loop
		sourceFile.get(s);										//getting char for next loop
	}
	return sourceFile;
}

ostream& operator<<(ostream& osObj ,const NPuzzle& gameBoard){
	for(int i=0 ; i < gameBoard.boardObj.getTotalRow() ; i++){
		for(int j=0 ; j < gameBoard.boardObj.getTotalColumn() ; j++){
			if(gameBoard.boardObj(i,j) != -1  && gameBoard.boardObj(i,j) != -2 ){					//checking for blank space or forbidden cell
				if ( gameBoard.boardObj(i,j) < 10 && gameBoard.boardObj(i,j) > -1 ) osObj << "0" ;	//checking for one digit intiger
				osObj << gameBoard.boardObj(i,j) ;
			}	
			else if( gameBoard.boardObj(i,j) == -2)
				osObj << "00"; 
			else 
				osObj << "bb" ;
			if( j != gameBoard.boardObj.getTotalColumn() -1 ) 
				osObj << " " ;	
		}
		osObj << endl; 
	}
	return osObj;
}



bool NPuzzle::Board::operator==(const Board otherBoardObj)const{
	if(boardVec == otherBoardObj.boardVec) // checking the equality of two vectors
		return true;
	else 
		return false;
}

void NPuzzle::goBackFromSolvedPuzzle(){
	vector<char> moveList;  									// a vector for stroing the move will be executed
	char tempMoveOperator;										// temp char for move operator
	Board* tempBoardObj = &boardObjVec[boardObjVec.size()-1];	// creating a board pointer for temp Board Object

	for(int i=boardObjVec.size()-1 ; i > 0 ; i--){				// loop for going back from end of board vec
		if(boardObjVec[i] == (*tempBoardObj) ){		
			tempBoardObj=&boardObjVec[i];
			tempMoveOperator=tempBoardObj->lastMove();			// taking the last move of that board
			moveList.push_back(tempMoveOperator);				// storing that move to vector
			tempBoardObj->reverseMove(tempMoveOperator);		// doing reverse move to find previous board
		}
	}
	for(int i= moveList.size() -1 ; i >=0 ; i--){				// loop for making the stored moves to the actual board
		cout << "Next move is " << moveList[i] << endl;
		boardObj.move(moveList[i]);
		print();												// printing the board
	}
}

void NPuzzle::solvePuzzle(){
	int indexCounter=0;
	auto solutionFound = false;
	while(solutionFound != true){
		// making the 4 way moves in order. if one of them has found the solituon, others wont executed
		solutionFound= createObjectForVector(indexCounter,'U');
		if(solutionFound !=true){
			solutionFound= createObjectForVector(indexCounter,'D');
			if(solutionFound !=true){
				solutionFound= createObjectForVector(indexCounter,'L');
				if(solutionFound !=true){
					solutionFound= createObjectForVector(indexCounter,'R');
				}
			}	
		}
		indexCounter++;
	}
	goBackFromSolvedPuzzle(); 
	int minMove= boardObj.numberOfMoves() - boardObjVec[0].numberOfMoves();
	cout << endl << "Puzzle solved with  " << minMove << " move!" << endl <<  endl ;
	boardObjVec.resize(0);				// reseting the boardVec after the algorithm executed
	boardObjVec.push_back(boardObj);
}

bool NPuzzle::checkForDuplicate(const Board& tempBoardObj ,const int& indexNumber)const{
	int numberOfTotalIndex = boardObjVec.size();
	for(int i=0 ; i < numberOfTotalIndex ; i++){	// loop for checking all vector to find duplicate
		if(boardObjVec[i] ==tempBoardObj )
			return false;
	}
	return true;
}

bool NPuzzle::createObjectForVector(const int& indexNumber , char moveOperator){
	Board tempBoardObj = boardObjVec[indexNumber];
	if(tempBoardObj.move(moveOperator) == true){					//checking that is move executable
		if(checkForDuplicate(tempBoardObj , indexNumber)==true){	//checking for duplicate
			boardObjVec.push_back(tempBoardObj);					// if other two condition is ok, push the board to vector
			if(tempBoardObj.isSolved() == true){					// checking for solition
				return true;
			}
		}
	}	
	return false;
}

bool NPuzzle::Board::isSolved()const{ 
	bool solvedStatus = true; 																		//setting true at start. if it is not i t will change later
	int counter = 1 ;
	for(int i=0 ; i < totalRow ; i++){		
		for(int j=0 ; j < totalColumn ; j++){
			if( boardVec[i][j] != FORBIDDEN_CELL ){																// skipping the forbidden places
				if( boardVec[totalRow-1 ][totalColumn-1 ] != -1 ) 									// first of all checking right down corner. if its not -1(blank space) return as game is not finished
					solvedStatus = false; 
				else if ( !( i == (totalRow-1) && j == (totalColumn-1) ) && boardVec[i][j] != counter ) // checking non-forbidden places in order with counter
					solvedStatus = false;
				counter++ ; 
			}
			
		}
	}
	return solvedStatus;
}	

void NPuzzle::Board::resetMoveCount(){
	moveCount = 0;
}

void NPuzzle::Board::resetLastMove(){
	lastMoveChar = 'S' ;
}

void NPuzzle::shuffle(){
	int shuffleSize = boardObj.getShuffleSize();
	NPuzzle::reset();
	for(int i=0 ; i < shuffleSize ; i++){
		moveRandom();
	}
	boardObj.resetMoveCount();
	boardObjVec.resize(0);
	boardObjVec.push_back(boardObj);
	cout << endl << "Shuffled!" << endl ;
}

int NPuzzle::Board::getShuffleSize(){
	return totalRow*totalColumn;
}

void NPuzzle::moveRandom(){
	auto moveCheck = false;
	int randomNumber;
	while(moveCheck != true){
		randomNumber = rand() %4 ;					//there are four ways and this is for rondomize 
		switch(randomNumber){						// making the random move according to the random number which decided above
			case 0 :
				moveCheck = boardObj.move('U');
				break;
			case 1 :
				moveCheck = boardObj.move('D');
				break;
			case 2 :
				moveCheck = boardObj.move('R');
				break;
			case 3 :
				moveCheck = boardObj.move('L');
				break;
		}
	}
	boardObjVec.resize(0);
	boardObjVec.push_back(boardObj);
}

void NPuzzle::readFromFile(string fileName){
	ifstream sourceFile;
	do{	
		sourceFile.open(fileName);
		if(sourceFile.fail()){  
			cout << "Input file connot found! Try again!" << endl;
			cin >> fileName;
		}	
	}while( sourceFile.fail() );		// checking valid input file
	boardObj.readFromFile(*this,sourceFile);
	sourceFile.close();
	boardObjVec.resize(0);
	boardObjVec.push_back(boardObj);
}

void NPuzzle::Board::readFromFile(NPuzzle& gameBoard , istream& sourceFile){
	sourceFile >> gameBoard; 								// using the overloaded operator
}

void NPuzzle::move(char moveOperator){
	int moveStatus = boardObj.move(moveOperator);
	if (moveStatus == true){
		boardObjVec.resize(0);
		boardObjVec.push_back(boardObj);
	}	
	else
		cout << endl << "You cannot move this way!" << endl ;
}

void NPuzzle::Board::reverseMove(char moveOperator){
	// moving opposite way of input
	switch(moveOperator){
		case 'U':
		case 'u':
			move('D');
			break;
		case 'D':
		case 'd':
			move('U');
			break;
		case 'R':
		case 'r':
			move('L');
			break;
		case 'L':
		case 'l':
			move('R');
			break;			
	}
}

bool NPuzzle::Board::move(char moveOperator){
	auto moveStatus = true;  					//initiliazing the flag as false
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
	if( postMoveRow > totalRow-1 || postMoveRow < 0 || postMoveColumn > totalColumn-1 || postMoveColumn < 0 || boardVec[postMoveRow][postMoveColumn] == FORBIDDEN_CELL){
		moveStatus = false;
	}
	if(moveStatus != false){
		swapNumbers(boardVec[currentRow][currentColumn] , boardVec[postMoveRow][postMoveColumn]);
		currentRow = postMoveRow; 
		currentColumn = postMoveColumn;
		moveCount++;
		lastMoveChar = moveOperator;
	}
	return moveStatus;
}

void NPuzzle::reset(){
	boardObj.reset();
	boardObjVec.resize(0);
}

void NPuzzle::print()const{
	cout << *this;  					// using overloaded operator and sending the current Npuzzle object to cout
}

void NPuzzle::Board::print()const{  	// this func can print any board unlike "<< operator overload". << operator can only prints the main game board.
	for(int i=0 ; i < totalRow ; i++){
		for(int j=0 ; j < totalColumn ; j++){
			if(boardVec[i][j] != BLANK_SPACE  && boardVec[i][j] != FORBIDDEN_CELL ){	//checking for blank space or forbidden cell
				if ( boardVec[i][j] < 10 && boardVec[i][j] > -1 ) cout << "0" ;			//checking for one digit intiger. if it is put a '0' before it to look '01'
				cout << boardVec[i][j] << " " ;
			}	
			else if( boardVec[i][j] == FORBIDDEN_CELL)
				cout << "00 "; 
			else 
				cout << "bb " ;
		}
		cout << endl; 
	}
	cout << endl << lastMoveChar << endl; 
}

void NPuzzle::Board::reset(){
	int counter = 1 ;							
	for(int i=0 ; i < totalRow ; i++ ){				// loop for initialize the board according to game size 
		for(int j=0 ; j < totalColumn ; j++){
			if(boardVec[i][j] != FORBIDDEN_CELL ){
				boardVec[i][j]= counter;
				counter++;
			}
		}
	}
	currentRow = totalRow-1;
	currentColumn = totalColumn-1;
	boardVec[currentRow][currentColumn] = BLANK_SPACE;
}

bool NPuzzle::setSize(int row , int column){
	if ( row < 3 || row > 9 || column < 3 || column > 9){
		cout << "Invalid game size! Try again!" << endl ;
		return false;
	}	
	else{
		boardObj.setSize(row,column);
		boardObj.reset();
		shuffle();
		return true;
	}
}

void NPuzzle::Board::setSize(int row , int column){
	totalRow = row;
	totalColumn = column;
	vector<int> rowVec;
	for(int i=0 ; i < totalRow ; i++ ){				// loop for initialize the board according to game size 
		rowVec.resize(0);
		for(int j=0 ; j < totalColumn ; j++){
			rowVec.push_back(0);
		}
		boardVec.push_back(rowVec);
	}
}

int NPuzzle::stringCheckerAndConverter( string str){
	int input_intiger = 0 , counter;	
	for( counter = 0 ; str[counter] != '\0' ; counter++){
		if( str[counter] < '0' || str[counter] > '9' )		//checking that is character a digit
			return -1;  									// -1 means this string cannot be converted to intiger with digits	
	}
	for( int i = 0 ; str[i] != '\0' ; i++){
		input_intiger += (str[i] - '0') * pow( 10 , counter -1 ); 	// multiplying the digits with power of ten
		counter--;
	}
	return input_intiger;
}

void NPuzzle::Board::swapNumbers(int& numberOne , int& numberTwo){
	int backupNumber;
	backupNumber = numberOne ;
	numberOne = numberTwo ; 
	numberTwo = backupNumber;
}