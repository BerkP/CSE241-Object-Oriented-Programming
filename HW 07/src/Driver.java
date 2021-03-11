import java.io.*;
import Boards.*;

public class Driver{


	public static void main(String ... args){


		System.out.println("****************************************************");
		System.out.println("BoardArray1D test STARTED!");
		System.out.println("****************************************************");

		System.out.println("board1_1D created with no parameter constructer") ;
		BoardArray1D board1_1D = new BoardArray1D();
		System.out.println(board1_1D);

		System.out.println("board2_1D created with constructer with parameter(6,7)");
		BoardArray1D board2_1D = new BoardArray1D(6,7);
		System.out.println(board2_1D);

		System.out.println("Move func called with U-R-L-D-D-U(some of them unvalid moves and program ignores them) to Board 1. lastMove and numberOfMoves called");
		board1_1D.move('U');
		board1_1D.move('R');
		board1_1D.move('L');
		board1_1D.move('D');
		board1_1D.move('D');
		board1_1D.move('U');
		System.out.println(board1_1D);
		System.out.println( board1_1D.lastMove());
		System.out.println(board1_1D.numberOfMoves());

		System.out.println("Reset func called to board1_1D");
		board1_1D.reset();
		System.out.println(board1_1D);

		System.out.println("setSize func called (4,5) and reset called to board1_1D" );
		board1_1D.setSize(4,5);
		System.out.println(board1_1D);

		try {
			System.out.println("readFromFile func called with 'boardTextFiles/b.txt' to board1_1D");
			board1_1D.readFromFile("boardTextFiles/b.txt");
			System.out.println(board1_1D);
		}
		catch(Exception e) {
			System.out.println("Catched!");
		}

		System.out.println("board1_1D checked for isSolved and reset called to board1_1D again checked for isSolved");
		System.out.printf("Board is ") ;
		if(board1_1D.isSolved())		System.out.println( "solution\n");
		else 						System.out.println("not solution\n");
		System.out.println("-Reset called");
		board1_1D.reset();
		System.out.println(board1_1D);
		System.out.printf("Board is ") ;
		if(board1_1D.isSolved())		System.out.println( "solution\n");
		else 						System.out.println("not solution\n");


		System.out.println("board3_1D created with copy constructer as board1_1D and equality checked");
		BoardArray1D board3_1D = new BoardArray1D(board1_1D);
		System.out.println(board3_1D);
		System.out.printf("Boards are ");
		if(board1_1D.equals(board3_1D)) 		System.out.println("same!\n");
		else 						System.out.println("not same!\n");

		System.out.println("Equality of board1_1D and board2_1D checked");
		System.out.printf("Boards are ");
		if(board1_1D.equals(board2_1D)) 		System.out.println("same!\n");
		else 						System.out.println("not same!\n");

		System.out.println("To finish writeToFile func called");
		try{
			board1_1D.writeToFile("writeToFile_1D.txt");
		}
		catch(IOException e){
			System.out.println("Sth went wrong with file!");
		}

		System.out.println("File created and BoardArray1D test finished!");






		System.out.println("\n\n****************************************************");
		System.out.println("BoardArray2D test STARTED!");
		System.out.println("****************************************************");

		System.out.println("board1_2D created with no parameter constructer") ;
		BoardArray2D board1_2D = new BoardArray2D();
		System.out.println(board1_2D);

		System.out.println("board2_2D created with constructer with parameter(6,7)");
		BoardArray2D board2_2D = new BoardArray2D(6,7);
		System.out.println(board2_2D);

		System.out.println("Move func called with U-R-L-D-D-U(some of them unvalid moves and program ignores them) to Board 1. lastMove and numberOfMoves called");
		board1_2D.move('U');
		board1_2D.move('R');
		board1_2D.move('L');
		board1_2D.move('D');
		board1_2D.move('D');
		board1_2D.move('U');
		System.out.println(board1_2D);
		System.out.println( board1_2D.lastMove());
		System.out.println(board1_2D.numberOfMoves());

		System.out.println("Reset func called to board1_2D");
		board1_2D.reset();
		System.out.println(board1_2D);

		System.out.println("setSize func called (4,5) and reset called to board1_2D" );
		board1_2D.setSize(4,5);
		System.out.println(board1_2D);

		try {
			System.out.println("readFromFile func called with 'boardTextFiles/b.txt' to board1_2D");
			board1_2D.readFromFile("boardTextFiles/b.txt");
			System.out.println(board1_2D);
		}
		catch(Exception e) {
			System.out.println("Catched!");
		}

		System.out.println("board1_2D checked for isSolved and reset called to board1_2D again checked for isSolved");
		System.out.printf("Board is ") ;
		if(board1_2D.isSolved())		System.out.println( "solution\n");
		else 						System.out.println("not solution\n");
		System.out.println("-Reset called");
		board1_2D.reset();
		System.out.println(board1_2D);
		System.out.printf("Board is ") ;
		if(board1_2D.isSolved())		System.out.println( "solution\n");
		else 						System.out.println("not solution\n");


		System.out.println("board3_2D created with copy constructer as board1_2D and equality checked");
		BoardArray2D board3_2D = new BoardArray2D(board1_2D);
		System.out.println(board3_2D);
		System.out.printf("Boards are ");
		if(board1_2D.equals(board3_2D)) 		System.out.println("same!\n");
		else 						System.out.println("not same!\n");

		System.out.println("Equality of board1_2D and board2_2D checked");
		System.out.printf("Boards are ");
		if(board1_2D.equals(board2_2D)) 		System.out.println("same!\n");
		else 						System.out.println("not same!\n");

		System.out.println("To finish writeToFile func called");

		try{
			board1_2D.writeToFile("writeToFile_2D.txt");
		}
		catch(IOException e){
			System.out.println("Sth went wrong with file!");
		}


		System.out.println("File created and BoardArray2D test finished!");

		System.out.println("\n\nStatic method test started");

		BoardArray1D fboard1 = new BoardArray1D();
		BoardArray2D fboard2 = new BoardArray2D();
		BoardArray1D fboard3 = new BoardArray1D();
		BoardArray2D fboard4 = new BoardArray2D();
		BoardArray1D fboard5 = new BoardArray1D();
		BoardArray2D fboard6 = new BoardArray2D();

		try {
			fboard1.readFromFile("boardTextFiles/1.txt");
	
			fboard2.readFromFile("boardTextFiles/2.txt");
	
			fboard3.readFromFile("boardTextFiles/3.txt");
	
			fboard4.readFromFile("boardTextFiles/4.txt");
	
			fboard5.readFromFile("boardTextFiles/5.txt");
	
			fboard6.readFromFile("boardTextFiles/6.txt");
		}
		catch(Exception e) {
			System.out.println("Catched!");
		}

		System.out.println("Boards are readed from files 1/2/3/4/5/6.txt");

		System.out.println("Boards are listed " );

		System.out.println("-------------------" );
		System.out.println( "Board 1" );
		System.out.println( fboard1 );

		System.out.println("-------------------" );
		System.out.println( "Board 2" );
		System.out.println( fboard2 );

		System.out.println("-------------------" );
		System.out.println( "Board 3" );
		System.out.println( fboard3 );

		System.out.println("-------------------" );
		System.out.println( "Board 4" );
		System.out.println( fboard4 );

		System.out.println("-------------------" );
		System.out.println( "Board 5" );
		System.out.println( fboard5 );

		System.out.println("-------------------" );
		System.out.println( "Board 6" );
		System.out.println( fboard6 );


		System.out.println("********************************************************************************");

		AbstractBoard [] sequance_1 = {fboard4,fboard1,fboard2,fboard3};
		AbstractBoard [] sequance_2 = {fboard4,fboard1,fboard2};
		AbstractBoard [] sequance_3 = {fboard1,fboard5,fboard2,fboard3};
		AbstractBoard [] sequance_4 = {fboard2,fboard1,fboard5};
		AbstractBoard [] sequance_5 = {fboard4,fboard1,fboard2,fboard6};

		System.out.printf( "sequance_1 is <Board 4-Board 1-Board 2-Board 3> and this sequence ");
		if( StaticMethod.isSequanceGoToSolituon(sequance_1 )) System.out.printf("goes to solution.\n ");
		else 										System.out.printf("does not go to solution.\n ");

		System.out.printf("sequance_2 is <Board 4-Board 1-Board 2        > and this sequence ");
		if( StaticMethod.isSequanceGoToSolituon(sequance_2 )) System.out.printf("goes to solution. \n");
		else 										System.out.printf("does not go to solution.\n");

		System.out.printf("sequance_3 is <Board 1-Board 5-Board 2-Board 3> and this sequence ");
		if( StaticMethod.isSequanceGoToSolituon(sequance_3 )) System.out.printf("goes to solution.\n");
		else 										System.out.printf("does not go to solution.\n");

		System.out.printf("sequance_4 is <Board 2-Board 1-Board 5        > and this sequence ");
		if( StaticMethod.isSequanceGoToSolituon(sequance_4)) System.out.printf("goes to solution.\n");
		else 										System.out.printf("does not go to solution.\n ");

		System.out.printf("sequance_5 is <Board 4-Board 1-Board 2-Board 6> and this sequence ");
		if( StaticMethod.isSequanceGoToSolituon(sequance_5 )) System.out.printf("goes to solution.\n");
		else 										System.out.printf("does not go to solution. \n");



	}	
}
