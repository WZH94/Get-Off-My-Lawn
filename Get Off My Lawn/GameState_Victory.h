/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_Victory.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Victory
gamestate.
Functions include:
GameStateVictoryLoad
GameStateVictoryInit
GameStateVictoryUpdate
GameStateVictoryDraw
GameStateVictoryFree
GameStateVictoryUnload
Spawn_Stars

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_VICTORY_H
#define GAMESTATE_VICTORY_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateVictoryLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateVictoryInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateVictoryUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateVictoryDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateVictoryFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateVictoryUnload(void);

/******************************************************************************/
/*!
Spawns Stars depending on how many were earned in the level
*/
/******************************************************************************/
void Spawn_Stars(int stars_earned);

#endif GAMESTATE_VICTORY_H