/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   PauseState_Menu.h
\author Wong Zhihao						(50%)| Ngm Hui Min, Lois(50%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu
\par    DigiPen login: zhihao.wong		| lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to show the pause menu when pause is clicked
or when pause is invoked by keyboard shortcuts

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef PAUSESTATEMENU_H
#define PAUSESTATEMENU_H

// Load Graphics for pause menu
void PauseStateMenu_Load();

// update pause menu
void PauseStateMenu_Update();

// draw pause menu
void PauseStateMenu_Draw();

#endif