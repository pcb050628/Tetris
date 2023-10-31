#pragma once
#include "framework.h"
#include "enums.h"
#include "Input.h"
#include "Time.h"

#define DT Time::GetInst()->GetDeltaTime()

#define KEY_CHECK(key, state) Input::GetInst()->KeyCheck(key) == state

#define KEY_PRESSED(key) KEY_CHECK(key, KEY_STATE::Pressed)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::Hold)
#define KEY_RELEASE(key) KEY_CHECK(key, KEY_STATE::Release)

#define SQUARESIZE 40
#define GBOARD_COLUMN 10
#define GBOARD_ROW 20
#define GBOARDHALF (Vec2(GBOARD_COLUMN / 2, GBOARD_ROW / 2) * SQUARESIZE)