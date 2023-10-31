#include "Camera.h"
#include "Engine.h"

Camera* Camera::Inst = nullptr;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Vec2 Resolution = Engine::GetInst()->GetResolution();
	Vec2 Center = Resolution / 2;

	m_Dist = m_LookAt - Center;
}
