/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_Options.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Options
gamestate.
Functions include:
GameStateOptionsLoad
GameStateOptionsInit
GameStateOptionsUpdate
GameStateOptionsDraw
GameStateOptionsFree
GameStateOptionsUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_OPTIONS_H
#define GAMESTATE_OPTIONS_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateOptionsLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateOptionsInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateOptionsUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateOptionsDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateOptionsFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateOptionsUnload(void);

#endif GAMESTATE_OPTIONS_H