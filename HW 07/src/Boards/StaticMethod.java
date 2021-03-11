package Boards;
/**
 * 
 * StaticMethod class to hold the static isSequanceGoToSolituon method
 * 
 * @author Berk Pekgoz GTU 171044041
 *
 */
public class StaticMethod{
	/**
	 *  A static method that takes an array of AbstractBoard references and returns true if the array contains a valid sequence of moves for a solution
	 * @param arrayOfBoards Array of AbstractBoard referances
	 * @return True if the sequance goes to solituon
	 */
	public static boolean isSequanceGoToSolituon( AbstractBoard[]  arrayOfBoards){
	/* Takes an array of AbstractBoard pointers and returns true */ 
	/*if the array contains a valid sequence of moves for a solution */
	int size = arrayOfBoards.length;
		if(!arrayOfBoards[size-1].isSolved())
			return false;

		for(int i=0 ; i < size-1 ; i++){
			if( !isMoveBetweenTwoBoardsValid(arrayOfBoards[i],arrayOfBoards[i+1])){
				return false;
			}
		}
		return true;
	}

	private static boolean isCellOneOfTheBlankSpaces( AbstractBoard board1 ,  AbstractBoard board2 , int row , int column){
		return ((row==board1.getCurrentRow() && column==board1.getCurrentColumn()) || (row==board2.getCurrentRow() && column==board2.getCurrentColumn()));
	}

	private static boolean isBlankSpacesConsecutive(int rowDistance , int columnDistance){
		return (((rowDistance==-1 || rowDistance==1) && columnDistance==0) || ((columnDistance==-1 || columnDistance==1) && rowDistance==0));
	}

	private static boolean isSizesOfBoardsSame( AbstractBoard board1,  AbstractBoard board2){
		return (board1.getRowSize() == board2.getRowSize() && board1.getColumnSize() == board2.getColumnSize());
	}


	private static boolean isMoveBetweenTwoBoardsValid( AbstractBoard board1 ,  AbstractBoard board2){
		if (!isSizesOfBoardsSame(board1,board2))
			return false;

		int rowDistance = board1.getCurrentRow() - board2.getCurrentRow();
		int columnDistance = board1.getCurrentColumn() - board2.getCurrentColumn();

		if( !isBlankSpacesConsecutive(rowDistance,columnDistance))
			return false;

		for(int row=0; row<board1.getRowSize(); row++){
			for(int column=0; column<board1.getColumnSize(); column++){
				if( !isCellOneOfTheBlankSpaces(board1,board2,row,column) && board1.cell(row,column) != board2.cell(row,column))
					return false;
			}
		}
		return true;
	}


}