#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H
#include <vector>
#include "AbstractBoard.h"

using namespace std;

namespace GTU_PKGZ{

	class BoardVector:public AbstractBoard{
	public:
		BoardVector();
		/* Default constr */
		BoardVector(int ,int);
		void setSize(int rowInput,int columnInput) override;
		virtual int& operator()(int ,int );
		virtual const int& operator()(int ,int )const;
	private:
		vector<vector<int>> boardVec;
	};


	
};

#endif