#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>
#include"NPuzzle.h"


int main( int argc , char** argv ){
	srand(time(NULL));
	int gameSize;
	char inputAction;
	auto quitGame = false;
	string inputString , fileName;
	NPuzzle game;

	if( argc > 1 ){																//checking if file name entered in command line
		game.readFromFile(argv[1]);
	}
	else{																	// if command line is empty starts normal
		cout << "Please enter the problem size" << endl ;
		do{
			cin >> inputString ;												//taking a string for game size input
			gameSize = NPuzzle::stringCheckerAndConverter(inputString);				// checking and converting the string to intiger
		}while(game.setSize(gameSize,gameSize) != true)  ; 
	}	
	cout << "Your initial board is" << endl;
	game.print();
	do{
		cout << "Your move:" ;
		cin >> inputAction ;
		switch (inputAction){
			case 'l':			//double case for uppercase and lowercase letters
			case 'L':
			case 'r':			
			case 'R':
			case 'u':			
			case 'U':
			case 'd':			
			case 'D':
				game.move(inputAction);
				break;	
			case 's':
			case 'S':
				game.shuffle(); 
				break;
			case 'v':
			case 'V':
				game.solvePuzzle();
				break;  
			case 'o':
			case 'O':
				cout << endl << "Please enter the file name" << endl;
				cin >> fileName;
				game.readFromFile( fileName );
				break;
			case 'e':
			case 'E':
				cout << endl << "Please enter the file name" << endl;
				cin >> fileName;
				game.writeToFile( fileName );
				break;	
			case 't':
			case 'T':
				game.printReport();
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
		if(quitGame != true)
			game.print();
}while( quitGame != true );
	return 0;
}