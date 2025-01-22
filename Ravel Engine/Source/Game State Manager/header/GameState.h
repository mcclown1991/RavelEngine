/******************************************************************************/
/*!
\file		GameState.h
\project	Walkure

\author 	Nazrin Shah Bin Azlan Shah, nazrinshah.a, 390002313
\author2	Terence Peh, terence.peh, 390005313

\brief

	Work percentage
		Narzin	: 90
		Terence	: 10

	Work details
		Narzin	: everything else
		Terence	: state transition

	All content © 2014 DigiPen (SINGAPORE) Corporation, all rights reserved.
 */
/******************************************************************************/

#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <list>
#include "DataType.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "main.h"

/******************************************************************************/
/*!
\class GameState

\brief
	Base game state class inherited by all game states
*/
/******************************************************************************/
class GameState
{
public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	
	virtual void Update()		= 0;
	//virtual void Draw()		= 0;
	
	virtual void Free()		= 0;
	virtual void Unload()	= 0;
	
	virtual void Pause()	= 0;
	virtual void Resume()	= 0;

	//inline void FadeIn() { f32 alpha = m_fadeScreen->GetAlpha(); m_fadeScreen->SetAlpha(alpha+=g_dt); }
	//inline void FadeOut () { f32 alpha = m_fadeScreen->GetAlpha(); m_fadeScreen->SetAlpha( alpha-=g_dt); }

	inline void SetChangeState(bool change) { m_changeState = change; }

	//std::list<GameObject* > SceneObject;

protected:
	GameState() { }

	//std::vector<Sprites *>m_spriteList;		//!< pointers to the sprites required for the state
	//std::vector<GameObject *>m_gameObjList;	//!< pointers to all the game objects created in the state

	bool m_changeState;			//!< check if should changesate in the next frame
	bool m_transitOut;			//!< check if should transit

	
};

#endif