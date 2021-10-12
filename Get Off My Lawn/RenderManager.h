/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   RenderManager.h
\author Wong Zhihao			(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of Rendering functions to render
things out into the game.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "AEEngine.h"	// Alpha engine 
#include "Font.h"		// Font types

// Forward declarations
typedef class GameObject GameObject;
typedef class Soldier Soldier;
typedef class Particle Particle;
typedef class Tower Tower;

// Renders a given object in the game. Called during Game State Draw
void Render_Object(GameObject &object);

// Renders particles in the game
void Render_Particle(Particle & particle);

// Renders particles in the game without fading
void Render_Particle_Without_Fade(Particle & particle);

// Prints text in game
void Print_Text(u32 fontID, char strBuffer[], s32 x, s32 y, f32 red = 1.0f, f32 green = 1.0f, f32 blue = 1.0f);

// Animates soldiers by changing their texture
void Animate_Soldier(Soldier & soldier);

// Animates towers by changing their texture
void Animate_Tower(Tower & tower);

#endif RENDERMANAGER_H