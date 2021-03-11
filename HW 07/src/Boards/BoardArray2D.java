package Boards;
/**
 * 
 * BoardArray2D class represents the board configuration with 2D Array
 * 
 * @author Berk Pekgoz GTU 171044041
 *
 */
public class BoardArray2D extends AbstractBoard{

	private int[][] board;

	/**
	 * No paramater constructor for BoardArray2D.
	 * Size of board is setted to (3,3) as default.
	 */
	public BoardArray2D(){
		this(3,3);
	}

	
	/**
	 * Constructor with size parameters.
	 * @param rowSize Parameter for row size
	 * @param columnSize Parameter for column size
	 */
	public BoardArray2D(int rowSize , int columnSize){
		super();
		board=null;
		if(rowSize < 3 || columnSize < 3){
			rowSize = 3 ; 
			columnSize = 3;
		}
		this.setSize(rowSize,columnSize);
		reset();
	}
	
	/**
	 * Copy Constructor with another BoardArray2D object referance
	 * @param other Board2D object referance for copy constructor
	 */
	public BoardArray2D(BoardArray2D other){
		increaseTotalBoard();
		setSize(other.getRowSize(),other.getColumnSize());

		for(int i=0; i < getRowSize(); i++){
			for(int j=0; j< getColumnSize(); j++){
				board[i][j] = other.board[i][j];
			}
		}
	}

	public void setSize(int row , int column){
		if(row < 3 || column < 3){
			row = 3 ; 
			column = 3;
		}
		super.setSize(row,column);
		board = new int[row][column];
		reset();
	}

	public int cell(int row , int column){
		if( !isCellValid(row,column))
			System.exit(1);
		return board[row][column];
	}

	protected void setCell(int row , int column , int data){
		if( !isCellValid(row,column))
			System.exit(1);
		board[row][column] = data;
	}



}