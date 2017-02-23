#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>
#include <hge.h>
#include <hgeSprite.h>
#include "DataType.h"

class Sprite
{
public:
	Sprite(rawTEXTURE* r_pTexSprite, float r_fWidth, float r_fHeight, float r_fYOffset = 0.0f);
	Sprite(rawTEXTURE* r_pTexSprite, float r_fWidth, float r_fHeight, float r_fPosX, float r_fPosY, float r_fYOffset = 0.0f);
	~Sprite(void);

	fVector2	GetScreenPosition	();
	//rectInt		GetCurrentFramePos	();

	//HTEXTURE*	GetTexture			()						{return m_pTexSprite;}

	bool		SetTexture			(rawTEXTURE* r_pTexture);
	bool		Render				(fVector2 r_v2Pos);
	bool		UpdateScreenPosition();
	bool		ReverseScreenPosition();

	fVector2	m_vScreenDrawnPosition;

	bool		SetScreenPosition	(fVector2 r_v2Pos)		{m_vScreenPosition	= r_v2Pos;			return true;}
	fVector2	GetSize				();
	bool		Flip				();
	bool		IsPointOver			(float32 pos_x, float32 pos_y);

private:

	//rawTEXTURE*	m_pTexSprite;
	SPRITE*		m_pHgeSprite;
	fVector2	m_vScreenPosition;			//top left of sprite
	fVector2	m_vSize;

	sInt32		m_nMapHeight;
	sInt32		m_nMapWidth;
	sInt32		m_nFacingDirection; 
	sInt32		m_nFrame; 
	sInt32		m_nFrameWidth; 
	sInt32		m_nFrameHeight;
	sInt32		m_nFrameBaseOffY;
	sInt32		m_nTotalFrames;
	sInt32		m_nLogicalYOffset;		// so that the "AI" position more accurately reflects the sprite

	bool		m_bStatic;			//used for things like the pitch that dont move
	bool		m_bFixedFrame;		//used for single-frame sprites that do move, like the ball shadow
	bool		m_bVisible;
	hgeRect*	hge_Rect;
};
#endif