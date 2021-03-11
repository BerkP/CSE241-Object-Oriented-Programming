#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H
#include "AbstractBoard.h"

namespace GTU_PKGZ{

	class BoardArray2D:public AbstractBoard{
	public:
		BoardArray2D();
		/*Default const */
		BoardArray2D(int ,int);
		BoardArray2D(const BoardArray2D& );
		/*Copy constructor - Part of BIG3 */
		~BoardArray2D();
		/* Destructor  - Part of BIG3*/
		void setSize(int rowInput , int columnInput)override;
		virtual int& operator()(int ,int );
		virtual const int& operator()(int ,int )const;
		const BoardArray2D& operator=(const BoardArray2D&);
		/*Assignment operator - Part of BIG3 */
	private:
		void emptyBoard();
	private:
		int** Board;
	};


};


#endif