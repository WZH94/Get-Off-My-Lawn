/******************************************************************************/
/*!
\game Get Off My Lawn!
\file   Input.h
\author Ngm Hui Min, Lois		(90%)			| Tan Zhi Quan (10%)
\par    email: lois.ngm\@digipen.edu			| zhiquan.tan\@digipen.edu
\par    DigiPen login: lois.ngm					| zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file handles all input in the game

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef INPUT_H
#define INPUT_H

typedef class Button Button;

void Input_Handle_Granny_Tower_Nodes();

bool Input_Handle_Granny_Tower_Nodes(char tutorial);

void Input_Handle_Main_Menu();

void Input_Handle_Level_Selection();

bool Tutorial_G_S_Shooter();

bool Tutorial_G_T_Shooting();

void Input_Handle_Tutorial();

void Input_Handle_Load_Player();

void Input_Handle_Options();

void Input_Handle_Shop();

void Input_Handle_Credits();

void Input_Handle_Soldiers();

void Input_Handle_In_Game();

void Input_Handle_In_Game_Buttons();

void Input_Handle_Granny_Mojo();

bool Cursor_Box_Collision_Camera(Button* button);

bool Cursor_Box_Collision (Button *button);

void Input_Handle_In_Game_Commands();

#endif INPUT_H