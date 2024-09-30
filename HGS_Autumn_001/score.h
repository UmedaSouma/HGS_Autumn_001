#pragma once
//===========================================================================================================================================================
// 
// score.cppÇÃÉwÉbÉ_Å[ [score.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"

class CScore
{
public:
	CScore();
	~CScore();

	static void SetScore(int addscore) { m_nScore += addscore; }
	static void ResetScore() { m_nScore = 0; }
	static int GetScore() { return m_nScore; }
private:
	static int m_nScore;
};


#endif // !SCORE_H_
