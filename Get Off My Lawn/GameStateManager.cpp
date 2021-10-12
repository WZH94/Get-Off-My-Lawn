/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   GameStateManager.cpp
\author Wong Zhihao				(50%)| Tan Zhi Quan (50%)
\par    email: zhihao.wong\@digipen.edu | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong | zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the functions to handle the Game State Manager

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
								   
#include "GameStateManager.h"	   // Function declarations
#include "GameStateList.h"		   // List of game state enums
#include "Level1.h"				   // Level 1 functions
#include "Level0.h"				   // Level 0 functions
#include "Level2.h"                // Level 2 functions
#include "Level3.h"                // Level 3 functions
#include "Level4.h"                // Level 4 functions
#include "Level5.h"                // Level 5 functions
#include "Level6.h"                // Level 6 functions
#include "Level7.h"                // Level 7 functions
#include "Level8.h"                // Level 8 functions
#include "Level9.h"                // Level 9 functions
#include "Level10.h"               // Level 10 functions
#include "GameState_MainMenu.h"    // Main Menu functions
#include "GameState_GameOver.h"    // Game Over functions
#include "GameState_Victory.h"     // Victory functions
#include "GameState_LevelSelect.h" // Level Select functions
#include "GameState_LoadPlayer.h"  // Load Player functions
#include "GameState_Shop.h"		   // Shop functions
#include "GameState_Credits.h"	   // Credits functions
#include "GameState_Options.h"	   // Options functions
#include "GameState_DigipenLogo.h" // Digipen Logo functions
#include "GameState_TeamLogo.h"	   // Team Logo functions
#include "AEEngine.h"			   // Alpha Engine game state manager

void GameStateManager_Initialise()
{
	// Adds all the game states to the Game State Manager before initialising it
	AEGameStateMgrAdd(GS_LEVEL_0, Level0_Load, Level0_Init, Level0_Update, Level0_Draw, Level0_Free, Level0_Unload);
	
	AEGameStateMgrAdd(GS_LEVEL_1, Level1_Load, Level1_Init, Level1_Update, Level1_Draw, Level1_Free, Level1_Unload);

	AEGameStateMgrAdd(GS_LEVEL_2, Level2_Load, Level2_Init, Level2_Update, Level2_Draw, Level2_Free, Level2_Unload);

	AEGameStateMgrAdd(GS_LEVEL_3, Level3_Load, Level3_Init, Level3_Update, Level3_Draw, Level3_Free, Level3_Unload);
	
	AEGameStateMgrAdd(GS_LEVEL_4, Level4_Load, Level4_Init, Level4_Update, Level4_Draw, Level4_Free, Level4_Unload);
	
	AEGameStateMgrAdd(GS_LEVEL_5, Level5_Load, Level5_Init, Level5_Update, Level5_Draw, Level5_Free, Level5_Unload);

	AEGameStateMgrAdd(GS_LEVEL_6, Level6_Load, Level6_Init, Level6_Update, Level6_Draw, Level6_Free, Level6_Unload);

	AEGameStateMgrAdd(GS_LEVEL_7, Level7_Load, Level7_Init, Level7_Update, Level7_Draw, Level7_Free, Level7_Unload);

	AEGameStateMgrAdd(GS_LEVEL_8, Level8_Load, Level8_Init, Level8_Update, Level8_Draw, Level8_Free, Level8_Unload);

	AEGameStateMgrAdd(GS_LEVEL_9, Level9_Load, Level9_Init, Level9_Update, Level9_Draw, Level9_Free, Level9_Unload);

	AEGameStateMgrAdd(GS_LEVEL_10, Level10_Load, Level10_Init, Level10_Update, Level10_Draw, Level10_Free, Level10_Unload);

	AEGameStateMgrAdd(GS_MAINMENU, GameStateMainMenuLoad, GameStateMainMenuInit, GameStateMainMenuUpdate, GameStateMainMenuDraw, GameStateMainMenuFree, GameStateMainMenuUnload);

	AEGameStateMgrAdd(GS_LEVELSELECT, GameStateLevelSelectLoad, GameStateLevelSelectInit, GameStateLevelSelectUpdate, GameStateLevelSelectDraw, GameStateLevelSelectFree, GameStateLevelSelectUnload);

	AEGameStateMgrAdd(GS_LOADPLAYER, GameStateLoadPlayerLoad, GameStateLoadPlayerInit, GameStateLoadPlayerUpdate, GameStateLoadPlayerDraw, GameStateLoadPlayerFree, GameStateLoadPlayerUnload);

	AEGameStateMgrAdd(GS_SHOP, GameStateShopLoad, GameStateShopInit, GameStateShopUpdate, GameStateShopDraw, GameStateShopFree, GameStateShopUnload);

	AEGameStateMgrAdd(GS_CREDITS, GameStateCreditsLoad, GameStateCreditsInit, GameStateCreditsUpdate, GameStateCreditsDraw, GameStateCreditsFree, GameStateCreditsUnload);

	AEGameStateMgrAdd(GS_OPTIONS, GameStateOptionsLoad, GameStateOptionsInit, GameStateOptionsUpdate, GameStateOptionsDraw, GameStateOptionsFree, GameStateOptionsUnload);

	AEGameStateMgrAdd(GS_GAMEOVER, GameStateGameOverLoad, GameStateGameOverInit, GameStateGameOverUpdate, GameStateGameOverDraw, GameStateGameOverFree, GameStateGameOverUnload);
	
	AEGameStateMgrAdd(GS_VICTORY, GameStateVictoryLoad, GameStateVictoryInit, GameStateVictoryUpdate, GameStateVictoryDraw, GameStateVictoryFree, GameStateVictoryUnload);
	
	AEGameStateMgrAdd(GS_DIGIPENLOGO, GameStateDigipenLogoLoad, GameStateDigipenLogoInit, GameStateDigipenLogoUpdate, GameStateDigipenLogoDraw, GameStateDigipenLogoFree, GameStateDigipenLogoUnload);

	AEGameStateMgrAdd(GS_TEAMLOGO, GameStateTeamLogoLoad, GameStateTeamLogoInit, GameStateTeamLogoUpdate, GameStateTeamLogoDraw, GameStateTeamLogoFree, GameStateTeamLogoUnload);
	// Initialises Game State Manager with the first game state to load up
	AEGameStateMgrInit(GS_DIGIPENLOGO);

}