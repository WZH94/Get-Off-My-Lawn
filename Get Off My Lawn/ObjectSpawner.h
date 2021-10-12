/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   ObjectSpawner.h
\author Wong Zhihao (80%)| Ngm Hui Min, Lois (10%)| Sng Zhi Ren Zachary(10%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | lois.ngm | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of functions that handle object spawning

Functions include:
Spawn_Object
Spawn_Projectile

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef OBJECTSPAWNER_H
#define OBJECTSPAWNER_H

#include "AEVec2.h"

// Forward declarations
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class GameObject GameObject;
typedef enum Orientation Orientation;
typedef enum EMITTER_SOURCE_TYPE EMITTER_SOURCE_TYPE;
typedef class ParticleEmitter ParticleEmitter;

// Spawns object based on the type inputted
void Spawn_Object(UNIT_TYPES type, float x, float y);

// Spawns object based on the type inputted
void Spawn_Projectile(UNIT_TYPES type, float x, float y, int damage, GameObject & target);

// Spawns Particle Emitter
void Spawn_Particle_Emitter(float x, float y, UNIT_TYPES particletype, float range, float lifetime);

// Creates the paths that soldiers will travel on in a level
void Create_Path(Orientation orientation, UNIT_TYPES type);

// Create Wave indicator
void Create_Wave_Indicator(const int max_waves);

#endif OBJECTSPAWNER_H