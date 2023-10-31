#include "Input.h"
#include "header.h"
#include "Engine.h"

int g_KeySync[(unsigned int)KEY::END] =
{
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_TAB,
	VK_LSHIFT,
	VK_LMENU,
	VK_LCONTROL,
	VK_SPACE,

	VK_ESCAPE,
	VK_RETURN,
	VK_BACK,

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,
};

Input* Input::Inst = nullptr;

Input::Input()
{
}

Input::~Input()
{
}

void Input::Init()
{
	for (int i = 0; i < (unsigned int)KEY::END; i++)
	{
		mKeys[i] = KEY_DATA();
		mKeys[i].eKey = (KEY)i;
		mKeys[i].eState = KEY_STATE::None;
		mKeys[i].bPressed = false;
	}
}

void Input::Update()
{
	for (int idx = 0; idx < (unsigned int)KEY::END; idx++)
	{
		if (GetAsyncKeyState(g_KeySync[(unsigned int)mKeys[idx].eKey]) & 0x8001)
		{
			mKeys[idx].bPressed ? mKeys[idx].eState = KEY_STATE::Hold : mKeys[idx].eState = KEY_STATE::Pressed;

			mKeys[idx].bPressed = true;
		}
		else
		{
			mKeys[idx].bPressed ? mKeys[idx].eState = KEY_STATE::Release : mKeys[idx].eState = KEY_STATE::None;

			mKeys[idx].bPressed = false;
		}
	}

	POINT mousePos = {};
	GetCursorPos(&mousePos);
	ScreenToClient(Engine::GetInst()->GetHwnd(), &mousePos);
	m_MousePos = mousePos;
}
