/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   GraphcisManager.cpp
\author Ngm Hui Min, Lois			(90%)	| Zachary Sng Zhi Ren (10%)
\par    email: lois.ngm\@digipen.edu	| z.sng\@digipen.edu
\par    DigiPen login: lois.ngm			| z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file handles all graphics in the game

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "AEEngine.h"	// Alpha Engine graphics
#include <array>		// Array
#include "ObjectList.h"	// Object enums

// Forward declaration
typedef enum UNIT_TYPES UNIT_TYPES;

// The texture and mesh of a single game object
class GraphicsData
{
protected:
	AEGfxTexture* texture_;				// Pointer to texture of the object prototype
	AEGfxVertexList* render_mesh_;		// Pointer to mesh that the texture renders on of the object prototype
	AEGfxVertexList* collision_mesh_;	// Pointer to collision mesh, unused

public:
	// Constructor for GraphicsData, sets all its variables
	GraphicsData(AEGfxTexture * texture,
		AEGfxVertexList * tex_mesh,
		AEGfxVertexList * col_mesh);

	// Set the graphics of the GraphicsData
	void Set_Graphics(
		AEGfxTexture* texture,
		AEGfxVertexList* tex_mesh,
		AEGfxVertexList* col_mesh);

	// Gets the texture pointer
	AEGfxTexture* Get_Texture() const;

	// Gets the draw mesh pointer
	AEGfxVertexList* Get_Render_Mesh() const;

	// Gets the collision mesh pointer
	AEGfxVertexList* Get_Collision_Mesh() const;
	
	// Free the GraphicsData if its components exist
	void Free_Graphics_Data(bool = true);
};

class Graphics_Manager
{
protected:
	// The textures and meshes of every single game object
	std::array <GraphicsData*, LAST> graphics_list_;

	// All the shared textures in the game
	AEGfxTexture* pTex_granny;
	AEGfxTexture* pTex_kid;
	AEGfxTexture* pTex_button;
	AEGfxTexture* pTex_main_menu_button;
	AEGfxTexture* pTex_level_selection_button;
	AEGfxTexture* pTex_granny_desc;
	AEGfxTexture* pTex_granny_tower;
	AEGfxTexture* pTex_kid_tower;
	AEGfxTexture* pTex_path;
	AEGfxTexture* pTex_wave_flag;

	AEGfxTexture* pTex_button_volume;
	AEGfxTexture* pTex_button_bgm_sfx;
	AEGfxTexture* pTex_button_player_data;
	AEGfxTexture* pTex_button_play_data;
	AEGfxTexture* pTex_general_upgrade_panel;
	AEGfxTexture* pTex_button_upgrade;
	AEGfxTexture* pTex_desc_upgrade;
	AEGfxTexture* pTex_projectile_melee;
	AEGfxTexture* pTex_tutorial_speech;
	AEGfxTexture* pTex_button_tower;
	AEGfxTexture* pTex_desc_tower;
	AEGfxTexture* pTex_button_end_game;
	AEGfxTexture* pTex_button_quit;
	AEGfxTexture* pTex_button_state_pause;
	AEGfxTexture* pTex_button_yn;

public:
	// Graphics Manager constructor, sets all its elements to nullptr
	Graphics_Manager();

	// Gets the texture pointer of the specified object
	AEGfxTexture* Get_Texture(UNIT_TYPES) const;

	// Gets the draw mesh pointer of the specified object
	AEGfxVertexList* Get_Render_Mesh(UNIT_TYPES) const;

	// Gets the collision mesh pointer of the specified object
	AEGfxVertexList* Get_Collision_Mesh(UNIT_TYPES) const;

	// Run this when loading the level and loads every unit used in the level into the graphics list
	void Load_Graphics();

	// Unloads all the textures and meshes loaded when exiting application
	void Unload_Graphics();
};

// Loads a texture and returns a pointer to it
AEGfxTexture * Texture_Load(const char * texture);

// Loads a square/rectangle mesh out of 2 triangles for rendering textures and returns a pointer to it
AEGfxVertexList * Mesh_Load_Square(float length_scale, float height_scale, float texture_width = 1.0f, float texture_height = 1.0f, int index = 0);

// Loads a square/rectangle mesh out of 2 triangles for rendering textures of text boxes and returns a pointer to it
AEGfxVertexList * Mesh_Load_Text_Box(float length_scale, float height_scale, float texture_width, float texture_height, int index);

// Loads the meshes for the particles
AEGfxVertexList * Mesh_Load_Particle(UNIT_TYPES type);

// Loads a circle mesh out of a number of points for collision detection and returns a pointer to it
AEGfxVertexList * Mesh_Load_Circle(float scale, int points = 32);

#endif GRAPHICSMANAGER_H