#pragma once
#include <Windows.h>

class Time
{
private:
	Time();
	~Time();

	static Time* Inst;

public:
	static Time* GetInst()
	{
		if (Inst == nullptr)
			Inst = new Time();

		return Inst;
	}

private:
	LARGE_INTEGER	m_CpuFrequency;
	LARGE_INTEGER	m_PrevFrequency;
	LARGE_INTEGER	m_CurFrequency;

	float			m_DeltaTime;
	float			m_Time;
	int				m_iCall;
	float			m_fTime;

public:
	void Update();

	float GetDeltaTime() { return m_DeltaTime; }

public:
	void Init();

};

