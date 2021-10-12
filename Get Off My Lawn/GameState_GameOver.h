/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_GameOver.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the GameOver
gamestate.
Functions include:
GameStateGameOverLoad
GameStateGameOverInit
GameStateGameOverUpdate
GameStateGameOverDraw
GameStateGameOverFree
GameStateGameOverUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_GAMEOVER_H
#define GAMESTATE_GAMEOVER_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateGameOverLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateGameOverInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateGameOverUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateGameOverDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateGameOverFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateGameOverUnload(void);

#endif GAMESTATE_GAMEOVER_H