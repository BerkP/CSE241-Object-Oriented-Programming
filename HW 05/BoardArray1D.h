#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H
#include "AbstractBoard.h"

namespace GTU_PKGZ{

	class BoardArray1D:public AbstractBoard{
	public:
		BoardArray1D();
		/*Default const */
		BoardArray1D(int ,int );
		BoardArray1D(const BoardArray1D& );
		/*Copy constructor - Part of BIG3 */
		~BoardArray1D();
		/* Destructor  - Part of BIG3*/
		void setSize(int rowInput , int columnInput)override;
		virtual int& operator()(int ,int );
		virtual const int& operator()(int ,int )const;
		const BoardArray1D& operator=(const BoardArray1D&);
		/*Assignment operator - Part of BIG3 */
	private:
		int* Board;
	};

}

#endif