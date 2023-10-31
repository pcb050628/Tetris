#pragma once
#include "header.h"

class Entity
{
private:
	static UINT_PTR g_NextID;

private:
	const UINT_PTR m_ID;
	bool m_bDead;

public:
	UINT_PTR GetID() { return m_ID; }
	void SetDead() { m_bDead = true; }
	bool IsDead() { return m_bDead; }

public:
	Entity();
	virtual ~Entity();
};

