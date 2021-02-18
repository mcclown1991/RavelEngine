/******************************************************************************/
/*!
\file		GameStateManager.h
\project	Walkure

\author 	Nazrin Shah Bin Azlan Shah, nazrinshah.a, 390002313

\brief

	Work percentage 100

	Work details

	All content © 2014 DigiPen (SINGAPORE) Corporation, all rights reserved.
 */
/******************************************************************************/

#ifndef __GAMESTATEMANAGER_H__
#define __GAMESTATEMANAGER_H__

#include <vector>

class GameState;

/******************************************************************************/
/*!
\class GameSateManager

\brief
	Game state manager class
*/
/******************************************************************************/
class GameStateManager
{
public:	
	void GSM_Init();
	void GSM_Exit();
	inline void QuitGame() { m_running = false; }
	inline void GSM_NextState(GameState *state) { m_nextState = state; m_changeState = true; }
	inline bool GSM_Running() const { return m_running; }
	inline bool GSM_ChangeState() const { return m_changeState; }

	void StateUpdate();
	void StateDraw();
	
	void ChangeState();
	void ResetState();
	void PauseState(GameState *subState);
	void UnPauseState();

private:
	std::vector<GameState *>m_gameStates;	//!< pointers to the states which are active
	
	GameState *m_currState;	//!< current state of the game
	GameState *m_nextState;	//!< next state to be loaded
	
	bool m_running;		 //!< checks if the game is still running
	bool m_paused;		 //!< checks if the game was paused
	bool m_changeState;	 //!< checks if the next state should be loaded

public:
	GameState* GetCurrState() {return m_currState;}
};

#endif