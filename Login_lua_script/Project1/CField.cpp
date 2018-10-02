#include "CField.h"



CField * CField::Instance()
{
	static CField instance;
	return &instance;
}

CField::CField()
{
}


CField::~CField()
{
}
void CField::ScoreReset(int *level, int * exp)
{
	if (*exp >= 100) {
		*level= *level + 1;
		*exp -= 100;
	}
}

void CField::Play(int num)
{
	system("cls");
	SelectMode();

	float weight = 50;

	int me_level = m_member[num]->GetLevel();
	int me_exp = m_member[num]->GetExp();
	int me_hp = m_member[num]->GetHp();

	std::cout << "전투 종료" << std::endl;
	std::cout << "전투 정보 : " << weight << "경험치 획득" << std::endl;
	me_exp += weight;
	ScoreReset(&me_level, &me_exp);
	std::cout << "레벨 :" << me_level << "경험치 " << me_exp << std::endl;

	m_member[num]->SetLevelExp(me_level, me_exp);
}
