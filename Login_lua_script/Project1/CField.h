#pragma once
#include "CManager.h"

class CField : public CManager
{
	int my_num = -1;
public:
	static CField* Instance();

	CField();
	~CField();

	void ScoreReset(int *level, int * exp);
	void Play(int num);

};

