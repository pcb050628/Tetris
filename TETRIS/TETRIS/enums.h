#pragma once

enum class LAYER
{
	BACKGROUND,
	BLOCK,
	UI,
	END
};

enum class SCENE_TYPE
{
	TITLE,
	PLAY,
	END,
};

enum class KEY
{
	NUM0,NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,

	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,

	TAB, LSHIFT, MENU, LCTR, SPACE,
	ESCAPE, RETURN, BACK,

	LEFT, RIGHT, UP, DOWN,

	LBTN, RBTN,	
	
	END
};

enum class KEY_STATE
{
	Pressed,
	Hold,
	Release,
	None
};

enum class COLOR
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	ORANGE,
	MINT,
	GREY,
	BLACK,
	WHITE,
	END
};

enum class BLOCK_TYPE
{
	O,
	J,
	L,
	Z,
	S,
	I,
	T,
	GHOST,
};

enum class BLOCK_STATE
{
	FRONT,
	RIGHT,
	BACK,
	LEFT,
};