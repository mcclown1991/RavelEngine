#include "Input.h"
#include <iostream>
#include <algorithm>

void InitInput(HWND hWnd)
{
	for (int i = 0; i < 256; i++) {
		msg[i] = 0x00;
	}
	hwnd = hWnd;
}

void SetMessage(const MSG& ms)
{
	BOOL er = GetKeyboardState(msg);
	_ms = ms;
	DWORD error = GetLastError();
	if (!er)
	{
		std::cout << error << std::endl;
	}
}

void StartKeyTrap() {
	traps.clear();
	//traps[0] = 0x00;
}

void StopKeyTrap() {
	for (WORD i : traps) {
		msg[i] = 0x00;
	}
	SetKeyboardState(msg);
}

/** Takes in the key desired to check if it is being pressed
*
* @param data	WM code for the key
*/
bool OnKeyPress(WORD data)
{
	//& with bit 30
	if ((msg[data] & 0x80))
	{
		/*msg[data] = 0x00;
		SetKeyboardState(msg);*/
		traps.push_back(data);
		return true;
	}

	return false;
}

/** Takes in the key desired to check if it is being released
*
* @param data	WM code for the key
*/
bool OnKeyRelease(WORD data)
{
	if (~(msg[data] & 0x80))
	{
		return true;
	}
	return false;
}

/** Takes in the key desired to check if it is being pressed
*
* @param data	WM code for the key
*/
bool OnKeyHold(WORD data)
{
	if (msg[data] & 0x80)
	{
		return true;
	}

	return false;
}

/** Takes in two ints to store mouse X and Y locations
*
* @param mX X location
* @param mY Y location
*/
bool GetMousePos(int& mX, int& mY)
{
	UNREFERENCED_PARAMETER(mX);
	UNREFERENCED_PARAMETER(mY);
	/*if (msg.message == WM_MOUSEMOVE)
	{
	mX = GET_X_LPARAM(msg.lParam);
	mY = GET_Y_LPARAM(msg.lParam);
	return true;
	}*/
	return false;
}

bool GetMouseButtonDown(int button)
{
	switch (button) {
	case 0:
		return _ms.message == WM_LBUTTONDOWN ? true : false;
	case 1:
		return WM_RBUTTONDOWN ? true : false;
	case 2:
		return WM_MBUTTONDOWN ? true : false;
	}
	return false;
}

/** Checks if left mouse button is pressed
*/
bool OnLClick()
{
	if (_ms.message == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}

/** Checks if right mouse button is pressed
*/
bool OnRClick()
{
	if (_ms.message == WM_RBUTTONDOWN)
	{
		return true;
	}
	return false;
}

/** Checks if mouse wheel is moved
*/
bool OnWheelMove()
{
	/*if (msg.message == WM_MOUSEWHEEL)
	{
	return true;
	}*/
	return false;
}

void GetMousePos(float& x, float& y) {
	POINT p;
	GetCursorPos(&p);
	if (ScreenToClient(hwnd, &p)) {
		Vector2 position(static_cast<float>(p.x), static_cast<float>(p.y));
		position = RavelEngine::GetRavelEngine()->ScenceTransform() * position;
		x = position.x;
		y = -position.y;
		//std::cout << "X: " << x << "  Y: " << y << std::endl;
	}
}

XBOXController::XBOXController(int playerNumber) : deadzoneX(0.3f), deadzoneY(0.3f)
{
	// Set the Controller Number
	_controllerNum = playerNumber - 1;
}

XINPUT_STATE XBOXController::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool XBOXController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void XBOXController::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = (WORD)leftVal;
	Vibration.wRightMotorSpeed = (WORD)rightVal;

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}

bool XBOXController::Refesh()
{
	if (_controllerNum != -1)
	{
		ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
		if (XInputGetState(_controllerNum, &_controllerState) != ERROR_SUCCESS)
		{
			_controllerNum = -1;
			return false;
		}

#if (_MSC_VER == 1800)	//For VS2013 only
		float normLX = fmaxf(-1, (float)_controllerState.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)_controllerState.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRX = fmaxf(-1, (float)_controllerState.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)_controllerState.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float)_controllerState.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)_controllerState.Gamepad.bRightTrigger / 255;

#else	//Any older VS versions
		float normLX = std::max(-1.f, (float)_controllerState.Gamepad.sThumbLX / 32767);
		float normLY = std::max(-1.f, (float)_controllerState.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRY = std::max(-1.f, (float)_controllerState.Gamepad.sThumbRY / 32767);
		float normRX = std::max(-1.f, (float)_controllerState.Gamepad.sThumbRX / 32767);
								  
		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float)_controllerState.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)_controllerState.Gamepad.bRightTrigger / 255;
#endif

		return true;
	}
	return false;
}

bool XBOXController::IsPressed(WORD button)
{
	return (_controllerState.Gamepad.wButtons & button) != 0;
}

const float XBOXController::LeftStickAngle()
{
	Vector2 r(leftStickX, leftStickY);
	r.Normalize();

	float angle = atan2(r.x, r.y);

	//check for NaN
	if (angle != angle)
		return false;

	return angle;
}

const float XBOXController::RightStickAngle()
{
	Vector2 r(rightStickX, rightStickY);

	if (r.SqLenght() < 0.64f)
	{
		return false;
	}
	r.Normalize();

	float angle = atan2(r.x, r.y);

	//check for NaN
	if (angle != angle)
		angle = 0;

	std::cout << "magnitude: " << angle << std::endl;

	return angle;
}

const Vector2 XBOXController::LeftStickVector()
{
	Vector2 r(leftStickX, leftStickY);
	//r.normalize();

	return r;
}

const Vector2 XBOXController::RightStickVector()
{
	Vector2 r(rightStickX, rightStickY);
	//r.normalize();

	return r;
}