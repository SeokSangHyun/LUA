#pragma once
#include "CManager.h"

class CLogIn : public CManager
{
public:
	static CLogIn* Instance();

	CLogIn();
	~CLogIn();

	void SignUp();
	int SignIn();

	void ChangePassword();
};

