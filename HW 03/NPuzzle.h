using namespace std;

class NPuzzle{
public:
	void print()const;
	void printReport()const;
	void readFromFile(string );
	void writeToFile(string )const;
	void shuffle();
	void reset();
	bool setSize(int  , int );
	void moveRandom();
	void moveIntelligent();
	void move(char );
	void solvePuzzle();
	static int stringCheckerAndConverter(string );
private:
	class Board{
	public:
		void print()const;
		void readFromFile(string );
		void writeToFile(string )const;
		void reset();
		void setSize(int  , int );
		bool move(char );
		bool isSolved()const;
		bool moveIntelligent();
		int getShuffleSize()const;
		bool moveComparator(int  , int  , int& );
		int moveCalculator(int  , int  , int );
		void swapNumbers(int&  , int& );

	private:
		const int BLANK_SPACE = -1 ,
				  FORBIDDEN_CELL = -2;
		static const int MAX_GAME_SIZE = 9;
		int boardArr[MAX_GAME_SIZE][MAX_GAME_SIZE];
		int totalRow ,
			totalColumn , 
			currentRow , 
			currentColumn;
	};
private:
	Board boardObj;	
	int moveCount;
};