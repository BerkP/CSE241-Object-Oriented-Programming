#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<string>
#include<fstream>
#include"NPuzzle.h"

using namespace std;

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

void NPuzzle::solvePuzzle(){
	const int 	MAX_MOVE_SIZE = 100000,												// setting constants
				SHUFFLE_SIZE = 5;										//random move(shuffle) size
	auto gameFinished = false ;
	decltype(gameFinished) moveStatus;	
	int counter =0;																//setting counter as 0 at start
	while( counter < MAX_MOVE_SIZE && gameFinished != true){ 					// loop will continue until MAXMOVE or gameFinished
		moveStatus = boardObj.moveIntelligent();
		if(moveStatus != true){
			for(int i=0 ; i < SHUFFLE_SIZE ; i++){
				moveRandom();
				counter++;
			}
		}
		else{
			cout << endl ;
			counter++;
		}
		boardObj.print();
		cout << endl;
		gameFinished = boardObj.isSolved();
		if( gameFinished == true ) 
			cout << endl << "Solved!" << endl ;
	}
	if(gameFinished != true)
		cout << endl <<  MAX_MOVE_SIZE << " move has done and couldnt found yet!" << endl ;
	moveCount += counter;
}

void NPuzzle::moveIntelligent(){
	if(boardObj.moveIntelligent()  == false)
		cout << endl << "Intelligent move cannot found!" << endl;
	else
		moveCount++;
}


bool NPuzzle::Board::moveIntelligent(){
	int minMove = totalRow * totalColumn ;  // setting min as max at start to compare with others
	auto moveStatus = true; 				// setting as true at start if it is not it will change later
	char moveOperator = '0'; 				// '0' is default
	if( NPuzzle::Board::moveComparator(currentRow-1 , currentColumn , minMove) == true) // checking each way
		moveOperator = 'U';
	if( NPuzzle::Board::moveComparator(currentRow+1 , currentColumn , minMove) == true)
		moveOperator = 'D';
	if( NPuzzle::Board::moveComparator(currentRow , currentColumn-1 , minMove) == true)
		moveOperator = 'L';
	if( NPuzzle::Board::moveComparator(currentRow , currentColumn+1 , minMove) == true)
		moveOperator = 'R';

	if(moveOperator != '0'){				// it means there is no intelligent move
		NPuzzle::Board::move(moveOperator);
		cout << endl << "Intelligent move chooses " << moveOperator << endl;
	}
	else 
		moveStatus = false;
	return moveStatus;
}

bool NPuzzle::Board::moveComparator(int rowOfNumber , int columnOfNumber , int& minMove){
	int moveCount;
	auto isNumberAvliable = false;			//setting false at start, if it is it will change later
	if( !(rowOfNumber > totalRow-1 || rowOfNumber < 0 || columnOfNumber > totalColumn-1 || columnOfNumber < 0 || boardArr[rowOfNumber][columnOfNumber] == FORBIDDEN_CELL) ){	
	// checking for border
		moveCount = NPuzzle::Board::moveCalculator( boardArr[rowOfNumber][columnOfNumber] , currentRow , currentColumn ) ;  
		if ( moveCount < NPuzzle::Board::moveCalculator( boardArr[rowOfNumber][columnOfNumber], rowOfNumber , columnOfNumber)  &&   moveCount < minMove ){
			//finding the most close possibility to move and this will not move the better placed number
			minMove = moveCount;
			isNumberAvliable = true;
		}
	}
	return isNumberAvliable;
}

int NPuzzle::Board::moveCalculator( int number , int rowOfNumber , int columnOfNumber){
	int rowCounter , columnCounter , actualRow , actualColumn , counter = 0;
	for(int i=0 ; i < totalRow ; i++){					// this double loop finds actual row and actual column 
		for(int j=0 ; j < totalColumn ; j++){
			if(boardArr[i][j] != FORBIDDEN_CELL ){
				counter++;
				if(counter == number){
					actualRow = i;
					actualColumn = j;
				}
			}	
		}
	}
	rowCounter = rowOfNumber - actualRow ;
	if (rowCounter < 0 )	rowCounter *= -1;
	columnCounter = columnOfNumber - actualColumn ;
	if (columnCounter < 0 )	columnCounter *= -1;
	return rowCounter + columnCounter ;  // this returns the  how many moves away from the actual place
}


void NPuzzle::printReport()const{
	auto solvedStatus = boardObj.isSolved();
	cout << endl << moveCount << " move has been done!" << endl
		 << "Puzzle is " ;
	if(solvedStatus == true)
		cout << "Solved!" << endl << endl;
	else 
		cout << "not solved yet!" << endl << endl;
}

bool NPuzzle::Board::isSolved()const{ 
	bool solvedStatus = true; 																		//setting true at start. if it is not i t will change later
	int counter = 1 ;
	for(int i=0 ; i < totalRow ; i++){		
		for(int j=0 ; j < totalColumn ; j++){
			if( boardArr[i][j] != FORBIDDEN_CELL ){																// skipping the forbidden places
				if( boardArr[totalRow-1 ][totalColumn-1 ] != -1 ) 									// first of all checking right down corner. if its not -1(blank space) return as game is not finished
					solvedStatus = false; 
				else if ( !( i == (totalRow-1) && j == (totalColumn-1) ) && boardArr[i][j] != counter ) // checking non-forbidden places in order with counter
					solvedStatus = false;
				counter++ ; 
			}
			
		}
	}
	return solvedStatus;
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
}

void NPuzzle::shuffle(){
	int shuffleSize = boardObj.getShuffleSize();
	NPuzzle::reset();
	for(int i=0 ; i < shuffleSize ; i++){
		moveRandom();
	}
}

int NPuzzle::Board::getShuffleSize()const{
	return totalRow*totalColumn;
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
}


void NPuzzle::print()const{
	boardObj.print();
}

void NPuzzle::Board::print()const{
	for(int i=0 ; i < totalRow ; i++){
		for(int j=0 ; j < totalColumn ; j++){
			if(boardArr[i][j] != BLANK_SPACE  && boardArr[i][j] != FORBIDDEN_CELL ){	//checking for blank space or forbidden cell
				if ( boardArr[i][j] < 10 && boardArr[i][j] > -1 ) cout << "0" ;			//checking for one digit intiger. if it is put a '0' before it to look '01'
				cout << boardArr[i][j] << " " ;
			}	
			else if( boardArr[i][j] == FORBIDDEN_CELL)
				cout << "00 "; 
			else 
				cout << "bb " ;
		}
		cout << endl; 
	}
}

void NPuzzle::writeToFile(string fileName)const{
	boardObj.writeToFile(fileName);
}

void NPuzzle::Board::writeToFile(string fileName)const{
	ofstream outputFile;
	outputFile.open(fileName);
	for(int i=0 ; i < totalRow ; i++){
		for(int j=0 ; j < totalColumn ; j++){
			if(boardArr[i][j] != BLANK_SPACE  && boardArr[i][j] != FORBIDDEN_CELL ){
				if ( boardArr[i][j] < 10 && boardArr[i][j] > -1 ) outputFile << "0" ;
				outputFile << boardArr[i][j] ;		// last number is blank space and checking for blank place
			}
			else if( boardArr[i][j] == FORBIDDEN_CELL)
				outputFile << "00"; 	
			else 
				outputFile << "bb" ;
			if( j != totalColumn -1 ) 		// this check for end of line. if it is not prints " ". if program doesnt do that the file which created cannot be loadable again
				outputFile << " " ;			// because program detect '\n'
		}
		outputFile << endl; 
	}
	outputFile.close();
	cout << "Configuration saved!" << endl;
}

void NPuzzle::readFromFile(string fileName){
	boardObj.readFromFile(fileName);
	moveCount = 0;					//reseting the move count
}

void NPuzzle::Board::readFromFile(string fileName){
	int inputIntiger , numberOfRow=0 , numberOfCOlumn=0;
	string inputString;
	char s;		// char for detecting ' ' or '\n'
	ifstream sourceFile;		
	do{	
		sourceFile.open(fileName);
		if(sourceFile.fail()){  
			cout << "Input file connot found! Try again!" << endl;
			cin >> fileName;
		}	
	}while( sourceFile.fail() );		// checking valid input file
	sourceFile >> inputString; // first input is outside of the loop because of use of .eof() .
	sourceFile.get(s);			// geting a char to know end of line
	while(!sourceFile.eof()){
		inputIntiger = NPuzzle::stringCheckerAndConverter(inputString);  	// checking that is string convertable to int  and if it is convert. if itsn returns -1 as nonintiger
		if (inputIntiger == -1 ){									//checking if input is string(bb or smth else)
			if(inputString == "bb"){
				boardArr[numberOfRow][numberOfCOlumn] = BLANK_SPACE;
				currentRow = numberOfRow;
				currentColumn = numberOfCOlumn;
			}
		}
		else if(inputIntiger == 0)									//checking for '0'. if it is '0', it means forbidden cell
			boardArr[numberOfRow][numberOfCOlumn] = FORBIDDEN_CELL;
		else{
			boardArr[numberOfRow][numberOfCOlumn] = inputIntiger; // placing the number into the board
		}
		numberOfCOlumn++; 										// after each input in a row
		if(s == '\n'){
			numberOfRow++;										// after end of line increasing the totalRow
			totalRow = numberOfRow;								// total row will be return as last totalRow
			totalColumn = numberOfCOlumn;						// total column will be return as last totalRow
			numberOfCOlumn = 0;									// reseting number of column after end of line
		} 
		sourceFile >> inputString;								//geting input for next loop
		sourceFile.get(s);										//getting char for next loop
	}
	sourceFile.close();
}

void NPuzzle::reset(){
	boardObj.reset();
	moveCount = 0; 												//reseting moveCount
}

void NPuzzle::Board::reset(){
	int counter = 1 ;							
	for(int i=0 ; i < totalRow ; i++ ){				// loop for initialize the board according to game size 
		for(int j=0 ; j < totalColumn ; j++){
			if(boardArr[i][j] != FORBIDDEN_CELL ){
				boardArr[i][j]= counter;
				counter++;
			}
		}
	}
	currentRow = totalRow-1;
	currentColumn = totalColumn-1;
	boardArr[currentRow][currentColumn] = BLANK_SPACE;
}

void NPuzzle::move(char moveOperator){
	int moveStatus = boardObj.move(moveOperator);
	if (moveStatus == true)
		moveCount++;
	else
		cout << endl << "You cannot move this way!" << endl ;
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
	if( postMoveRow > totalRow-1 || postMoveRow < 0 || postMoveColumn > totalColumn-1 || postMoveColumn < 0 || boardArr[postMoveRow][postMoveColumn] == FORBIDDEN_CELL){
		moveStatus = false;
	}
	if(moveStatus != false){
		swapNumbers(boardArr[currentRow][currentColumn] , boardArr[postMoveRow][postMoveColumn]);
		currentRow = postMoveRow; 
		currentColumn = postMoveColumn;
	}
	return moveStatus;
}