/* Start Header **************************************************************/
/*!
\file		Level0.h
\author		Tan Zhi Quan, zhiquan.tan (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the level 0
gamestate.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header ****************************************************************/

#ifndef LEVEL0_H
#define LEVEL0_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void Level0_Load();

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void Level0_Init();

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void Level0_Update();

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void Level0_Draw();

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void Level0_Free();

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void Level0_Unload();

/******************************************************************************/
/*!
Tutorial handler
*/
/******************************************************************************/
void Tutorial(int stage);

#endif LEVEL0_H