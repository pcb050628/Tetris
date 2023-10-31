#include "Entity.h"

UINT_PTR Entity::g_NextID = 0;

Entity::Entity()
	:m_ID(g_NextID++)
	,m_bDead(false)
{
}

Entity::~Entity()
{
}
