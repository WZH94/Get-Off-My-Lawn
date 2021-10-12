/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_LevelSelect.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Shop
gamestate.
Functions include:
GameStateShopLoad
GameStateShopInit
GameStateShopUpdate
GameStateShopDraw
GameStateShopFree
GameStateShopUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_SHOP_H
#define GAMESTATE_SHOP_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateShopLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateShopInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateShopUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateShopDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateShopFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateShopUnload(void);

#endif GAMESTATE_SHOP_H