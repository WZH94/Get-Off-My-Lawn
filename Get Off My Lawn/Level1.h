/******************************************************************************/
/*!
\file   Level1.h
\author Wong Zhihao				(25%)| Ngm Hui Min, Lois		(25%)
Zachary Sng ZhiRen		(25%)| Tan Zhi Quan				(25%)
\par    email: zhihao.wong\@digipen.edu		| lois.ngm\@digipen.edu
z.sng\@digipen.edu			| zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong			| lois.ngm
z.sng				| zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation for level 1 of Get off my Lawn
Functions include:
Level1_Load
Level1_Init
Level1_Update
Level1_Draw
Level1_Free
Level1_Unload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef LEVEL1_H
#define LEVEL1_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void Level1_Load();

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void Level1_Init();

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void Level1_Update();

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void Level1_Draw();

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void Level1_Free();

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void Level1_Unload();

#endif LEVEL1_H