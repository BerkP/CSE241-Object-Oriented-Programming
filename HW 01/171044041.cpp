#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

using namespace std;

const int MAX_GAME_SIZE = 9;
const int MIN_GAME_SIZE = 3;
const int NON_INTIGER = -1;		//used for the non-intiger return value
const int TRUE = 1; 	// used insted of bool functions
const int FALSE = 0;	// used insted of bool functions

void puzzle_game();
int string_checker_and_converter( char str[] );
void shufle( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int * , int * , int  , int );
void print_board(int ,int board[MAX_GAME_SIZE][MAX_GAME_SIZE]);
void intelligent_move(int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int * , int * , int );
int move_calculator(int  , int  , int  , int );
void swap_numbers(int * , int *);
int move_up( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int * , int * ,int  );
int move_down( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int * , int * ,int  );
int move_right( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int * , int * ,int  );
int move_left( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int * , int * ,int  );
int check_for_finish(int ,int board[MAX_GAME_SIZE][MAX_GAME_SIZE], int );

int main(){
	srand(time(NULL));
	puzzle_game();	
	return 0;
}

void puzzle_game(){
	const int MAX_INPUT_STRING = 20;
	int gameFinished = FALSE , moveCheck;			//check flags
	char inputMove , inputString[MAX_INPUT_STRING];
	int	currentRow , currentColumn , gameSize , moveCount=0 ;
	int board[MAX_GAME_SIZE][MAX_GAME_SIZE];
	cout << "Please enter the problem size" << endl ;
	do{
		cin >> inputString ;
		gameSize = string_checker_and_converter(inputString);
		if ( gameSize < MIN_GAME_SIZE || gameSize > MAX_GAME_SIZE) 	cout << "Invalid game size! Try again!" << endl ;
	}while ( gameSize < MIN_GAME_SIZE || gameSize > MAX_GAME_SIZE)  ; 
	shufle(board,&currentRow,&currentColumn,gameSize,1000);  // 1000 is chosen for complex game. if user wants to shuffle again, it will be size*size.
	cout << "Your initial random board is" << endl;
	print_board(gameSize,board);
	do{
		moveCheck = TRUE ;			//reseting the flag
		cout << "Your move:" ;
		cin >> inputMove ;
		switch (inputMove){
			case 'l':			//double case for uppercase and lowercase letters
			case 'L':
				moveCheck = move_left(board,&currentRow,&currentColumn,gameSize);
				break;
			case 'r':	
			case 'R':
				moveCheck = move_right(board,&currentRow,&currentColumn,gameSize);
				break;
			case 'u':
			case 'U':
				moveCheck = move_up(board,&currentRow,&currentColumn,gameSize);
				break;
			case 'd':
			case 'D':
				moveCheck = move_down(board,&currentRow,&currentColumn,gameSize);
				break;		
			case 's':
			case 'S':
				shufle(board,&currentRow,&currentColumn,gameSize,gameSize*gameSize);  // this time shuffle size*size move according to rule
				moveCount = 0;														// reseting move count
				cout << "Game has been shuffled again!" << endl ; 
				break;
			case 'i':	
			case 'I':
				intelligent_move(board, &currentRow , &currentColumn ,gameSize);
				break;
			case 'q':
			case 'Q':
				gameFinished = TRUE ;												
				cout << endl << "THANKS FOR PLAYING! SEE YOU NEXT TIME!" << endl;
				break;	
			default :
				cout << "Wrong input!" << endl ;
				break;	
		}
		if(gameFinished != TRUE){
			if(moveCheck == FALSE)		cout << "Invalid move! Try another way!" << endl ;
			else 	moveCount++;
			print_board(gameSize,board);
			gameFinished = check_for_finish(gameSize,board,moveCount);
		}
	}while( gameFinished != TRUE );
}


int string_checker_and_converter( char str[] ){
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

void shufle( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize , int quantityOfMove){
	bool moveCheck;
	int counter = 1 , randomNumber; 							
	for(int i=0 ; i < gameSize ; i++ ){				// loop for initialize the board according to game size 
		for(int j=0 ; j < gameSize ; j++){
			board[i][j]= counter;
			counter++;
		}
	}
	*currentRow = gameSize-1;
	*currentColumn = gameSize-1;
	
	for( int numberOfMove=0 ; numberOfMove < quantityOfMove ; numberOfMove++){
		randomNumber = rand() %4 ;					//there are four ways and this is for rondomize 
		switch(randomNumber){
			case 0 :
				moveCheck = move_up(board,currentRow,currentColumn,gameSize);
				break;
			case 1 :
				moveCheck = move_down(board,currentRow,currentColumn,gameSize);
				break;
			case 2 :
				moveCheck = move_right(board,currentRow,currentColumn,gameSize);
				break;
			case 3 :
				moveCheck = move_left(board,currentRow,currentColumn,gameSize);
				break;
		}
		if( moveCheck != TRUE )	numberOfMove -= 1;			//decreasing the current move because move couldnt happen
	}
}

void print_board(int gameSize,int board[MAX_GAME_SIZE][MAX_GAME_SIZE]){
	for(int i=0 ; i < gameSize ; i++){
		for(int j=0 ; j < gameSize ; j++){
			if(board[i][j] != gameSize * gameSize )	cout << board[i][j] << "\t" ;		// last number is blank space and checking for blank place
			else cout << " \t" ;
		}
		cout << endl;
	}
}

void intelligent_move(int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize){
	char moveOperator;
	int minMove = MAX_GAME_SIZE * MAX_GAME_SIZE , moveCount; // minMove is max move at start so after the calculations we'll find the min 
	
	if( *currentRow  != 0 ){								// checking the upper border
		moveCount = move_calculator( board[*currentRow -1 ][*currentColumn] , *currentRow , *currentColumn , gameSize ) ;  
		if ( moveCount < minMove ){							//finding the most close possibility to move
			minMove = moveCount;
			moveOperator = 'U' ;
		}
	}
	if( *currentRow  != gameSize -1 ){						//checking the lower border
		moveCount = move_calculator( board[*currentRow +1 ][*currentColumn] , *currentRow , *currentColumn , gameSize ) ;
		if ( moveCount < minMove ){
			minMove = moveCount;
			moveOperator = 'D' ;
		}
	}
	if( *currentColumn != 0 ){								//checking the left border
		moveCount = move_calculator( board[*currentRow][*currentColumn -1 ] , *currentRow , *currentColumn , gameSize ) ;
		if ( moveCount < minMove ){
			minMove = moveCount;
			moveOperator = 'L' ;
		}
	}
	if( *currentColumn  != gameSize -1 ){					//checking the right border
		moveCount = move_calculator( board[*currentRow ][*currentColumn + 1] , *currentRow , *currentColumn , gameSize ) ;
		if ( moveCount < minMove ){
			minMove = moveCount;
			moveOperator = 'R' ;
		}
	}
	
	switch (moveOperator){
		case 'L' :
			move_left(board,currentRow,currentColumn,gameSize);
			break;
		case 'R':
			move_right(board,currentRow,currentColumn,gameSize);
			break;
		case 'U':
			move_up(board,currentRow,currentColumn,gameSize);
			break;
		case 'D':
			move_down(board,currentRow,currentColumn,gameSize);
			break;	
	}
}

int move_calculator(int number , int currentRow , int currentColumn , int gameSize){
	int rowCounter , columnCounter , actualRow , actualColumn;
	number -= 1 ; // its needen bacause it is the easiest way to calculate the actual place of the number on board in this games
	actualRow = number / gameSize; 
	actualColumn = number % gameSize ; 
	rowCounter = currentRow - actualRow ;
	if (rowCounter < 0 )	rowCounter *= -1;
	columnCounter = currentColumn - actualColumn ;
	if (columnCounter < 0 )	columnCounter *= -1;
	return rowCounter + columnCounter ;  // this returns the  how many moves away from the actual place
}

void swap_numbers(int *numberOne , int *numberTwo){
	int backupNumber;
	backupNumber = *numberOne ;
	*numberOne = *numberTwo ; 
	*numberTwo = backupNumber;
}

int move_up( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize){
	if(*currentRow != 0 ){							//checking feasibility of the move
		swap_numbers( &board[*currentRow][*currentColumn] , &board[*currentRow - 1][*currentColumn] );
		*currentRow -= 1;  							// updating current coordinate
		return TRUE;
	}
	else	return FALSE;
}

int move_down( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize){
	if(*currentRow != gameSize -1 ){					//checking feasibility of the move
		swap_numbers( &board[*currentRow][*currentColumn] , &board[*currentRow + 1][*currentColumn] );
		*currentRow += 1;  							// updating current coordinate
		return TRUE;
	}
	else	return FALSE;
}

int move_right( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize){
	if(*currentColumn != gameSize-1 ){				//checking feasibility of the move
		swap_numbers( &board[*currentRow][*currentColumn] , &board[*currentRow][*currentColumn + 1] );
		*currentColumn += 1;  						// updating current coordinate
		return TRUE;
	}
	else	return FALSE;
}

int move_left( int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int *currentRow , int *currentColumn , int gameSize){
	if(*currentColumn != 0 ){						//checking feasibility of the move
		swap_numbers( &board[*currentRow][*currentColumn] , &board[*currentRow][*currentColumn - 1] );
		*currentColumn -= 1;  						// updating current coordinate
		return TRUE;
	}
	else	return FALSE;
}

int check_for_finish(int gameSize,int board[MAX_GAME_SIZE][MAX_GAME_SIZE] , int moveCount){
	int counter = 1 ;
	for(int i=0 ; i < gameSize ; i++){
		for(int j=0 ; j < gameSize ; j++){
			if(board[i][j] != counter )	return FALSE ;		
			counter++ ; 
		}
	}
	cout << endl << "Congrats! You won the game!" << endl << "Total move:" << moveCount << endl;  //if program can end the loop above, it means all numbers in correct place.
	return TRUE;
}
