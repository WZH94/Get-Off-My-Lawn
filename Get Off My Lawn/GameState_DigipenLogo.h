/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_DigipenLogo.h
\author		Tan Zhi Quan, zhiquan.tan (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Digipen Logo
gamestate.
Functions include:
GameStateDigipenLogoLoad
GameStateDigipenLogoInit
GameStateDigipenLogoUpdate
GameStateDigipenLogoDraw
GameStateDigipenLogoFree
GameStateDigipenLogoUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_DIGIPENLOGO_H
#define GAMESTATE_DIGIPENLOGO_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateDigipenLogoLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateDigipenLogoInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateDigipenLogoUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateDigipenLogoDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateDigipenLogoFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateDigipenLogoUnload(void);

#endif GAMESTATE_DIGIPENLOGO_H