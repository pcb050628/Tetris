#pragma once
#include "define.h"

class Camera
{
private:
	Camera();
	~Camera();

	static Camera* Inst;

public:
	static Camera* GetInst()
	{
		if (Inst == nullptr)
			Inst = new Camera;
		
		return Inst;
	}

private:
	Vec2 m_LookAt;
	Vec2 m_Dist;

public:
	void Update();
	void GetRenderPos(Vec2& _pos) { _pos -= m_Dist; }

};

