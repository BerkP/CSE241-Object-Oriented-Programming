#include "AbstractBoard.h"
#include "BoardArray1D.h"
#include "BoardVector.h"
#include "BoardArray2D.h"
#include "globalFunc.h"

using namespace GTU_PKGZ;



int main(){
	string fileName;
	ifstream file1;
	ofstream file2;


	cout << endl << "********************************************************************************" << endl << "Array1D test started!" << 
		endl << "------------------" << endl;

	cout << "board1_1D created with no parameter constructer" << endl;
	BoardArray1D board1_1D;
	board1_1D.print();

	cout << endl << "------------------" << endl << "board2_1D created with constructer with parameter(6,7)" << endl;
	BoardArray1D board2_1D(6,7);
	board2_1D.print();

	cout << endl << "------------------" << endl << "Move func called with U-R-L-D-D-U(some of them unvalid moves and program ignores them) to Board 1. lastMove and numberOfMoves called" << endl;
	board1_1D.move('U');
	board1_1D.move('R');
	board1_1D.move('L');
	board1_1D.move('D');
	board1_1D.move('D');
	board1_1D.move('U');
	board1_1D.print();
	cout << "Last move is " << board1_1D.lastMove() << endl;
	cout << "numberOfMoves is " << board1_1D.numberOfMoves() << endl ;

	cout << endl << "------------------" << endl << "Reset func called to board1_1D" << endl;
	board1_1D.reset();
	board1_1D.print();

	cout << endl << "------------------" << endl << "setSize func called(4,5) and reset called to board1_1D" << endl;
	board1_1D.setSize(4,5);
	board1_1D.reset();
	board1_1D.print();

	cout << endl << "------------------" << endl << "readFromFile func called with 'boardTextFiles/b.txt' to board1_1D" << endl;
	file1.open("boardTextFiles/b.txt");
	board1_1D.readFromFile(file1);
	file1.close();
	board1_1D.print();

	cout << endl << "------------------" << endl << "board1_1D checked for isSolved and reset called to board1_1D again checked for isSolved" << endl;
	cout << "Board is " ;
	if(board1_1D.isSolved())		cout << "solution";
	else 						cout << "not solution";
	cout << endl;
	cout << "-Reset called" <<endl;
	board1_1D.reset();
	board1_1D.print();
	cout << "Board is " ;
	if(board1_1D.isSolved())		cout << "solution";
	else 						cout << "not solution";
	cout << endl;


	cout << endl << "------------------" << endl << "board3_1D created with copy constructer as board1_1D and equality checked" << endl;
	BoardArray1D board3_1D(board1_1D);
	board3_1D.print();
	cout << endl << "Boards are ";
	if(board1_1D == board3_1D) 		cout << "same!" << endl;
	else 						cout << "not same!" << endl;

	cout << endl << "------------------" << endl << "Equality of board1_1D and board2_1D checked" << endl;
	cout << endl << "Boards are ";
	if(board1_1D == board2_1D) 		cout << "same!" << endl;
	else 						cout << "not same!" << endl;

	cout << endl << "------------------" << endl << "To finish BoardArray1D test please enter a file name to test board1_1D writeToFile func:" << endl;
	cin >> fileName ;
	file2.open(fileName);
	board1_1D.writeToFile(file2);
	file2.close();
	cout << "File created and BoardArray1D test finished!" << endl;



	cout << endl << "********************************************************************************" << endl << "Array2D test started!" << 
		endl << "------------------" << endl;

	cout << "board1_1D_2D created with no parameter constructer" << endl;
	BoardArray2D board1_1D_2D;
	board1_1D_2D.print();

	cout << endl << "------------------" << endl << "board2_1D_2D created with constructer with parameter" << endl;
	BoardArray2D board2_1D_2D(6,7);
	board2_1D_2D.print();

	cout << endl << "------------------" << endl << "Move func called with U-R-L-D-D-U(some of them unvalid moves and program ignores them) to board1_1D_2D. lastMove and numberOfMoves called" << endl;
	board1_1D_2D.move('U');
	board1_1D_2D.move('R');
	board1_1D_2D.move('L');
	board1_1D_2D.move('D');
	board1_1D_2D.move('D');
	board1_1D_2D.move('U');
	board1_1D_2D.print();
	cout << "Last move is " << board1_1D_2D.lastMove() << endl;
	cout << "numberOfMoves is " << board1_1D_2D.numberOfMoves() << endl ;

	cout << endl << "------------------" << endl << "Reset func called to board1_1D_2D" << endl;
	board1_1D_2D.reset();
	board1_1D_2D.print();

	cout << endl << "------------------" << endl << "setSize func called(4,5) and reset called to board1_1D_2D" << endl;
	board1_1D_2D.setSize(4,5);
	board1_1D_2D.reset();
	board1_1D_2D.print();

	cout << endl << "------------------" << endl << "readFromFile func called with 'boardTextFiles/b.txt' to board1_1D_2D" << endl;
	file1.open("boardTextFiles/b.txt");
	board1_1D_2D.readFromFile(file1);
	file1.close();
	board1_1D_2D.print();

	cout << endl << "------------------" << endl << "board1_1D_2D checked for isSolved and reset called to board1_1D_2D again checked for isSolved" << endl;
	cout << "Board is " ;
	if(board1_1D_2D.isSolved())		cout << "solution";
	else 						cout << "not solution";
	cout << endl;
	cout << "-Reset called" <<endl;
	board1_1D_2D.reset();
	board1_1D_2D.print();
	cout << "Board is " ;
	if(board1_1D_2D.isSolved())		cout << "solution";
	else 						cout << "not solution";
	cout << endl;

	cout << endl << "------------------" << endl << "board3_1D_2D created with copy constructer as board1_1D_2D and equality checked" << endl;
	BoardArray2D board3_1D_2D(board1_1D_2D);
	board3_1D_2D.print();
	cout << endl << "Boards are ";
	if(board1_1D_2D == board3_1D_2D) 		cout << "same!" << endl;
	else 						cout << "not same!" << endl;

	cout << endl << "------------------" << endl << "Equality of board1_1D_2D and board2_1D_2D checked" << endl;
	cout << endl << "Boards are ";
	if(board1_1D_2D == board2_1D_2D) 		cout << "same!" << endl;
	else 						cout << "not same!" << endl;

	cout << endl << "------------------" << endl << "To finish BoardArray2D test please enter a file name to test board1_1D_2D writeToFile func:" << endl;
	cin >> fileName ;
	file2.open(fileName);
	board1_1D_2D.writeToFile(file2);
	file2.close();
	cout << "File created and BoardArray1D test finished!" << endl;

	cout << endl << "********************************************************************************" << endl << "ArrayVector test started!" << 
		endl << "------------------" << endl;

	cout << "board1_Vec created with no parameter constructer" << endl;
	BoardVector board1_Vec;
	board1_Vec.print();

	cout << endl << "------------------" << endl << "baord2_Vec created with constructer with parameter" << endl;
	BoardVector baord2_Vec(6,7);
	baord2_Vec.print();

	cout << endl << "------------------" << endl << "Move func called with U-R-L-D-D-U(some of them unvalid moves and program ignores them) to board1_Vec. lastMove and numberOfMoves called" << endl;
	board1_Vec.move('U');
	board1_Vec.move('R');
	board1_Vec.move('L');
	board1_Vec.move('D');
	board1_Vec.move('D');
	board1_Vec.move('U');
	board1_Vec.print();
	cout << "Last move is " << board1_Vec.lastMove() << endl;
	cout << "numberOfMoves is " << board1_Vec.numberOfMoves() << endl ;

	cout << endl << "------------------" << endl << "Reset func called to board1_Vec" << endl;
	board1_Vec.reset();
	board1_Vec.print();

	cout << endl << "------------------" << endl << "setSize func called(4,5) and reset called to board1_Vec" << endl;
	board1_Vec.setSize(4,5);
	board1_Vec.reset();
	board1_Vec.print();

	cout << endl << "------------------" << endl << "readFromFile func called with 'boardTextFiles/b.txt' to board1_Vec" << endl;
	file1.open("boardTextFiles/b.txt");
	board1_Vec.readFromFile(file1);
	file1.close();
	board1_Vec.print();

	cout << endl << "------------------" << endl << "board1_Vec checked for isSolved and reset called to board1_Vec again checked for isSolved" << endl;
	cout << "Board is " ;
	if(board1_Vec.isSolved())		cout << "solution";
	else 						cout << "not solution";
	cout << endl;
	cout << "-Reset called" <<endl;
	board1_Vec.reset();
	board1_Vec.print();
	cout << "Board is " ;
	if(board1_Vec.isSolved())		cout << "solution";
	else 						cout << "not solution";
	cout << endl;

	cout << endl << "------------------" << endl << "board3_1D_Vec created with copy constructer as board1_Vec and equality checked" << endl;
	BoardVector board3_1D_Vec(board1_Vec);
	board3_1D_Vec.print();
	cout << endl << "Boards are ";
	if(board1_Vec == board3_1D_Vec) 		cout << "same!" << endl;
	else 						cout << "not same!" << endl;

	cout << endl << "------------------" << endl << "Equality of board1_Vec and baord2_Vec checked" << endl;
	cout << endl << "Boards are ";
	if(board1_Vec == baord2_Vec) 		cout << "same!" << endl;
	else 						cout << "not same!" << endl;

	cout << endl << "------------------" << endl << "To finish BoardVector test please enter a file name to test board1_Vec writeToFile func:" << endl;
	cin >> fileName ;
	file2.open(fileName);
	board1_Vec.writeToFile(file2);
	file2.close();
	cout << "File created and BoardArray1D test finished!" << endl;

	cout << endl << "********************************************************************************" 
				 << "********************************************************************************" 
				 << "********************************************************************************" 
				 << "********************************************************************************" 
				 << endl << "Global func test started!" << endl << "------------------" << endl;

	BoardArray1D fboard1;
	BoardArray2D fboard2;
	BoardVector fboard3;
	BoardArray1D fboard4;
	BoardArray2D fboard5;
	BoardVector fboard6;

	file1.open("boardTextFiles/1.txt");
	fboard1.readFromFile(file1);
	file1.close();

	file1.open("boardTextFiles/2.txt");
	fboard2.readFromFile(file1);
	file1.close();

	file1.open("boardTextFiles/3.txt");
	fboard3.readFromFile(file1);
	file1.close();

	file1.open("boardTextFiles/4.txt");
	fboard4.readFromFile(file1);
	file1.close();

	file1.open("boardTextFiles/5.txt");
	fboard5.readFromFile(file1);
	file1.close();

	file1.open("boardTextFiles/6.txt");
	fboard6.readFromFile(file1);
	file1.close();

	cout << "Boards are readed from files 1/2/3/4/5/6.txt" << endl << 
			"Boards are listed " ;

	cout << endl << "-------------------" << endl << "Board 1" << endl;
	fboard1.print();
	cout << endl << "-------------------" << endl << "Board 2" << endl;
	fboard2.print();
	cout << endl << "-------------------" << endl << "Board 3" << endl;
	fboard3.print();
	cout << endl << "-------------------" << endl << "Board 4" << endl;
	fboard4.print();
	cout << endl << "-------------------" << endl << "Board 5" << endl;
	fboard5.print();
	cout << endl << "-------------------" << endl << "Board 6" << endl;
	fboard6.print();

	cout << endl << "********************************************************************************" << endl;

	AbstractBoard* sequance_1[] = {&fboard4,&fboard1,&fboard2,&fboard3};
	AbstractBoard* sequance_2[] = {&fboard4,&fboard1,&fboard2};
	AbstractBoard* sequance_3[] = {&fboard1,&fboard5,&fboard2,&fboard3};
	AbstractBoard* sequance_4[] = {&fboard2,&fboard1,&fboard5};
	AbstractBoard* sequance_5[] = {&fboard4,&fboard1,&fboard2,&fboard6};

	cout << endl << "sequance_1 is <Board 4-Board 1-Board 2-Board 3> and this sequence ";
	if( isSequanceGoToSolituon(sequance_1 , 4)) cout << "goes to solution. ";
	else 										cout << "does not go to solution. ";

	cout << endl << "sequance_2 is <Board 4-Board 1-Board 2        > and this sequence ";
	if( isSequanceGoToSolituon(sequance_2 , 3)) cout << "goes to solution. ";
	else 										cout << "does not go to solution. ";

	cout << endl << "sequance_3 is <Board 1-Board 5-Board 2-Board 3> and this sequence ";
	if( isSequanceGoToSolituon(sequance_3 , 4)) cout << "goes to solution. ";
	else 										cout << "does not go to solution. ";

	cout << endl << "sequance_4 is <Board 2-Board 1-Board 5        > and this sequence ";
	if( isSequanceGoToSolituon(sequance_4 , 3)) cout << "goes to solution. ";
	else 										cout << "does not go to solution. ";

	cout << endl << "sequance_5 is <Board 4-Board 1-Board 2-Board 6> and this sequence ";
	if( isSequanceGoToSolituon(sequance_5 , 4)) cout << "goes to solution. ";
	else 										cout << "does not go to solution. ";



	return 0;
}



