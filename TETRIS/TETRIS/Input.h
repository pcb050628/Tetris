#pragma once
#include "structs.h"
#include "enums.h"

class Input
{
private:
	Input();
	~Input();

	static Input* Inst;

public:
	static Input* GetInst()
	{
		if (Inst == nullptr)
			Inst = new Input;

		return Inst;
	}

private:
	KEY_DATA mKeys[(int)KEY::END];
	Vec2 m_MousePos;

public:
	void Update();

	KEY_STATE KeyCheck(KEY _key) { return mKeys[(unsigned int)_key].eState; }
	bool GetKeyPressed(KEY _key) { return mKeys[(unsigned int)_key].bPressed; }

	Vec2 GetMousePos() { return m_MousePos; }
	
public:
	void Init();

};

