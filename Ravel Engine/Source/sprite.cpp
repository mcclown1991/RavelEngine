//#include "sprite.h"
//#include <assert.h>
//
//Sprite::Sprite(HTEXTURE* r_pTexSprite, float r_fWidth, float r_fHeight, float r_fYOffset)
//{
//	//check texture given is valid, if not refuse to create
//	if(r_pTexSprite)
//	{
//		//first frame (at 0,0) by default
//		m_pHgeSprite = new SPRITE(*r_pTexSprite,0.0f,0.0f,r_fWidth, r_fHeight);
//		//m_pTexSprite = r_pTexSprite;
//		//SetLogicalYOffset( (sInt32) r_fYOffset);
//	}
//	else
//	{
//		m_pHgeSprite = NULL;
//	}
//	m_vSize.x = r_fWidth;
//	m_vSize.y = r_fHeight;
//	m_nFacingDirection	= 0;
//	m_nFrame			= 0;
//	//m_nTotalFrames		= 0;
//
//	//m_nFrameBaseOffY	= 0;
//
//	m_bStatic = false;
//}
//
//Sprite::Sprite(rawTEXTURE* r_pTexSprite, float r_fWidth, float r_fHeight, float r_fPosX, float r_fPosY, float r_fYOffset)
//{
//	//check texture given is valid, if not refuse to create
//	if(r_pTexSprite)
//	{
//		//first frame (at 0,0) by default
//		m_pHgeSprite = new SPRITE(*r_pTexSprite,0.0f,0.0f,r_fWidth, r_fHeight);
//		//m_pTexSprite = r_pTexSprite;
//		m_vScreenPosition.x = r_fPosX;
//		m_vScreenPosition.y = r_fPosY;
//		//SetLogicalYOffset( (sInt32) r_fYOffset);
//	}
//
//	else
//	{
//		m_pHgeSprite = NULL;
//	}
//	//hge_Rect = new hgeRect(r_fPosX, r_fPosY, r_fWidth + r_fPosX, r_fHeight + r_fPosY);
//	m_vSize.x = r_fWidth;
//	m_vSize.y = r_fHeight;
//	m_nFacingDirection	= 0;
//	//m_nFrame			= 0;
//	//m_nTotalFrames		= 0;
//
//	//m_nFrameBaseOffY	= 0;
//
//	m_bStatic = false;
//}
//
////------------------------------------------------------------------------------------
//// Description	: Destructor - ensure all claimed memory items are deleted here
//// Author		: MGG
//// Date			: 20/11/08
//// Last Changed :
////------------------------------------------------------------------------------------
//Sprite::~Sprite(void)
//{
//	//if( m_pTexSprite ) delete m_pTexSprite;
//	if( m_pHgeSprite ) delete m_pHgeSprite;
//}
//
////------------------------------------------------------------------------------------
//// Description	: Main Sprite Render Method. All Sprite rendering occurs here
//// Author		: MGG
//// Date			: 20/11/08
//// Last Changed :
////------------------------------------------------------------------------------------
//bool Sprite::Render(Vector2 r_vPos)
//{
//
//	m_pHgeSprite->RenderStretch(r_vPos.x, r_vPos.y,
//		r_vPos.x + GetSize().x, r_vPos.y + GetSize().y);
//
//	return true;
//}
//
//bool Sprite::Render(Vector2 const& pos, Matrix3x3 const & transform)
//{
//	Vector2 left (pos), right (pos + GetSize());
//	left = transform * left;
//	right = transform * right;
//
//	m_pHgeSprite->RenderStretch(left.x, left.y,
//		right.x, right.y);
//
//	//m_pHgeSprite->RenderEx(pos.x, pos.y, )
//
//	return true;
//}
//
//bool Sprite::Render(Vector2 const & pos, float angle, float hscale, float vscale)
//{
//	m_pHgeSprite->RenderEx(pos.x, pos.y, angle, hscale, vscale);
//
//	return false;
//}
//
//bool Sprite::Render(Vector2 quad[4])
//{
//	m_pHgeSprite->Render4V(quad[0].x, quad[0].y, quad[1].x, quad[1].y, quad[2].x, quad[2].y,
//		quad[3].x, quad[3].y);
//	return false;
//}
//
////------------------------------------------------------------------------------------
//// Description	: Sets the Texture Map to use for the sprite and their animations
//// Author		: MGG
//// Date			: 20/11/08
//// Last Changed :
////------------------------------------------------------------------------------------
//bool Sprite::SetTexture(HTEXTURE* r_pTexture)
//{
//	assert(r_pTexture);
//
//	//m_pTexSprite = r_pTexture;
//
//	return true;
//}
//
////------------------------------------------------------------------------------------
//// Description	: Returns the Sprites current screen position
//// Author		: MGG
//// Date			: 20/11/08
//// Last Changed :
////------------------------------------------------------------------------------------
//Vector2 Sprite::GetScreenPosition()	
//{
//	return( m_vScreenPosition );
//}
//
//Vector2 Sprite::GetSize()
//{
//	return ( m_vSize );
//}
//
//
//bool Sprite::Flip()
//{
//	m_vSize.x -= m_vSize.x * 2;
//	m_vScreenPosition.x -= m_vSize.x;
//	return true;
//}
//
//bool Sprite::UpdateScreenPosition()
//{
//	m_pHgeSprite->SetTextureRect(m_vSize.x, 0, m_vSize.x, m_vSize.y);
//
//	return true;
//}
//
//bool Sprite::ReverseScreenPosition()
//{
//	if(m_nFrame>0)
//	return false;
//	else
//	{
//		m_pHgeSprite->SetTextureRect(0, 0, m_vSize.x, m_vSize.y);
//	}
//	return true;
//}
//
//bool Sprite::IsPointOver(float32 pos_x, float32 pos_y)
//{
//	if(hge_Rect->TestPoint(pos_x, pos_y))
//		return true;
//	else
//		return false;
//	return false;
//}