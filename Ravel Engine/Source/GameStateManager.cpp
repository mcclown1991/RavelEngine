/******************************************************************************/
/*!
\file		GameStateManager.cpp
\project	Walkure

\author 	Nazrin Shah Bin Azlan Shah, nazrinshah.a, 390002313

\brief

	Work percentage 100

	Work details

	All content © 2014 DigiPen (SINGAPORE) Corporation, all rights reserved.
 */
/******************************************************************************/

#include "GameStateManager.h"
#include "GameState.h"
//#include "PauseMenuState.h"

/******************************************************************************/
/*!
	\fn void GameStateManager::GSM_Init()

	\brief
		Initializes the gsm's variables.
*/
/******************************************************************************/
void GameStateManager::GSM_Init()
{
	m_running = true;
	m_paused = false;
	m_changeState = false;
}

/******************************************************************************/
/*!
	\fn void GameStateManager::GSM_Exit()

	\brief
		Unloads all active states before exiting program
*/
/******************************************************************************/
void GameStateManager::GSM_Exit()
{	
	while(!m_gameStates.empty())
	{
		m_gameStates.back()->Free();
		m_gameStates.back()->Unload();
		m_gameStates.pop_back();
	}
	QuitGame();
}

/******************************************************************************/
/*!
	\fn void GameStateManager::StateUpdate()

	\brief
		Updates the active state
*/
/******************************************************************************/
void GameStateManager::StateUpdate()
{
	if(!m_gameStates.empty())
		m_gameStates.back()->Update();
}

/******************************************************************************/
/*!
	\fn void GameStateManager::StateDraw()

	\brief
		Draws the active state
*/
/******************************************************************************/
void GameStateManager::StateDraw()
{
	/*if(!m_gameStates.empty())
	{
		// if paused, there will be 2 states active
		if(m_paused)
		{
			for(auto elem : m_gameStates)
				elem->Draw();
		}

		else
			m_gameStates.back()->Draw();
	}*/
}
	
/******************************************************************************/
/*!
	\fn void GameStateManager::ChangeState()

	\brief
		Pops the active states before loading the next state
*/
/******************************************************************************/
void GameStateManager::ChangeState()
{
	while(!m_gameStates.empty())
	{
		m_gameStates.back()->Free();
		m_gameStates.back()->Unload();
		m_gameStates.pop_back();
		//AESysReset();
	}

	m_paused = false;
	
	m_gameStates.push_back(m_nextState);
	m_gameStates.back()->Load();
	m_gameStates.back()->Init();

	m_currState = m_nextState;
	m_changeState = false;
}

/******************************************************************************/
/*!
	\fn void GameStateManager::ResetState()

	\brief
		Restarts the current state
*/
/******************************************************************************/
void GameStateManager::ResetState()
{
	m_gameStates.back()->Free();
	m_gameStates.back()->Init();
}

/******************************************************************************/
/*!
	\fn void GameStateManager::PauseState(GameState *subState)

	\brief
		Push in the pausestate

	\param *subState
		The state to push on top of the current state, could be pause or
		win/lose state
*/
/******************************************************************************/
void GameStateManager::PauseState(GameState *subState)
{
	if(!m_gameStates.empty())
		m_gameStates.back()->Pause();
		
	m_paused = true;

	m_gameStates.push_back(subState);
	m_gameStates.back()->Load();
	m_gameStates.back()->Init();
}

/******************************************************************************/
/*!
	\fn void GameStateManager::UnPauseState()

	\brief
		Pop out the pause state
*/
/******************************************************************************/
void GameStateManager::UnPauseState()
{
	if(!m_gameStates.empty())
	{
		m_gameStates.back()->Free();
		m_gameStates.back()->Unload();
		m_gameStates.pop_back();

		if(m_gameStates.size() == 1)
			m_paused = false;
	}

	if(!m_gameStates.empty())
		m_gameStates.back()->Resume();
}
