/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   System.h
\author Ngm Hui Min, Lois			(25%) | Wong Zhihao (25%)
		Tan Zhi Quan				(25%) | Zachary Sng Zhi Ren (25%)
\par    email: lois.ngm\@digipen.edu	  | zhihao.wong\@digipen.edu
				zhiquan.tan\@digipen.edu	| z.sng\@digipen.edu
\par    DigiPen login: lois.ngm				| zhihao.wong
						zhiquan.tan			| z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of system functions and system initialisations

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "AEEngine.h"	// Alpha Engine

// Initialises the system
void System_Initialise(HINSTANCE instanceH, int show);

// Exit and unloads all the components and Alpha Engine system
void System_Exit();

#endif SYSTEM_H