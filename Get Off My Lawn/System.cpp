/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   System.cpp
\author Ngm Hui Min, Lois			(25%) | Wong Zhihao (25%)
		Tan Zhi Quan				(25%) | Zachary Sng Zhi Ren (25%)
\par    email: lois.ngm\@digipen.edu	  | zhihao.wong\@digipen.edu
				zhiquan.tan\@digipen.edu	| z.sng\@digipen.edu
\par    DigiPen login: lois.ngm				| zhihao.wong
						zhiquan.tan			| z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file handles system functions and system initialisations

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

// Include components
#include "SystemComponents.h"
#include "LogicComponents.h"
#include "resource.h"

System_Components system_components;
Logic_Components logic_components;

/******************************************************************************/
/*!
	Initialises the system
*/
/******************************************************************************/
void System_Initialise(HINSTANCE instanceH, int show)
{
	// Initialises Alpha Engine Graphics, Frame Rate and Input managers
	AESysInit(instanceH, show, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 60, NULL);

	AESysSetWindowTitle("Get off my Lawn!");

	AEToogleFullScreen(full_screen);

	AEGfxSetBackgroundColor(0, 0, 0);

	// Initialise and load the components
	system_components.Load_System_Components();
	logic_components.Initialise_Logic_Components();
}

/******************************************************************************/
/*!
	Exit and unloads all the components and Alpha Engine system
*/
/******************************************************************************/
void System_Exit()
{
	system_components.Unload_System_Components();
	logic_components.Free_Logic_Components();

	AESysExit();
}