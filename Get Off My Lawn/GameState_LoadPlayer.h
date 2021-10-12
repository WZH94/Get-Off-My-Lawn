/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_LoadPlayer.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Load Player
gamestate.
Functions include:
GameStateLoadPlayerLoad
GameStateLoadPlayerInit
GameStateLoadPlayerUpdate
GameStateLoadPlayerDraw
GameStateLoadPlayerFree
GameStateLoadPlayerUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_LOADPLAYER_H
#define GAMESTATE_LOADPLAYER_H


/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerUnload(void);

#endif GAMESTATE_LOADPLAYER_H