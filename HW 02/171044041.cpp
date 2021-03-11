#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<string>
#include<fstream>

using namespace std;

#define MAX_GAME_SIZE  9 														 // setting max game size as 9 to pass 2D array to functions

void puzzle_game( int argc , char** argv ); 
int string_checker_and_converter( string str);
void initialize_board(int board[][MAX_GAME_SIZE] , int * , int * ,  int  , int );
inline void shufle( int board[][MAX_GAME_SIZE] , int * , int * , int  ,  int  , int ); 			// inline func because used in inteligent solving and it could used too many times
void print_board(int board[][MAX_GAME_SIZE], int , int );
inline bool intelligent_move(int board[][MAX_GAME_SIZE] , int * , int * , int , int , int );	// inline func because used in inteligent solving and it could used too many times
int move_calculator( int board[][MAX_GAME_SIZE] , int  , int  , int  , int , int , int );
void swap_numbers(int& , int& );
bool move_up( int board[][MAX_GAME_SIZE] , int * , int * ,int  , int );
bool move_down( int board[][MAX_GAME_SIZE] , int * , int * ,int ,int );
bool move_right( int board[][MAX_GAME_SIZE] , int * , int * ,int ,int );
bool move_left( int board[][MAX_GAME_SIZE] , int * , int * ,int ,int );
bool check_for_finish(int ,int board[][MAX_GAME_SIZE], int ,int  , int  );
int new_intelligent_solving(int board[][MAX_GAME_SIZE] , int& , int& , int  , int , int );
void report_about_board(int moveCount , bool gameFinished);
void read_board_from_file(int board[][MAX_GAME_SIZE], int&  , int& , int&  , int&  , string ); 
void print_board_to_file(int board[][MAX_GAME_SIZE], int  , int  , int  , int );  
void print_welcome();

int main( int argc , char** argv ){
	srand(time(NULL));
	puzzle_game( argc , argv );	
	return 0;
}

void puzzle_game( int argc , char** argv ){
	const int 	MIN_GAME_SIZE = 3,
				START_SHUFFLE_SIZE = 100;										// 100 is chosen for complex game. if user wants to shuffle again, it will be size*size.
	auto gameFinished = false , moveCheck = true , quitGame = false;			//check flags
	char inputMove ;
	string inputString , fileName;
	int	totalRow, totalColumn, currentRow , currentColumn , gameSize , moveCount=0 ;
	int board[MAX_GAME_SIZE][MAX_GAME_SIZE];  									// array for board
	print_welcome();
	if( argc > 1 ){																//checking if file name entered in command line
		read_board_from_file(board, totalRow,totalColumn,currentRow,currentColumn, argv[1]);
	}
	else{																		// if command line is empty starts normal
		cout << "Please enter the problem size" << endl ;
		do{
			cin >> inputString ;												//taking a string for game size input
			gameSize = string_checker_and_converter(inputString);				// checking and converting the string to intiger
			if ( gameSize < MIN_GAME_SIZE || gameSize > MAX_GAME_SIZE) 	cout << "Invalid game size! Try again!" << endl ;
		}while ( gameSize < MIN_GAME_SIZE || gameSize > MAX_GAME_SIZE)  ; 
		totalRow = gameSize;									//setting totalRow as gameSize since board is square when programs starts
		totalColumn = gameSize;									//setting totalColumn as gameSize since board is square when programs starts
		initialize_board(board,&currentRow,&currentColumn,totalRow,totalColumn);	// intialize the board as ordered
		shufle(board,&currentRow,&currentColumn,START_SHUFFLE_SIZE,totalRow,totalColumn);  // if user wants to shuffle again, it will be size*size. 
	}	
	cout << "Your initial board is" << endl;
	print_board(board,totalRow,totalColumn); 
	do{
		moveCheck = true ;			//reseting the flag
		cout << "Your move:" ;
		cin >> inputMove ;
		switch (inputMove){
			case 'l':			//double case for uppercase and lowercase letters
			case 'L':
				moveCheck = move_left(board,&currentRow,&currentColumn,totalRow ,totalColumn); 
				moveCount++;
				break;
			case 'r':	
			case 'R':
				moveCheck = move_right(board,&currentRow,&currentColumn,totalRow ,totalColumn);
				moveCount++; 
				break;
			case 'u':
			case 'U':
				moveCheck = move_up(board,&currentRow,&currentColumn,totalRow ,totalColumn);
				moveCount++;
				break;
			case 'd':
			case 'D':
				moveCheck = move_down(board,&currentRow,&currentColumn,totalRow ,totalColumn); 
				moveCount++;
				break;		
			case 's':
			case 'S':
				shufle(board,&currentRow,&currentColumn, totalRow*totalColumn ,totalRow,totalColumn);  // this time shuffle totalRow*totalColumn move according to rule ////////////////////////
				moveCount = 0;														// reseting move count
				cout << "Game has been shuffled again!" << endl ; 
				break;
			case 'i':	
			case 'I':
				intelligent_move(board, &currentRow , &currentColumn ,gameSize , totalRow,  totalColumn);  
				moveCount++;
				break;
			case 'v':
			case 'V':
				moveCount += new_intelligent_solving( board, currentRow , currentColumn , gameSize , totalRow, totalColumn);
				break;
			case 'y':
			case 'Y':
				cout << endl << "Please enter the file name" << endl;
				cin >> fileName;
				read_board_from_file(board, totalRow,totalColumn,currentRow,currentColumn,fileName);
				moveCount = 0;							// reseting move count
				break;
			case 'e':
			case 'E':
				print_board_to_file(board, totalRow,totalColumn,currentRow,currentColumn);	
				break;	
			case 't':
			case 'T':
				gameFinished = check_for_finish(gameSize,board,moveCount,totalRow,totalColumn);  
				report_about_board( moveCount , gameFinished);
				break;
			case 'q':
			case 'Q':
				quitGame = true ;												
				cout << endl << "THANKS FOR PLAYING! SEE YOU NEXT TIME!" << endl;
				break;	
			default :
				cout << "Wrong input!" << endl ;
				break;	
		}
		if(quitGame != true){
			if(moveCheck == false)		cout << "Invalid move! Try another way!" << endl ;
			print_board(board , totalRow , totalColumn); 
		}
	}while( quitGame != true );
}


int string_checker_and_converter( string str){
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

void initialize_board(int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn ,  int totalRow , int totalColumn){
	const int BLANK_SPACE = -1;
	int counter = 1 ;							
	for(int i=0 ; i < totalRow ; i++ ){				// loop for initialize the board according to game size 
		for(int j=0 ; j < totalColumn ; j++){
			board[i][j]= counter;
			counter++;
		}
	}
	*currentRow = totalRow-1;
	*currentColumn = totalColumn-1;
	board[*currentRow][*currentColumn] = BLANK_SPACE; // setting blank space as -1 
}

 inline void shufle( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int quantityOfMove , int totalRow , int totalColumn){
	int moveCheck , randomNumber;
	
	
	for( int numberOfMove=0 ; numberOfMove < quantityOfMove ; numberOfMove++){
		randomNumber = rand() %4 ;					//there are four ways and this is for rondomize 
		switch(randomNumber){						// making the random move according to the random number which decided above
			case 0 :
				moveCheck = move_up(board,currentRow,currentColumn,totalRow,totalColumn);
				break;
			case 1 :
				moveCheck = move_down(board,currentRow,currentColumn,totalRow ,totalColumn);
				break;
			case 2 :
				moveCheck = move_right(board,currentRow,currentColumn,totalRow ,totalColumn);
				break;
			case 3 :
				moveCheck = move_left(board,currentRow,currentColumn,totalRow ,totalColumn);
				break;
		}
		if( moveCheck != true )	numberOfMove -= 1;			//decreasing the current move because move couldnt happen
	}
}

void print_board(int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int totalRow, int totalColumn){
	for(int i=0 ; i < totalRow ; i++){
		for(int j=0 ; j < totalColumn ; j++){
			if(board[i][j] != -1 ){
				if ( board[i][j] < 10 && board[i][j] > -1 ) cout << "0" ;
				cout << board[i][j] << " " ;		// last number is blank space and checking for blank place
			}	
			else cout << "bb " ;
		}
		cout << endl; 
	}
}

inline bool intelligent_move(int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize , int totalRow, int totalColumn){
	char moveOperator;
	int minMove = MAX_GAME_SIZE * MAX_GAME_SIZE , moveCount; // minMove is max move at start so after the calculations we'll find the min 
	auto moveStatus = true;
	
	if( *currentRow  != 0 && board[*currentRow -1 ][*currentColumn] != 0 ){									// checking the upper border
		moveCount = move_calculator( board,board[*currentRow -1 ][*currentColumn] , *currentRow , *currentColumn , gameSize , totalRow,  totalColumn) ;  
		if ( moveCount < move_calculator( board,board[*currentRow -1 ][*currentColumn] , *currentRow -1 , *currentColumn , gameSize , totalRow,  totalColumn)  &&  moveCount < minMove ){
			//finding the most close possibility to move and this will not move the better placed number
			minMove = moveCount;
			moveOperator = 'U' ;
		}
	}
	if( *currentRow  != totalRow -1 && board[*currentRow +1 ][*currentColumn] != 0){						//checking the lower border
		moveCount = move_calculator( board, board[*currentRow +1 ][*currentColumn] , *currentRow , *currentColumn , gameSize ,  totalRow,  totalColumn) ;
		if (moveCount < move_calculator( board,board[*currentRow +1 ][*currentColumn]  , *currentRow +1 , *currentColumn , gameSize , totalRow,  totalColumn)  &&  moveCount < minMove ){
			//finding the most close possibility to move and this will not move the better placed number
			minMove = moveCount;
			moveOperator = 'D' ;
		}
	}
	if( *currentColumn != 0 && board[*currentRow ][*currentColumn -1] != 0){								//checking the left border
		moveCount = move_calculator( board , board[*currentRow][*currentColumn -1 ] , *currentRow , *currentColumn , gameSize , totalRow,  totalColumn ) ;
		if (moveCount < move_calculator( board,board[*currentRow][*currentColumn -1] , *currentRow , *currentColumn - 1 , gameSize , totalRow,  totalColumn)  &&moveCount < minMove ){
			//finding the most close possibility to move and this will not move the better placed number
			minMove = moveCount;
			moveOperator = 'L' ;
		}
	}
	if( *currentColumn  != totalColumn -1 && board[*currentRow][*currentColumn +1] != 0 ){					//checking the right border
		moveCount = move_calculator( board, board[*currentRow ][*currentColumn + 1] , *currentRow , *currentColumn , gameSize , totalRow,  totalColumn ) ;
		if (moveCount <  move_calculator( board,board[*currentRow ][*currentColumn +1] , *currentRow , *currentColumn +1, gameSize , totalRow,  totalColumn) &&  moveCount < minMove ){
			//finding the most close possibility to move and this will not move the better placed number
			minMove = moveCount;
			moveOperator = 'R' ;
		}
	}
	switch (moveOperator){ // making the move according to the move operator which decided above
		case 'L' :
			move_left(board,currentRow,currentColumn,totalRow ,totalColumn);
			break;
		case 'R':
			move_right(board,currentRow,currentColumn,totalRow ,totalColumn);
			break;
		case 'U':
			move_up(board,currentRow,currentColumn,totalRow,totalColumn);
			break;
		case 'D':
			move_down(board,currentRow,currentColumn,totalRow ,totalColumn);
			break;	
		default:
			moveStatus = false; // there is no intelligent move
			break;
	} 
	if(moveStatus != false)
		cout << endl << "Intelligent move choose " << moveOperator << endl ;
	return moveStatus;
}

int move_calculator(int board[MAX_GAME_SIZE][MAX_GAME_SIZE], int number , int currentRow , int currentColumn , int gameSize , int totalRow, int totalColumn){
	int rowCounter , columnCounter , actualRow , actualColumn , counter = 0;
	for(int i=0 ; i < totalRow ; i++){					// this double loop finds actual row and actual column 
		for(int j=0 ; j < totalColumn ; j++){
			if(board[i][j] != 0 ){
				counter++;
				if(counter == number){
					actualRow = i;
					actualColumn = j;
				}
			}	
		}
	}

	rowCounter = currentRow - actualRow ;
	if (rowCounter < 0 )	rowCounter *= -1;
	columnCounter = currentColumn - actualColumn ;
	if (columnCounter < 0 )	columnCounter *= -1;
	return rowCounter + columnCounter ;  // this returns the  how many moves away from the actual place
}

void swap_numbers(int& numberOne , int& numberTwo){
	int backupNumber;
	backupNumber = numberOne ;
	numberOne = numberTwo ; 
	numberTwo = backupNumber;
}

bool move_up( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int totalRow , int totalColumn){
	if(*currentRow == 0 || board[*currentRow-1][*currentColumn] == 0 ){							//checking feasibility of the move
		return false;
	}
	else{
		swap_numbers( board[*currentRow][*currentColumn] , board[*currentRow - 1][*currentColumn] );
		*currentRow -= 1;  																		// updating current coordinate
		return true;
	}	
}

bool move_down( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int totalRow , int totalColumn){
	if(*currentRow == totalRow -1 || board[*currentRow+1][*currentColumn] == 0  ){				//checking feasibility of the move
		return false;
	}
	else{
		swap_numbers( board[*currentRow][*currentColumn] , board[*currentRow + 1][*currentColumn] );
		*currentRow += 1;  																		// updating current coordinate
		return true;
	}
}

bool move_right( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int totalRow , int totalColumn){
	if(*currentColumn == totalColumn-1 || board[*currentRow][*currentColumn+1] == 0  ){			//checking feasibility of the move
		return false;
	}
	else{
		swap_numbers( board[*currentRow][*currentColumn] , board[*currentRow][*currentColumn + 1] );
		*currentColumn += 1;  																	// updating current coordinate
		return true;
	}	
}

bool move_left( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int totalRow , int totalColumn){
	if(*currentColumn == 0 || board[*currentRow][*currentColumn-1] == 0){						//checking feasibility of the move
		return false;
	}
	else{
		swap_numbers( board[*currentRow][*currentColumn] , board[*currentRow][*currentColumn - 1] );
		*currentColumn -= 1;  																	// updating current coordinate
		return true;
	}
}

bool check_for_finish(int gameSize,int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int moveCount , int totalRow , int totalColumn ){
	int counter = 1 ;
	for(int i=0 ; i < totalRow ; i++){		
		for(int j=0 ; j < totalColumn ; j++){
			if( board[i][j] != 0 ){																// skipping the forbidden places
				if( board[totalRow-1 ][totalColumn-1 ] != -1 ) 									// first of all checking right down corner. if its not -1(blank space) return as game is not finished
					return false; 
				else if ( !( i == (totalRow-1) && j == (totalColumn-1) ) && board[i][j] != counter ) // checking non-forbidden places in order with counter
					return false;
				counter++ ; 
			}
			
		}
	}
	return true;
}

int new_intelligent_solving(int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int& currentRow , int& currentColumn , int gameSize , int totalRow, int totalColumn){
	//this function consists three stages. random moves different in each stage
	const int 	MAX_MOVE_SIZE = 100000,												// setting constants
				SHUFFLE_SIZE = 5;										//random move(shuffle) size
	auto gameFinished = false ;
	decltype(gameFinished) moveStatus;	
	int counter =0;																//setting counter as 0 at start
	while( counter < MAX_MOVE_SIZE && gameFinished != true){ 					// loop will continue until MAXMOVE or gameFinished
		moveStatus = intelligent_move(board , &currentRow , &currentColumn , gameSize , totalRow , totalColumn);
		if(moveStatus != true){
			shufle(board , &currentRow , &currentColumn , SHUFFLE_SIZE , totalRow , totalColumn);
			cout << endl ;
			counter += SHUFFLE_SIZE;
		}
		else{
			cout << endl ;
			counter++;
		}
		print_board(board,totalRow,totalColumn);
		cout << endl;
		gameFinished = check_for_finish(gameSize,board,counter,totalRow,totalColumn);
		if( gameFinished == true ) 
			cout << endl << "Solved!" << endl ;
	}
	return counter;
}

void report_about_board(int moveCount , bool gameFinished){  // reports situtation of game
	cout << endl << moveCount << "  moves has beeen done!" << endl;
	if( gameFinished == true )
		cout << "Solution is found!" << endl;
	else
		cout << "Solution couldnt found yet!" << endl;
}

void read_board_from_file(int board[MAX_GAME_SIZE][MAX_GAME_SIZE], int& totalRow , int& totalColumn , int& currentRow , int& currentColumn , string fileName){
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
		inputIntiger = string_checker_and_converter(inputString);  // checking that is string convertable to int  and if it is convert. if itsn returns -1 as nonintiger
		if (inputIntiger == -1 ){
			if(inputString == "bb"){
				board[numberOfRow][numberOfCOlumn] = -1;
				currentRow = numberOfRow;
				currentColumn = numberOfCOlumn;
			}
		}
		else{
			board[numberOfRow][numberOfCOlumn] = inputIntiger; // placing the number into the board
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

void print_board_to_file(int board[MAX_GAME_SIZE][MAX_GAME_SIZE], int totalRow , int totalColumn , int currentRow , int currentColumn){
	string fileName;
	ofstream outputFile;
	cout << "Please enter the file name to save the current configuration:" << endl;
	cin >> fileName;
	outputFile.open(fileName);

	for(int i=0 ; i < totalRow ; i++){
		for(int j=0 ; j < totalColumn ; j++){
			if(board[i][j] != -1 ){
				if ( board[i][j] < 10 && board[i][j] > -1 ) outputFile << "0" ;
				outputFile << board[i][j] ;		// last number is blank space and checking for blank place
			}	
			else 
				outputFile << "bb" ;
			if( j != totalColumn -1 ) 		// this check for end of line. if it is not prints " ". if program doesnt do that the file which created cannot be loadable again
				outputFile << " " ;			// because program detect '\n'
		}
		outputFile << endl; 
	}
	cout << "Configuration saved!" << endl;
}

void print_welcome(){
	cout << "Welcome N-Puzzle Game!" << endl
		 <<	"L - Move Left" << endl
		 << "R - Move Right" << endl
		 << "U - Move Up" << endl
		 << "D - Move Down" << endl
		 << "I - Intelligent Move" << endl
		 << "S - Shuffle" << endl
		 << "V - Intelligent Solve" << endl
		 << "T - Report About Board" << endl
		 << "E - Load the current board to file" << endl
		 << "Y - Load the board from file" << endl
		 << "Q - Quit Game" << endl
		 << endl << endl;
}