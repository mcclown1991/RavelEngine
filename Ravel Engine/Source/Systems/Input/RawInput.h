#pragma once

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>
#include <xinput.h>
#include <bitset>
#include <vector>
#include "RavelMath.h"
#include "RavelEngine.h"

#pragma comment(lib,"xinput.lib")

static BYTE		msg[256];
static MSG		_ms;
static HWND		hwnd;
static std::vector<WORD> traps;

//Defines list
#define RK_ESC			0x1B
#define RK_SPACE		0x20
#define RK_PAGEUP		0x21
#define RK_PAGEDOWN		0x22
#define RK_END			0x23
#define RK_HOME			0x24
#define RK_LEFT			0x25
#define RK_UP			0x26
#define RK_RIGHT		0x27
#define RK_DOWN			0x28

#define RK_RETURN		0x0D

#define RK_0			0x30
#define RK_1			0x31
#define RK_2			0x32
#define RK_3			0x33
#define RK_4			0x34
#define RK_5			0x35
#define RK_6			0x36
#define RK_7			0x37
#define RK_8			0x38
#define RK_9			0x39

#define RK_A			0x41
#define RK_B			0x42
#define RK_C			0x43
#define RK_D			0x44
#define RK_E			0x45
#define RK_F			0x46
#define RK_G			0x47
#define RK_H			0x48
#define RK_I			0x49
#define RK_J			0x4A
#define RK_K			0x4B
#define RK_L			0x4C
#define RK_M			0x4D
#define RK_N			0x4E
#define RK_O			0x4F
#define RK_P			0x50
#define RK_Q			0x51
#define RK_R			0x52
#define RK_S			0x53
#define RK_T			0x54
#define RK_U			0x55
#define RK_V			0x56
#define RK_W			0x57
#define RK_X			0x58
#define RK_Y			0x59
#define RK_Z			0x5A

#define RK_LCTRL		0xA2

constexpr auto RK_MOUSE_LEFT = WM_LBUTTONDOWN;
constexpr auto RK_MOUSE_RIGHT = WM_RBUTTONDOWN;
constexpr auto RK_MOUSE_MIDDLE = WM_MBUTTONDOWN;

typedef WORD Keystroke;

constexpr Keystroke UP = RK_UP;


void		InitInput(HWND hWnd);
void		SetMessage(const MSG&);
void		StartKeyTrap();
void		StopKeyTrap();
//=========================================================================
//=========================================================================
/** Takes in the key desired to check if it is being pressed
*
* @param data	VK code for the key
*/
bool		OnKeyPress(WORD data);

//=========================================================================
//=========================================================================
/** Takes in the key desired to check if it is being released
*
* @param data	WM code for the key
*/
bool		OnKeyRelease(WORD data);

//=========================================================================
//=========================================================================
/** Takes in the key desired to check if it is being pressed
*
* @param data	WM code for the key
*/
bool		OnKeyHold(WORD data);

//=========================================================================
//=========================================================================
/** Takes in two ints to store mouse X and Y locations
*
* @param mX X location
* @param mY Y location
*/
bool		GetMousePos(int& mX, int& mY);

//=========================================================================
//=========================================================================
/** Checks if mouse button is pressed 0 - Left, 1 - Right, 2 - Middle
*/
bool		GetMouseButtonDown(int button);

//=========================================================================
//=========================================================================
/** Checks if left mouse button is pressed
*/
bool		OnLClick();

//=========================================================================
//=========================================================================
/** Checks if right mouse button is pressed
*/
bool		OnRClick();

//=========================================================================
//=========================================================================
/** Checks if mouse wheel is moved
*/
bool		OnWheelMove();

void		GetMousePos(float& x, float& y);

#define WIN32_LEAN_AND_MEAN

class XBOXController
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;

	float deadzoneX;
	float deadzoneY;

public:
	//=========================================================================
	//=========================================================================
	/** Set up XBOX360 controller
	*/
	XBOXController() : deadzoneX(0.3f), deadzoneY(0.3f) {};
	XBOXController(int playerNumber);
	~XBOXController() {}

	void SetPlayerNumber(int playerNumber);

	//=========================================================================
	//=========================================================================
	/** Get Controller state
	*/
	XINPUT_STATE GetState();

	//=========================================================================
	//=========================================================================
	/** Check if controller is connected
	*/
	bool IsConnected();

	inline void UpdateControllerNum(const int playerNum)
	{
		_controllerNum = playerNum - 1;
	}

	void Vibrate(int leftVal = 0, int rightVal = 0);

	bool Refesh();

	bool IsPressed(WORD button);

	const float LeftStickAngle();
	const float RightStickAngle();
	const Vector2 LeftStickVector();
	const Vector2 RightStickVector();

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;
};
