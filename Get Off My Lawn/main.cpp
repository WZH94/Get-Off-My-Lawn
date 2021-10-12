/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   main.cpp
\author Ngm Hui Min, Lois					(25%)| Wong Zhihao(25%)
		Tan Zhi Quan						(25%)| Sng Zhi Ren Zachary (25%)
\par    email: lois.ngm\@digipen.edu		| zhihao.wong\@digipen.edu
			   zhiquan.tan\@digipen.edu		| z.sng\@digipen.edu
\par    DigiPen login: lois.ngm				| zhihao.wong
					   zhiquan.tan			| z.sng
\par    Course: GAM150
\date	13/04/18
\brief
main folder for game loop

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "main.h"				// System stuff
#include "GameStateList.h"		// Game state enums
#include "SystemComponents.h"	// Components
#include "LogicComponents.h"	// Components
#include "resource.h"

// ---------------------------------------------------------------------------
// Globals

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(prevInstanceH);

	// Check for memery leaks
	#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// Seeks out memory leak locations
	//_CrtSetBreakAlloc(3841);
	#endif

	// Initialises all system components
	System_Initialise(instanceH, show);

	// Adds every game state in the game and initialises Game State Manager
	GameStateManager_Initialise();

	// Game State Loop
	while (gAEGameStateCurr != AE_GS_QUIT && AESysDoesWindowExist())
	{
		if (gAEGameStateCurr == AE_GS_RESTART)
		{
			gAEGameStateCurr = gAEGameStatePrev;
			gAEGameStateNext = gAEGameStatePrev;
		}

		else
		{
			AEGameStateMgrUpdate();
			AEGameStateLoad();
		}

		AEGameStateInit();
		system_components.framerate_manager->Set_New_State_Start_Time();

		// Game Loop
		while (gAEGameStateCurr == gAEGameStateNext && AESysDoesWindowExist())
		{
			AESysFrameStart();
			AEInputUpdate();
			system_components.cursor_position_->Set_Cursor_Position();
			AEGameStateUpdate();
			AEGameStateDraw();
			AESysFrameEnd();

			system_components.framerate_manager->Update_Framerate_Manager();
			system_components.audio_manager->Update_FMOD();

			// Pause state loop
			while (gAEGameStateCurr == GS_PAUSE)
			{
				logic_components.pause_state_manager->Pause_State_Load();
				logic_components.pause_state_manager->Set_Current_State();

				// Pause loop
				while (logic_components.pause_state_manager->Check_Current_State())
				{
					AESysFrameStart();
					AEInputUpdate();
					AEGameStateDraw();

					system_components.cursor_position_->Set_Cursor_Position();
					logic_components.pause_state_manager->Pause_State_Update();
					logic_components.pause_state_manager->Pause_State_Draw();
					AESysFrameEnd();

					system_components.audio_manager->Update_FMOD();
				}

				logic_components.pause_state_manager->Pause_State_Unload();
			}
		}

		AEGameStateFree();

		if (gAEGameStateNext != AE_GS_RESTART)
			AEGameStateUnload();

		  gAEGameStatePrev = gAEGameStateCurr;
		  gAEGameStateCurr = gAEGameStateNext;
	}

	System_Exit();
}

