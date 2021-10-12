/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   GameStateList.h
\author Wong Zhihao			(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18	
\brief
This file contains the enum of game states of Get off my Lawn.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef GAMESTATELIST_H
#define GAMESTATELIST_H

enum GS_STATES
{
	// Level enums
	GS_LEVEL_0 = 0,
	GS_LEVEL_1,
	GS_LEVEL_2, 
	GS_LEVEL_3,
	GS_LEVEL_4,
	GS_LEVEL_5,
	GS_LEVEL_6,
	GS_LEVEL_7,
	GS_LEVEL_8,
	GS_LEVEL_9,
	GS_LEVEL_10,

	// Main menu and UI states
	GS_MAINMENU,
	GS_LOADPLAYER,
	GS_LEVELSELECT,
	GS_SHOP,
	GS_GAMEOVER,
	GS_VICTORY,
	GS_OPTIONS,
	GS_CREDITS,
	GS_DIGIPENLOGO,
	GS_TEAMLOGO,
	GS_CHANGE_LEVEL,

	// Pause enum to break into a seperate pause state loop
	GS_PAUSE
};
#endif GAMESTATELIST_H