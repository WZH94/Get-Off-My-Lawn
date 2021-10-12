/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_Credits.h
\author		Tan Zhi Quan, zhiquan.tan (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Shop
gamestate.
Functions include:
GameStateCreditsLoad
GameStateCreditsInit
GameStateCreditsUpdate
GameStateCreditsDraw
GameStateCreditsFree
GameStateCreditsUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_CREDITS_H
#define GAMESTATE_CREDITS_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateCreditsLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateCreditsInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateCreditsUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateCreditsDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateCreditsFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateCreditsUnload(void);

#endif GAMESTATE_CREDITS_H