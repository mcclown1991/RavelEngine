//#include "global.h"
//
//#include <direct.h>
//#include <stdlib.h>
//#include <iostream>
//
//Global* GetGlobal(void)
//{
//	static Global s ; 
//	return(&s) ; 
//}
//
//Global::Global(void)
//{
//}
//
//bool Global::Initialise(HGE*		r_pHge,				//pointer to the game engine
//						hgeFont*	r_pFontLarge,		//pointer to a Large Font
//						hgeFont*	r_pFontSmall,		//pointer to a Small Font
//						sInt32		r_nScreenWidth,		//record currently used screen width here
//						sInt32		r_nScreenHeight,		//record currently used screen height here
//						float32		r_fCameraX,			//record starting camera position here
//						float32		r_fCameraY)
//{
//	m_pHge			= r_pHge;
//	m_pFontLarge	= r_pFontLarge;
//	m_pFontSmall	= r_pFontSmall;
//	m_nScreenWidth	= r_nScreenWidth;
//	m_nScreenHeight	= r_nScreenHeight;
//
//	m_vCamera.x		= r_fCameraX;
//	m_vCamera.y		= r_fCameraY;
//
//
//
//	return true;										//success
//}
//
//fVector2 Global::ConvertToOnScreenPosition(fVector2 r_vPos)
//{
//	fVector2 vScreenPos(r_vPos.x + GetCameraPosition().x,
//						r_vPos.y + GetCameraPosition().y);
//
//	return vScreenPos;
//}
//
//Global::~Global()
//{
//}