/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_TeamLogo.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Team Logo
gamestate.
Functions include:
GameStateTeamLogoLoad
GameStateTeamLogoInit
GameStateTeamLogoUpdate
GameStateTeamLogoDraw
GameStateTeamLogoFree
GameStateTeamLogoUnload


Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_TEAMLOGO_H
#define GAMESTATE_TEAMLOGO_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoUnload(void);

#endif GAMESTATE_TEAMLOGO_H