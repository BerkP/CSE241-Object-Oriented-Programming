using namespace std;

class NPuzzle{
public:
	void print()const;
	void printReport()const;
	void readFromFile(string );
	void writeToFile(string );
	void shuffle();
	void reset();
	bool setSize(int  , int );
	void moveRandom();
	void move(char );
	void solvePuzzle();
	static int stringCheckerAndConverter(string );
	friend ostream& operator<<(ostream&  , const NPuzzle& );
	friend istream& operator>>(istream& isObj , NPuzzle& gameBoard);

private:
	class Board{
	public:
		void print()const;
		void readFromFile(NPuzzle& gameBoard , istream& sourceFile );
		void writeToFile(const NPuzzle& gameBoard , ostream& sourceFile );
		void reset();
		void setSize(int  , int );
		bool move(char );
		bool isSolved()const;
		bool operator ==(const Board otherBoardObj)const;
		int operator()( int row,  int column)const{ return boardVec[row][column];};
		void setCurrentRow(int number){currentRow = number;};
		void setCurrentColumn(int number){currentColumn = number;};
		void setTotalRow(int number) { totalRow = number;};
		void setTotalColumn(int number){ totalColumn = number;}; 
		int getTotalRow()const{ return totalRow;};
		int getTotalColumn()const{ return totalColumn;};
		int getShuffleSize();
		void swapNumbers(int&  , int& );
		void resetMoveCount();
		void resetLastMove();
		int numberOfMoves()const{ return moveCount;};
		int numberofBoards(const NPuzzle& gameBoard)const{ return gameBoard.boardObjVec.size();};
		char lastMove()const{ return lastMoveChar;};
		void reverseMove(char );
		void resetBoardVec(){ boardVec.resize(0); };
		void pushVec( const vector<int>& inputVec) {boardVec.push_back(inputVec);};
	private:
		const int BLANK_SPACE = -1 ,
				  FORBIDDEN_CELL = -2;
		vector<vector<int>> boardVec;
		char lastMoveChar = 'S'; 				// initially 's'
		int moveCount =0,
			totalRow ,
			totalColumn , 
			currentRow , 
			currentColumn;
	};
private:
	Board boardObj;
	vector<Board> boardObjVec;

	bool checkForDuplicate(const Board& tempBoardObj ,const int& indexNumber)const;
	bool createObjectForVector(const int& indexNumber , char moveOperator);
	void goBackFromSolvedPuzzle();
};