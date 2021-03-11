package Boards;
import java.util.Scanner;
import java.io.*;

/**
 * 
 * AbstractBoard class represents the board configuration
 * 
 * @author Berk Pekgoz GTU 171044041
 * 
 */
public abstract class AbstractBoard{

	private int totalRow;
	private int totalColumn;
	private int currentRow;
	private int currentColumn;
	private char lastMoveChar;
	private int totalMove;
	static private int totalBoard;
	static final private int BLANK_SPACE = -1 ,
				 	 FORBIDDEN_CELL = -2;

	/**
	 * No parameter constructor. 
	 */
	public AbstractBoard(){
		increaseTotalBoard();
		resetLastMove();
		resetTotalMove();
	}

	/**
	 * Takes two indexes and returns the corresponding cell content.
	 * Terminates program if the indexes are not valid.
	 * @param row Input row number for cell
	 * @param column Input column number for cell
	 * @return Value of cell
	 */
	public abstract int cell(int row , int column);
	
	/**
	 * Takes two indexes and value to change the corresponding cell content.
	 * Terminates program if the indexes are not valid.
	 * @param row  Input row number for cell
	 * @param column  Input column number for cell
	 * @param data New value of cell
	 */
	protected abstract void setCell(int row , int column , int data);

	/**
	 * Makes a move according to the given char parameter.
	 * @param moveOperator Direction of move("L/R/U/D")
	 * @return Statement of is move happened
	 */
	public boolean move(char moveOperator){
		boolean moveStatus = true;  										//initiliazing the flag as false
		int postMoveRow = getCurrentRow() , 
			postMoveColumn = getCurrentColumn();
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
			swapNumbers(currentRow,currentColumn,postMoveRow,postMoveColumn);
			currentRow = postMoveRow; 
			currentColumn = postMoveColumn;
			setLastMove(moveOperator);
			totalMove++;
		}
		return moveStatus;
	}

	/**
	 * Sets the board size to given values. 
	 * The values are given as parameters and there are no restrictions on the board size and 
	 * if the parameters are invalid board size, they are automaticlly setted to 3.
	 * The board is reset after this operation.
	 * @param rowSize Input row size to change rows
	 * @param columnSize Input column size to change columns
	 */
	public void setSize(int rowSize , int columnSize){
		totalRow	=	rowSize;
		totalColumn	=	columnSize;
	}

	/**
	 * Returns true if the board is a solution
	 * @return Statement of the baord
	 */
	public boolean isSolved(){
		boolean solvedStatus = true; 																							//setting true at start. if it is not i t will change later
		int counter = 1 ;
		for(int i=0 ; i < getRowSize() ; i++){		
			for(int j=0 ; j < getColumnSize() ; j++){
				if( cell(i,j) != FORBIDDEN_CELL ){																// skipping the forbidden places
					if( cell(getRowSize()-1,getColumnSize()-1) != BLANK_SPACE) 									// first of all checking right down corner. if its not -1(blank space) return as game is not finished
						solvedStatus = false; 
					else if ( !( i == (getRowSize()-1) && j == (getColumnSize()-1) ) && cell(i,j) != counter )	// checking non-forbidden places in order with counter
						solvedStatus = false;
					counter++ ; 
				}
			}
		}
		return solvedStatus;
	}

	/**
	 * Two boards are equal, if the boards are the same. 
	 * This operator does not consider last move or the number of steps
	 * @param other Other {@link AbstractBoard} object to check
	 * @return Boolean for equality 
	 */
	public boolean equals( AbstractBoard other){
		if(getRowSize() != other.getRowSize() && getColumnSize() != other.getColumnSize())
			return false;

		for(int i=0 ; i < totalRow ; i++){
			for(int j=0 ; j < totalColumn ; j++){
				if(cell(i,j) != other.cell(i,j)){
					return false;
				}
			} 
		}
		return true;
	}

	/**
	 * Resets the board to the solution
	 */
	public void reset(){
		int counter = 1 ;							
		for(int i=0 ; i < getRowSize() ; i++ ){				// loop for initialize the board according to game size 
			for(int j=0 ; j < getColumnSize() ; j++){
				if(!isCellAForbiddenCell(cell(i,j))){
					setCell(i,j,counter);
					counter++;
				}
			}
		}
		currentRow = getRowSize()-1;
		currentColumn = getColumnSize()-1;
		setCell(currentRow,currentColumn,BLANK_SPACE);
		resetLastMove();
		resetTotalMove();
	}

	/**
	 * Reads the board from the file given as function parameter. 
	 * If the file cannot be opened. There will be an error message and board does not change.
	 * @param fileName File name for reading
	 */
	public void readFromFile(String fileName){
		Scanner fileScanner = null;
		try{
			File file = new File(fileName);
			setSizeFromFile(file);
			fileScanner = new Scanner(file);

			for(int i=0 ; i < getRowSize() ; i++ ){							// loop for initialize the board according to game size 
				for(int j=0 ; j < getColumnSize() ; j++){
					setCell(i,j,Integer.parseInt(fileScanner.next().replace("bb",String.valueOf(BLANK_SPACE)).replace("00",String.valueOf(FORBIDDEN_CELL))));
					if(cell(i,j) == BLANK_SPACE){
						currentRow=i;
						currentColumn=j;
					}
				}
			}
		}
		catch(Exception e){
			System.out.println("Something went wrong with reading file!");
		}
		finally {
			fileScanner.close();
		}

	}

	private void setSizeFromFile(File file)throws IOException{
		int lineCounter = 0;
		int columnCounter = 0;

		Scanner fileScanner = new Scanner(file);
		String str = fileScanner.nextLine();

		for(Scanner lineScnr = new Scanner(str) ; lineScnr.hasNext() ; lineScnr.next() , columnCounter++);
		lineCounter++;
		for( ;fileScanner.hasNextLine() ; fileScanner.nextLine() , lineCounter++ );	
			
		fileScanner.close();
		setSize(lineCounter,columnCounter);
	}

	/**
	 * Writes the board to the file given as function parameter
	 * @param fileName File name for writing
	 * @throws IOException When file cannot be opened
	 */
	public void writeToFile(String fileName)throws IOException{
		FileWriter fileWriter=null;
		try{
			fileWriter = new FileWriter(fileName);
   			fileWriter.write(toString());
		}	
		finally{
				fileWriter.close();
		}
	}

	/**
	 * Produces the board as string
	 */
	public String toString(){
		String str = "";

		for(int i=0 ; i < getRowSize() ; i++){
			for(int j=0 ; j < getColumnSize() ; j++){
				if(isCellANumber(cell(i,j))){		//checking for blank space or forbidden cell
					if ( isCellADigit(cell(i,j))) 	//checking for one digit intiger. if it is put a '0' before it to look '01'
						str = str + "0";
					str = str + String.format("%d ",cell(i,j));
				}	
				else if(isCellAForbiddenCell(cell(i,j)))
					str = str + "00 ";
				else 
					str = str + "bb ";
			}
			str = str + "\n";
		}
		return str;
	}


	/**
	 * Swap the contents of two cell
	 * @param currentRow Row for first cell
	 * @param currentColumn Column for first cell
	 * @param postMoveRow Row for second cell
	 * @param postMoveColumn Column for second cell
	 */
	protected void swapNumbers(int currentRow,int currentColumn,int postMoveRow,int postMoveColumn){
		int backupNumber;
		backupNumber = cell(currentRow,currentColumn) ;
		setCell(currentRow,currentColumn,cell(postMoveRow,postMoveColumn)) ;
		setCell(postMoveRow,postMoveColumn,backupNumber); 
	}

	/**
	 * Resets last move
	 */
	public void resetLastMove(){
		lastMoveChar = 'S';
	}

	/**
	 * Resets total move
	 */
	public void resetTotalMove(){
		totalMove = 0;
	}

	/**
	 * Checks the cell for forbidden cell
	 * @param cellIndex
	 * @return True if the cell is forbidden cell
	 */
	protected boolean isCellAForbiddenCell(int cellIndex){
		return (cellIndex == FORBIDDEN_CELL);
	}

	/**
	 * Setter for last move
	 * @param moveOperator
	 */
	public void setLastMove(char moveOperator){
		lastMoveChar=moveOperator;
	}

	/**
	 * Checks that if the cell is valid in current board
	 * @param row
	 * @param column
	 * @return True if the cell valid
	 */
	protected boolean isCellValid(int row, int column){
		return row < getRowSize() && row >= 0 && column < getColumnSize() && column >= 0;
	}

	/**
	 * Checks that if the move is unvalid
	 * @param postMoveRow
	 * @param postMoveColumn
	 * @return True if the move unvalid
	 */
	protected boolean isMoveUnvalid( int postMoveRow ,  int postMoveColumn){
		return postMoveRow > getRowSize()-1 || postMoveRow < 0 || postMoveColumn > getColumnSize()-1 || postMoveColumn < 0 
				|| isCellAForbiddenCell(cell(postMoveRow,postMoveColumn));
	}

	/**
	 * Checks that if the cell is number
	 * @param cellIndex
	 * @return True if the cell number
	 */
	protected boolean isCellANumber( int cellIndex){
		return (cellIndex != BLANK_SPACE  && cellIndex != FORBIDDEN_CELL);
	}

	/**
	 * Checks that if the cell is digit
	 * @param cellIndex
	 * @return True if the cell digit
	 */
	protected boolean isCellADigit( int cellIndex){
		return (cellIndex < 10 && cellIndex > -1);
	}

	/**
	 * Getter for row size
	 * @return Row size
	 */
	public int getRowSize(){
		return totalRow;
	}

	/**
	 * Getter for column size 
	 * @return Column size
	 */
	public int getColumnSize(){
		return totalColumn;
	}
	
	/**
	 * Getter for current row
	 * @return Current row
	 */
	public int getCurrentRow(){
		return currentRow;
	}
	
	/**
	 * Getter for current column
	 * @return Current column
	 */
	public int getCurrentColumn(){
		return currentColumn;
	}

	/**
	 * Increases to total board counter
	 */
	protected void increaseTotalBoard(){
		totalBoard++;
	}

	/**
	 * Getter for total board
	 * @return Total board
	 */
	public static int NumberOfBoards(){
		return totalBoard;
	}

	/**
	 * Getter for last move
	 * @return Last move
	 */
	public char lastMove(){
		return lastMoveChar;
	}

	/**
	 * Getter for number of moves
	 * @return Number of moves
	 */
	public int numberOfMoves(){
		return totalMove;
	}
}