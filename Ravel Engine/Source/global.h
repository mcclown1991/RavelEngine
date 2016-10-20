#ifndef GLOBAL_H
#define GLOBAL_H

#include <hge.h>
#include <hgeFont.h>
#include <hgecolor.h>
#include "DataType.h"

enum eItemTypes
{
};

class Global
{
public:
	Global();

	~Global();

	bool Initialise		(	HGE*		r_pHge, 
							hgeFont*	r_pFontLarge, 
							hgeFont*	r_pFontSmall, 
							sInt32		r_nScreenWidth, 
							sInt32		r_nScreenHeight,
							float32		r_fCameraX,
							float32		r_fCameraY);

	HGE*		GetHge()							{ return m_pHge; }
	hgeFont*	GetFontSmall()						{ return m_pFontSmall; }
	hgeFont*	GetFontLarge()						{ return m_pFontLarge; }
	sInt32		GetScreenWidth()					{ return m_nScreenWidth; }
	sInt32		GetScreenHeight()					{ return m_nScreenHeight; }
	fVector2	GetCameraPosition()					{ return m_vCamera; }
	float32		GetZoomRatio()						{ return m_fZoomRatio; }
	void		SetZoomRatio(float32 r_fRatio)		{ m_fZoomRatio = r_fRatio; }

	fVector2	ConvertToOnScreenPosition(fVector2 r_vPos);
	
	fVector2	m_vCamera;
	
private:
	HGE*		m_pHge;
	hgeFont*	m_pFontLarge;
	hgeFont*	m_pFontSmall;
	sInt32		m_nScreenWidth;// 800
	sInt32		m_nScreenHeight;// 600
	float32		m_fZoomRatio;
};

Global* GetGlobal(void); 

#endif