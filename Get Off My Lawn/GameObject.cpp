/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   GameObject.cpp
\author Wong Zhihao			(33%)| Ngm Hui Min, Lois (33%)| Tan Zhi Quan (33%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong | lois.ngm | zhiquan.tan
\par    Course: GAM150
\date
\brief
	This file contains the implementation of the GameObject class.

	Copyright (C) 2018 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of DigiPen Institute of Technology is prohibited.
	All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "GameObject.h"			// Class and function declarations5
#include "RenderManager.h"		// Render Object
#include "SystemComponents.h"	// Graphics List
#include "LogicComponents.h"
#include "LevelData.h"			// Enemy base location
#include "Input.h"
#include "Button.h"
#include "Players.h"

// Default Constructor
GameObject::GameObject()
// members initialization list
	:
	texture_{nullptr},
	renderMesh_{nullptr},
	collisionMesh_{nullptr},
	ID_{0},
	texture_change_{0.0f},
	texture_timer_{0.0f},
	texture_width_{0.0f},
	texture_start_{0.0f},
	alive_{true}
{
	pos_.x = 0;
	pos_.y = 0;
}

// Constructor for objects
GameObject::GameObject(SIDES side, float x, float y, float scale_x, float scale_y, OBJECT_TYPES object_type, UNIT_TYPES unit_type, f32 angle)
	:
	side_{side},
	scale_x{scale_x},
	scale_y{ scale_y},
	radius_{scale_x / 2},
	object_type_{object_type},
	unit_type_{unit_type},
	pos_{x, y},
	texture_{ system_components.graphics_manager_->Get_Texture(unit_type) },
	renderMesh_{ system_components.graphics_manager_->Get_Render_Mesh(unit_type) },
	collisionMesh_{ system_components.graphics_manager_->Get_Collision_Mesh(unit_type) },
	angle_{angle},

	speed_check_flag_{0},
	alive_{true}
{
	// Only soldiers will have animation
	if (object_type == SOLDIER)
	{
		texture_change_ = 0.125f;
		texture_timer_ = 0.05f;
		texture_width_ = 0.125f;
	}

	else
	{
		texture_change_ = 0;
		texture_timer_ = 0;
		texture_width_ = 0;
	}

	// Set enemy kids spawn location based on enemy base location. Currently hard-coded
	if (side_ == KIDS && object_type_ == SOLDIER)
	{
		pos_.x = logic_components.level_data->Get_Enemy_Base_Location().x + logic_components.level_data->Get_Kids_Spawn_Modifier().x;
		pos_.y = logic_components.level_data->Get_Enemy_Base_Location().y + logic_components.level_data->Get_Kids_Spawn_Modifier().y;
	}

	// Set granny kids spawn location based on granny base location. Currently hard-coded
	else if (side_ == GRANDMA && object_type_ == SOLDIER)
	{
		pos_.x = 0 + logic_components.level_data->Get_Grandma_Spawn_Modifier().x;
		pos_.y = 0 + logic_components.level_data->Get_Grandma_Spawn_Modifier().y;
	}
}

// Default Destructor
GameObject::~GameObject()
{

}

void GameObject::Update()
{
	if (Get_Unit_Type() == WAVE_FILLER)
	{
		if (!logic_components.level_data->Get_Wave_In_Progress() && logic_components.level_data->Get_Current_Timer() - logic_components.level_data->Get_Update_Timer() >= 1.0f)
		{
			if (Get_Scale_X() < 1082.8125f)
			{
				Set_Scale_X(Get_Scale_X() + 1082.8125f / logic_components.level_data->Get_Max_Waves() / ((system_components.framerate_manager->Get_Time_Multiplier() == 1) ? 60.0f : 30.0f));
				Set_x(1082.8125f / logic_components.level_data->Get_Max_Waves() / ((system_components.framerate_manager->Get_Time_Multiplier() == 1) ? 120.0f : 60.0f));
				logic_components.level_data->Set_Update_Timer(logic_components.level_data->Get_Current_Timer());
			}

			else
			{
				Set_Scale_X(1082.8125f);
				Set_x(0);
			}
		}
	}
	if(Get_Object_Type() == TYPE_CURSOR)
	{
		Set_x_pos(system_components.cursor_position_->Get_Cursor_Position().x + scale_x/2.0f);
		Set_y_pos(system_components.cursor_position_->Get_Cursor_Position().y - scale_y/2.0f);
	}
	if (Get_Unit_Type() == HEALTH)
	{
		if (side_ == GRANDMA)
		{
			if (logic_components.level_data->players->Get_Grandma_Base_HP() >= 10 &&
				logic_components.level_data->players->Get_Grandma_Base_HP() <= 17)
				texture_change_ = 0.25f;
			else if (logic_components.level_data->players->Get_Grandma_Base_HP() >= 1 &&
				logic_components.level_data->players->Get_Grandma_Base_HP() <= 10)
				texture_change_ = 0.5f;
			else if (logic_components.level_data->players->Get_Grandma_Base_HP() <= 0)
				texture_change_ = 0.75f;
		}
		else if (side_ == KIDS)
		{

			if (logic_components.level_data->players->Get_Kid_Base_HP() >= 10 &&
				logic_components.level_data->players->Get_Kid_Base_HP() <= 17)
				texture_change_ = 0.25f;
			else if (logic_components.level_data->players->Get_Kid_Base_HP() >= 1 &&
				logic_components.level_data->players->Get_Kid_Base_HP() <= 10)
				texture_change_ = 0.5f;
			else if (logic_components.level_data->players->Get_Kid_Base_HP() <= 0)
				texture_change_ = 0.75f;
		}
	}
}

void GameObject::Draw()
{
	if(alive_)
		Render_Object(*this);
}

///////////////////////
// Getters and Setters

// Gets the mesh of the object
AEGfxVertexList * GameObject::Get_Render_Mesh() const
{
	return renderMesh_;
}
// Sets the mesh of the object
void GameObject::Set_Collision_Mesh(AEGfxVertexList * Mesh)
{
	collisionMesh_ = Mesh;
}

// Gets the mesh of the object
AEGfxVertexList * GameObject::Get_Collision_Mesh() const
{
	return collisionMesh_;
}
// Sets the mesh of the object
void GameObject::Set_Render_Mesh(AEGfxVertexList * Mesh)
{
	renderMesh_ = Mesh;
}

// Gets the texture of the object
AEGfxTexture * GameObject::Get_Texture() const
{
	return texture_;
}

// Sets the texture of the object
void GameObject::Set_Texture(AEGfxTexture * Texture)
{
	texture_ = Texture;
}

// Gets position of the game object
AEVec2 GameObject::Get_Pos() const
{
	return pos_;
}

// Sets position of the game object
void GameObject::Set_Pos(AEVec2 position)
{
	pos_ = position;
}

// Gets the object's transformation matrix
AEMtx33 GameObject::Get_Matrix() const
{
	return matrix_;
}

// Sets the object's transformation matrix
void GameObject::Set_Matrix()
{
	AEMtx33 trans, scale, rot;

	// Check if object is not a button
	if (object_type_ != BUTTONS && object_type_ != TYPE_BLACK_SCREEN_FADE && object_type_ != TYPE_BLACK_SCREEN_TINT && object_type_ != DESCRIPTION && object_type_ != GENERAL && object_type_ != TYPE_CURSOR)
	{
		// Gets the camera zoom to scale objects by
		float camera_zoom = logic_components.camera->Get_Zoom();
		AEMtx33RotDeg(&rot, angle_);
		// Scale object with the camera zoom amount
		AEMtx33Scale(&scale, scale_x * camera_zoom, scale_y * camera_zoom);
		// Translate based on camera zoom amount
		AEMtx33Trans(&trans, pos_.x * camera_zoom, pos_.y * camera_zoom);
	}

	// Object is a button
	else
	{
		AEMtx33RotDeg(&rot, angle_);
		// Never scale it with camera zoom
		AEMtx33Scale(&scale, scale_x, scale_y);
		// Translates it so it always follows the camera
		AEMtx33Trans(&trans, pos_.x + logic_components.camera->Get_Camera_UI_Position().x, pos_.y + logic_components.camera->Get_Camera_UI_Position().y);
	}

	// Sets the object's transformation matrix
	AEMtx33Concat(&scale, &scale, &rot);
	AEMtx33Concat(&matrix_, &trans, &scale);
}

// Gets the x coordinate of the object
float GameObject::Get_x() const
{
	return pos_.x;
}

// Sets the x coordinate of the object
void GameObject::Set_x(float x_pos)
{
	pos_.x += x_pos;
}

void GameObject::Set_x_pos(float x_pos)
{
	pos_.x = x_pos;
}

void GameObject::Set_y_pos(float y_pos)
{
	pos_.y = y_pos;
}


// Gets the y coordinate of the object
float GameObject::Get_y() const
{
	return pos_.y;
}

// Sets the y coordinate of the object
void GameObject::Set_y(float y_pos)
{
	pos_.y += y_pos;
}

// Gets the ID of the object
long long GameObject::Get_ID() const
{
	return ID_;
}

// Sets the ID of the object
void GameObject::Set_ID(long long id)
{
	ID_ = id;
}

// Gets the type of the object
OBJECT_TYPES GameObject::Get_Object_Type() const
{
	return object_type_;
}

// Gets the enum type of the object
UNIT_TYPES GameObject::Get_Unit_Type() const
{
	return unit_type_;
}

// Gets the side of the object 
SIDES GameObject::Get_Side() const
{
	return side_;
}

// Gets the scale of the object
float GameObject::Get_Scale_X() const
{
	return scale_x;
}

// Gets the scale of the object
void GameObject::Set_Scale_X(float scale)
{
	scale_x = scale;
}

// Gets the scale of the object
float GameObject::Get_Scale_Y() const
{
	return scale_y;
}

// Gets the scale of the object
void GameObject::Set_Scale_Y(float scale)
{
	scale_y = scale;
}

// Gets the radius of the object, half of scale
float GameObject::Get_Radius() const
{
	return radius_;
}

// Sets the radius of the object, half of scale
void GameObject::Set_Radius(float Radius)
{
	radius_ = Radius;
}


bool GameObject::Get_Speed_Check_Flag() const
{
	return speed_check_flag_;
}

void GameObject::Set_Speed_Check_Flag(bool flag)
{
	speed_check_flag_ = flag;
}

float GameObject::Get_Texture_Change() const
{
	return texture_change_;
}
void GameObject::Set_Texture_Change(float change)
{
	texture_change_ = change;
}

float GameObject::Get_Texture_Timer() const
{
	return texture_timer_;
}
void GameObject::Set_Texture_Timer(float timer)
{
	texture_timer_ = timer;
}


float GameObject::Get_Texture_Width() const
{
	return texture_width_;
}
void GameObject::Set_Texture_Width(float width)
{
	texture_width_ = width;
}

bool GameObject::Get_Alive() const
{
	return alive_;
}

void GameObject::Set_Alive(bool living)
{
	if (alive_ == living)
		return;
	alive_ = living;
}

void GameObject::Set_Angle(f32 angle)
{
	angle_ = angle;
}


void GameObject::Set_Start_Texture(float start)
{
	texture_change_ = start;
	texture_start_ = start;
}
float GameObject::Get_Start_Texture()
{
	return texture_start_;
}