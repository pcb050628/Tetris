#include "Time.h"
#include "Engine.h"

Time* Time::Inst = nullptr;

Time::Time()
	:m_fTime(NULL)
	,m_iCall(NULL)
{
}

Time::~Time()
{
}

void Time::Init()
{
	QueryPerformanceFrequency(&m_CpuFrequency);
	QueryPerformanceCounter(&m_PrevFrequency);
}

void Time::Update()
{
	QueryPerformanceCounter(&m_CurFrequency);

	m_DeltaTime = float(m_CurFrequency.QuadPart - m_PrevFrequency.QuadPart) / float(m_CpuFrequency.QuadPart);

	m_PrevFrequency = m_CurFrequency;

	if (m_DeltaTime > (1.f / 60.f)) // 프레임 제한
		m_DeltaTime = (1.f / 60.f);

	m_fTime += m_DeltaTime;
	if (1.f <= m_fTime)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		SetWindowText(Engine::GetInst()->GetHwnd(), szText);

		m_iCall = 0;
		m_fTime = 0.f;
	}

	++m_iCall;
}

