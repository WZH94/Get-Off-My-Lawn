/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   GameObject.h
\author Wong Zhihao			(33%)| Ngm Hui Min, Lois (33%)| Tan Zhi Quan (33%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong | lois.ngm | zhiquan.tan
\par    Course: GAM150
\date
\brief
This file contains the declaration of the GameObject class and the enums for
both object types and the sides they are on

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "AEEngine.h"

// Forward declaration
typedef enum UNIT_TYPES UNIT_TYPES;

// Which side the game object is on
enum SIDES
{
	GRANDMA = 0,
	KIDS,
	NONE
};

// All the types of objects there ares
enum OBJECT_TYPES
{
	/////////////////////
	// Spawnable types 

	// Created within Init() or Update()
	SOLDIER = 0,
	TOWER,
	PROJECTILE,
	PARTICLE,
	PARTICLE_EMITTER,

	/////////////////////////////////
	// Environmentals, nodes and UI

	// Created within Load()
	BASE,
	GENERAL,
	SCALABLE_GENERAL,
	BUTTONS,
	TOWER_NODES,
	PATH, 
	BACKGROUND,
	DESCRIPTION, 
	SCALABLE_DESCRIPTION,
	SCALABLE_BUTTON,


	TYPE_BLACK_SCREEN_FADE,
	TYPE_BLACK_SCREEN_TINT,

	TYPE_CURSOR
};

class GameObject
{
protected:
	AEGfxTexture * texture_;			// Texture of the object
	AEGfxVertexList * renderMesh_;		// Mesh of the object
	AEGfxVertexList * collisionMesh_;	// Mesh of the object
	AEVec2 pos_;						// Coordinates of the object
	AEMtx33 matrix_;					// Transformation matrix

	float scale_x;						// The scale of the object (x)
	float scale_y;						// The scale of the object (y)
	float radius_;						// The radius of the object, half of scale
	bool speed_check_flag_;				// Controls the x and y speed

	SIDES side_;						// Grandma or Kid?
	OBJECT_TYPES object_type_;			// Soldier, Tower, Base, Projectile, Button?
	UNIT_TYPES unit_type_;				// What unit it is, taken from enum in ObjectList.h
	long long ID_;						// ID of the object inside the Object List
	float texture_change_;				// width to change the animation
	float texture_timer_;				// time to change the timer
	float texture_width_;				// the width of the image
	float texture_start_;				// the first image to start the texture with
	f32 angle_;

	bool alive_;
public:
	GameObject();

	GameObject(
		// GameObject variables
		SIDES side,					// Grandma or Kid?
		float x, float y,			// Spawn position
		float scale_x,				// Scale of the unit (x)
		float scale_y,				// Scale of the unit (y)
		OBJECT_TYPES object_type,	// What kind of object it is
		UNIT_TYPES unit_type,		// What type of unit it is
		f32 angle_ = 0.0f
	);

	virtual ~GameObject();

	virtual void Update();
	virtual void Draw();

	// Gets the texture mesh of the object
	AEGfxVertexList * Get_Render_Mesh() const;
	// Sets the texture mesh of the object
	void Set_Render_Mesh(AEGfxVertexList * Mesh);

	// Gets the collision mesh of the object
	AEGfxVertexList * Get_Collision_Mesh() const;
	// Sets the collision mesh of the object
	void Set_Collision_Mesh(AEGfxVertexList * Mesh);

	// Gets the texture of the object
	AEGfxTexture * Get_Texture() const;
	// Sets the texture of the object
	void Set_Texture(AEGfxTexture * Texture);

	// Gets position of the game object
	AEVec2 Get_Pos() const;
	// Sets position of the game object
	void Set_Pos(AEVec2 position);

	// Gets the object's transformation matrix
	AEMtx33 Get_Matrix() const;
	// Sets the object's transformation matrix
	void Set_Matrix();

	// Gets the x coordinate of the object
	float Get_x() const;
	// Sets the x coordinate of the object
	void Set_x(float x_pos);
	void Set_x_pos(float x_pos);

	// Gets the y coordinate of the object
	float Get_y() const;
	// Sets the y coordinate of the object
	void Set_y(float y_pos);
	void Set_y_pos(float y_pos);

	// Gets the ID of the object
	long long Get_ID() const;
	// Sets the ID of the object
	void Set_ID(long long id);

	// Gets the type of the object
	OBJECT_TYPES Get_Object_Type() const;

	// Gets the enum type of the object
	UNIT_TYPES Get_Unit_Type() const;

	// Gets the side of the object 
	SIDES Get_Side() const;

	// Gets the scale of the object
	float Get_Scale_X() const;

	// Sets the scale of the object
	void Set_Scale_X(float);

	// Gets the scale of the object
	float Get_Scale_Y() const;

	// Sets the scale of the object
	void Set_Scale_Y(float);

	// Gets the radius of the object, half of scale
	float Get_Radius() const;
	// Sets the radius of the object, half of scale
	void Set_Radius(float);

	bool Get_Speed_Check_Flag() const;
	void Set_Speed_Check_Flag(bool flag);

	void Set_Angle(f32 angle);

	// for animation
	float Get_Texture_Change()const;
	void Set_Texture_Change(float change);
	float Get_Texture_Timer()const;
	void Set_Texture_Timer(float timer);
	float Get_Texture_Width()const;
	void Set_Texture_Width(float timer);
	void Set_Start_Texture(float start);
	float Get_Start_Texture();

	bool Get_Alive() const;
	// Set transparency change. Return true if object has finished fading, else return false
	void Set_Alive(bool living);
};

#endif GAMEOBJECT_H