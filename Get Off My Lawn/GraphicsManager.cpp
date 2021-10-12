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
This file contains the implementation of the Graphics Manager, which holds
the texture and mesh of every object in the game.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "GraphicsManager.h"	// Class and Function declarations
#include "ObjectList.h"			// Object enums

/////////////////////////////////////////
// Graphics Data class member functions

/******************************************************************************/
/*!
	Constructor for GraphicsData, sets all its variables
*/
/******************************************************************************/
GraphicsData::GraphicsData(AEGfxTexture * texture,
	AEGfxVertexList * tex_mesh,
	AEGfxVertexList * col_mesh)
{
	texture_ = texture;
	render_mesh_ = tex_mesh;
	collision_mesh_ = col_mesh;

}

/******************************************************************************/
/*!
	Set the graphics of the GraphicsData
*/
/******************************************************************************/
void GraphicsData::Set_Graphics(
	AEGfxTexture * texture,
	AEGfxVertexList * tex_mesh,
	AEGfxVertexList * col_mesh)
{
	texture_ = texture;
	render_mesh_ = tex_mesh;
	collision_mesh_ = col_mesh;
}

AEGfxTexture * GraphicsData::Get_Texture() const
{
	return texture_;
}

AEGfxVertexList * GraphicsData::Get_Render_Mesh() const
{
	return render_mesh_;
}

AEGfxVertexList * GraphicsData::Get_Collision_Mesh() const
{
	return collision_mesh_;
}

/******************************************************************************/
/*!
	Free the GraphicsData if its components exist
*/
/******************************************************************************/
void GraphicsData::Free_Graphics_Data(bool unload_texture)
{
	if (texture_ && unload_texture == true)
	{
		AEGfxTextureUnload(texture_);
		texture_ = nullptr;
	}


	if (render_mesh_)
	{
		AEGfxMeshFree(render_mesh_);
		render_mesh_ = nullptr;
	}


	if (collision_mesh_)
	{
		AEGfxMeshFree(collision_mesh_);
		collision_mesh_ = nullptr;
	}
}

///////////////////////////////////////////
// Graphics Manager class member functions

/******************************************************************************/
/*!
	Graphics Manager constructor, sets all its elements to nullptr
*/
/******************************************************************************/
Graphics_Manager::Graphics_Manager()
{
	for (unsigned i = 0; i < graphics_list_.size(); ++i)
		graphics_list_.at(i) = nullptr;
}
/******************************************************************************/
/*!
Gets the texture pointer
*/
/******************************************************************************/
AEGfxTexture* Graphics_Manager::Get_Texture(UNIT_TYPES unit) const
{
	return graphics_list_.at(unit)->Get_Texture();
}

/******************************************************************************/
/*!
Gets the draw mesh pointer
*/
/******************************************************************************/
AEGfxVertexList* Graphics_Manager::Get_Render_Mesh(UNIT_TYPES unit) const
{
	return graphics_list_.at(unit)->Get_Render_Mesh();
}

/******************************************************************************/
/*!
Gets the collision mesh pointer
*/
/******************************************************************************/
AEGfxVertexList* Graphics_Manager::Get_Collision_Mesh(UNIT_TYPES unit) const
{
	return graphics_list_.at(unit)->Get_Collision_Mesh();
}

/////////////////////////////////////////////
// Mesh and Texture Load and Unload functions

/******************************************************************************/
/*!
Loads a texture and returns a pointer to it
*/
/******************************************************************************/
AEGfxTexture * Texture_Load(const char * texture)
{
	AEGfxTexture * pTex = nullptr;

	pTex = AEGfxTextureLoad(texture); 

	return pTex;
}

/******************************************************************************/
/*!
Loads a circle mesh out of a number of points for collision detection and returns a pointer to it
*/
/******************************************************************************/
AEGfxVertexList * Mesh_Load_Circle(float scale, int points)
{
	// Creates the pointer to the mesh to be returned
	AEGfxVertexList * pMesh = nullptr;

	int i = 0;		// Loop counter
	float radian;	// Radian of angle
	float x;		// x coordinate of current point
	float y;		// y coordinate of current point

	AEGfxMeshStart();

	// Starts at radian 0, cuts up the circle and therefore 360 degrees into specified number of points
	for (radian = 0; i <= points; ++i, radian += AEDegToRad(360.0f / points))
	{
		// Finds x coordinate of current radian through cos radian
		x = AECos(radian) * scale;
		// Finds y coordinate of current radian through sin radian
		y = AESin(radian) * scale;

		// Adds a point
		AEGfxVertexAdd(x, y, 0xFFFFFFFF, 0.0f, 0.0f);
	}

	pMesh = AEGfxMeshEnd(); /*CAUSES MEMORY LEAK*/

	return pMesh;
}

/******************************************************************************/
/*!
Loads a square/rectangle mesh out of 2 triangles for rendering textures and returns a pointer to it
*/
/******************************************************************************/
AEGfxVertexList * Mesh_Load_Square(float length_scale, float height_scale, float texture_width, float texture_height, int index)
{
	AEGfxVertexList * pMesh = nullptr;

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f * length_scale, -0.5f * height_scale, 0xFF000000, 0.0f, texture_height * (index + 1),
		0.5f * length_scale, -0.5f * height_scale, 0xFF000000, texture_width, texture_height * (index + 1),
		-0.5f * length_scale, 0.5f * height_scale, 0xFF000000, 0.0f, texture_height * index);

	AEGfxTriAdd(
		0.5f * length_scale, -0.5f * height_scale, 0xFF000000, texture_width, texture_height * (index + 1),
		0.5f * length_scale, 0.5f * height_scale, 0xFF000000, texture_width, texture_height * index,
		-0.5f * length_scale, 0.5f * height_scale, 0xFF000000, 0.0f, texture_height * index);

	pMesh = AEGfxMeshEnd();
	//AE_ASSERT_MESG(pMesh, "Failed to create mesh!!");

	return pMesh;
}

/******************************************************************************/
/*!
Loads a square/rectangle mesh out of 2 triangles for rendering textures of text boxes 
and returns a pointer to it
*/
/******************************************************************************/
AEGfxVertexList * Mesh_Load_Text_Box(float length_scale, float height_scale, float texture_width, float texture_height, int index)
{
	AEGfxVertexList * pMesh = nullptr;

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f * length_scale, -0.5f * height_scale, 0xFF8B4513, 0.0f, texture_height * (index + 1),
		0.5f * length_scale, -0.5f * height_scale, 0xFF8B4513, texture_width, texture_height * (index + 1),
		-0.5f * length_scale, 0.5f * height_scale, 0xFF8B4513, 0.0f, texture_height * index);

	AEGfxTriAdd(
		0.5f * length_scale, -0.5f * height_scale, 0xFF8B4513, texture_width, texture_height * (index + 1),
		0.5f * length_scale, 0.5f * height_scale, 0xFF8B4513, texture_width, texture_height * index,
		-0.5f * length_scale, 0.5f * height_scale, 0xFF8B4513, 0.0f, texture_height * index);

	pMesh = AEGfxMeshEnd();
	//AE_ASSERT_MESG(pMesh, "Failed to create mesh!!");

	return pMesh;
}

/******************************************************************************/
/*!
Loads the meshes for the particles
*/
/******************************************************************************/
AEGfxVertexList * Mesh_Load_Particle(UNIT_TYPES type)
{
	AEGfxVertexList * pMesh = nullptr;

	AEGfxMeshStart();
	int sides = 12;
	switch (type)
	{
	case PARTICLE_EXPLOSION:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFF8F0000, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFF8F0000, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_SWEAT:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0x0F000000, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFF00A0FF, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFF00A0FF, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_MONEY_DROPS:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFFFFFF00, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFFFFFF00, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_POISON:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0x0F000000, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFFF000FF, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFFF000FF, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_SLEEPY_BUBBLE:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0x0F000000, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFF00A0FF, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFF00A0FF, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_SMOKE:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_POOF:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_RUBBLE:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0x88000000, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0x88000000, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0x88000000, 0.0f, 0.0f);
		}
		break;
	case PARTICLE_ATTACK_AURA:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFF888800, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFFFF0000, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFFFF0000, 0.0f, 0.0f);
		}
		break;
	default:
		//Creating the circle shape
		for (float i = 0; i < sides; ++i)
		{
			AEGfxTriAdd(
				0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
				AECos(i * 2 * PI / sides)*0.5f, AESin(i * 2 * PI / sides)*0.5f, 0xFF8F0000, 0.0f, 0.0f,
				AECos((i + 1) * 2 * PI / sides)*0.5f, AESin((i + 1) * 2 * PI / sides)*0.5f, 0xFF8F0000, 0.0f, 0.0f);
		}
		break;
	}
	pMesh = AEGfxMeshEnd();

	return pMesh;
}

/******************************************************************************/
/*!
Run this when loading the level and loads every unit used in the level into the graphics list
*/
/******************************************************************************/
void Graphics_Manager::Load_Graphics()
{
	pTex_button_yn = Texture_Load("Resources/Graphics/button_yn.png");
	pTex_granny = Texture_Load("Resources/Graphics/granny_textures.png");

	pTex_kid = Texture_Load("Resources/Graphics/kid_textures.png");

	pTex_button = Texture_Load("Resources/Graphics/granny_buttons.png");

	pTex_main_menu_button = Texture_Load("Resources/Graphics/buttons_main_menu.png");

	pTex_level_selection_button = Texture_Load("Resources/Graphics/level_buttons.png");

	pTex_granny_desc = Texture_Load("Resources/Graphics/granny_descriptions.png");


	pTex_granny_tower = Texture_Load("Resources/Graphics/granny_towers.png");
	pTex_kid_tower = Texture_Load("Resources/Graphics/kid_towers.png");
	pTex_path = Texture_Load("Resources/Graphics/path.png");

	pTex_wave_flag = Texture_Load("Resources/Graphics/wave_flag.png");
	pTex_button_volume = Texture_Load("Resources/Graphics/button_adjust_volume.png");
	pTex_button_player_data = Texture_Load("Resources/Graphics/button_player_data.png");
	pTex_button_bgm_sfx = Texture_Load("Resources/Graphics/button_bgm_sfx.png");
	pTex_button_play_data = Texture_Load("Resources/Graphics/button_player_data.png");
	pTex_general_upgrade_panel = Texture_Load("Resources/Graphics/general_upgrade_panel.png");
	pTex_button_upgrade = Texture_Load("Resources/Graphics/button_upgrade.png");
	pTex_desc_upgrade = Texture_Load("Resources/Graphics/desc_upgrade.png");

	pTex_tutorial_speech = Texture_Load("Resources/Graphics/general_tutorial.png");
	pTex_button_tower = Texture_Load("Resources/Graphics/button_tower.png");
	pTex_desc_tower = Texture_Load("Resources/Graphics/desc_tower.png");

	pTex_button_quit = Texture_Load("Resources/Graphics/button_quit.png");
	pTex_button_state_pause = Texture_Load("Resources/Graphics/button_state_pause.png");
	pTex_button_end_game = Texture_Load("Resources/Graphics/button_end_game.png");

	pTex_projectile_melee = Texture_Load("Resources/Graphics/projectile_melee.png");

	for (unsigned TYPE = 0; TYPE < LAST; ++TYPE)
		switch (TYPE)
		{
		case G_BASE:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/granny_base.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_BASE:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/kids_base.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_TANK:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 1), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_TANK:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 1), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_SPEED:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 2), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_SPEED:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 2), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_SABOTEUR:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 3), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_SABOTEUR:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 3), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 4), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 4), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_ATTACKSPEEDUP:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 5), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_ATTACKSPEEDUP:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 5), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 6), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 6), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_HEALER:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 7), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_HEALER:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 7), Mesh_Load_Circle(1.0f) };
			break;
		case G_S_ATTACKBUFF:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 8), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_ATTACKBUFF:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 8), Mesh_Load_Circle(1.0f) };
			break;
		case K_S_BIGBOB:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid, Mesh_Load_Square(1.0f, 1.0f, 0.125f, 0.1f, 9), Mesh_Load_Circle(1.0f) };
			break;
		case P_BLANK:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_P_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_cookie.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_P_SABOTEUR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_ninja_star.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_P_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_crazy_cat.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_P_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_stun.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_P_HEAL:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_heal.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_P_ATTACKSPEEDUP:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_projectile_melee, Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_ATTACKSPEEDUP:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_projectile_melee, Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case GT_P_AOE:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_dentures.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case GT_P_POISON:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_broccoli.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case GT_P_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_cake.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case GT_P_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_bone.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case P_MELEE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_projectile_melee, Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_ball.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_SABOTEUR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_book.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_sleepy.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_stun.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_HEAL:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_heal.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_P_BIGBOB:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_projectile_melee, Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case KT_P_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_toilet_roll.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case KT_P_AOE:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_pillow.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case KT_P_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_toy_car.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case KT_P_POISON:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_fart.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case KT_P_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/projectile_mud.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_BUTTON_1:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f), nullptr };
			break;
		case G_BUTTON_2:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 1), nullptr };
			break;
		case G_BUTTON_3:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 2), nullptr };
			break;
		case G_BUTTON_4:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 3), nullptr };
			break;
		case G_BUTTON_5:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 4), nullptr };
			break;
		case G_BUTTON_6:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 5), nullptr };
			break;
		case G_BUTTON_7:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 6), nullptr };
			break;
		case G_BUTTON_8:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 7), nullptr };
			break;
		case G_BUTTON_9:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.1f, 8), nullptr };
			break;
		case G_DESC:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny_desc, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;
		case START_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_main_menu_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f), nullptr };
			break;
		case OPTIONS_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_main_menu_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 1),nullptr };
			break;
		case CREDITS_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_main_menu_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 2),nullptr };
			break;
		case GRANNY_MOJO:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/granny_coin.png"), Mesh_Load_Square(1.0f, 1.0f),nullptr };
			break;
		case QUIT_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_main_menu_button, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 3), nullptr };
			break;
		case DECREASE_VOLUME_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_volume, Mesh_Load_Square(1.0f, 1.0f,  1.0f/6.0f, 0.25f),nullptr };
			break;
		case INCREASE_VOLUME_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_volume, Mesh_Load_Square(1.0f, 1.0f,  1.0f / 6.0f, 0.25f, 1),nullptr };
			break;
		case FULLSCREEN_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_volume, Mesh_Load_Square(1.0f, 1.0f, 1.0f/6.0f, 0.25f, 2),nullptr };
			break;
		case DELETE_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_delete_player.png") , Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 2),nullptr };
			break;
		case NEW_GAME:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_play_data, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f),nullptr };
			break;
		case PLAYER_1:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_play_data, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 1),nullptr };
			break;
		case PLAYER_2:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_play_data, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 2),nullptr };
			break;
		case PLAYER_3:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_play_data, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 3),nullptr };
			break;
		case BGM_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_bgm_sfx, Mesh_Load_Square(1.0f, 1.0f, 1.0f/6.0f, 0.5f),nullptr };
			break;
		case SFX_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_bgm_sfx, Mesh_Load_Square(1.0f, 1.0f,  1.0f / 6.0f, 0.5f, 1),nullptr };
			break;
		case VOLUME_BAR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_adjust_volume_bar.png") , Mesh_Load_Square(1.0f, 1.0f, 1.0f/6.0f, 1.0f),nullptr };
			break;
		case FULLSCREEN:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_fullscreen.png") , Mesh_Load_Square(1.0f, 1.0f),nullptr };
			break;
		case LEVEL_1_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f), nullptr };
			break;
		case LEVEL_2_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 1), nullptr };
			break;
		case LEVEL_3_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 2), nullptr };
			break;
		case LEVEL_4_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 3), nullptr };
			break;
		case LEVEL_5_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 4), nullptr };
			break;
		case LEVEL_6_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 5), nullptr };
			break;
		case LEVEL_7_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 6), nullptr };
			break;
		case LEVEL_8_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 7), nullptr };
			break;
		case LEVEL_9_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 8), nullptr };
			break;
		case LEVEL_10_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_level_selection_button, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 0.1f, 9), nullptr };
			break;
		case LOCKED_LEVEL:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/locked_level.png") , Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case LOCKED_GRANNY:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/locked_granny.png") , Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case BACK_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_back.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f), nullptr };
			break;
		case SHOP_BUTTON:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_shop.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f), nullptr };
			break;
		case ICON_GRANNY:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_granny_icon.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case ICON_KID:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_kid_icon.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case UI_PANEL:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/UI_Panel.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case WAVE_BAR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/wave_bar.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case WAVE_FILLER:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/wave_filler.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case WAVE_FLAG:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_wave_flag, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 0.5f), Mesh_Load_Circle(1.0f) };
			break;
		case WAVE_FLAG_BOSS:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_wave_flag, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 0.5f, 1), Mesh_Load_Circle(1.0f) };
			break;
		case GRANNY_BAR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/granny_bar.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case GRANNY_FILLER:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/granny_filler.png"), Mesh_Load_Square(1.0f, 1.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_TOWER_NODE1:
		case G_TOWER_NODE2:
		case G_TOWER_NODE3:
		case G_TOWER_NODE4:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_tower_node.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f), nullptr };
			break;
		case G_T_SHOOTING:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f/6.0f), Mesh_Load_Circle(1.0f) };
			break;
		case G_T_POISON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 2), Mesh_Load_Circle(1.0f) };
			break;
		case G_T_SWING:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 1), Mesh_Load_Circle(1.0f) };
			break;
		case G_T_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 3), Mesh_Load_Circle(1.0f) };
			break;
		case G_T_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_granny_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 4), Mesh_Load_Circle(1.0f) };
			break;
		case K_TOWER_NODE:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/Kid_Tower_Node.png"), Mesh_Load_Square(1.0f, 1.0f, 0.5f), Mesh_Load_Circle(1.0f) };
			break;
		case K_T_SHOOTING:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid_tower,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f), Mesh_Load_Circle(1.0f) };
			break;
		case K_T_POISON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid_tower,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 2), Mesh_Load_Circle(1.0f) };
			break;
		case K_T_SWING:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid_tower,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 1), Mesh_Load_Circle(1.0f) };
			break;
		case K_T_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid_tower,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 3), Mesh_Load_Circle(1.0f) };
			break;
		case K_T_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_kid_tower,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 4), Mesh_Load_Circle(1.0f) };
			break;
		case PATH_STRAIGHT:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_path, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 0.5f), nullptr };
			break;
		case PATH_TURN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_path, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 0.5f, 1), nullptr };
			break;
		case BLACK_SCREEN:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case LEVEL1_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/Grass.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case DIGIPEN_LOGO_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/background_digipen_logo.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TEAM_LOGO_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/background_team_logo.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case MAIN_MENU_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/background_main_menu.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case CREDITS_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/background_credits.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case UPGRADE_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/background_upgrade.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case OPTIONS_BACKGROUND:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/background_options.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case VICTORY_STAR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_star.png"), Mesh_Load_Square(1.0f, 1.0f, 0.5f), nullptr };
			break;
		case LEVEL_MULTIPLIER:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_level_up.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f), nullptr };
			break;
		case PARTICLE_BLANK:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, nullptr, nullptr };
			break;
		case PARTICLE_HIT_EFFECT:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_HIT_EFFECT), nullptr };
			break;
		case PARTICLE_FIRE:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_FIRE), nullptr };
			break;
		case PARTICLE_EXPLOSION:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_EXPLOSION), nullptr };
			break;
		case PARTICLE_POISON:	
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_POISON), nullptr };
			break;
		case PARTICLE_SLEEPY_BUBBLE:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_SLEEPY_BUBBLE), nullptr };
			break;
		case PARTICLE_GLOW:
		case PARTICLE_ATTACK_AURA:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_ATTACK_AURA), nullptr };
			break;
		case PARTICLE_MONEY_DROPS:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_MONEY_DROPS), nullptr };
			break;
		case PARTICLE_SWEAT:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_SWEAT), nullptr };
			break;
		case PARTICLE_SMOKE:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_SMOKE), nullptr };
			break;
		case PARTICLE_RUBBLE:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_RUBBLE), nullptr };
			break;
		case PARTICLE_POOF:
			graphics_list_.at(TYPE) = new GraphicsData{ nullptr, Mesh_Load_Particle(PARTICLE_POOF), nullptr };
			break;
		case GENERAL_GRANNY_UPGRADE_1:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;
		case GENERAL_GRANNY_UPGRADE_2:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;
		case GENERAL_GRANNY_UPGRADE_3:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																	
		case GENERAL_GRANNY_UPGRADE_4:												
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																	
		case GENERAL_GRANNY_UPGRADE_5:												
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																	
		case GENERAL_GRANNY_UPGRADE_6:												
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																
		case GENERAL_GRANNY_UPGRADE_7:											
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																
		case GENERAL_GRANNY_UPGRADE_8:											
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																
		case GENERAL_GRANNY_UPGRADE_9:											
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;																
		case GENERAL_GRANNY_UPGRADE_10:											
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_general_upgrade_panel, Mesh_Load_Square(1.0f, 1.0f, 0.1f, 1.0f), nullptr };
			break;

		case BUTTON_HEALTH_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f/6.0f, 1.0f/12.0f), nullptr };
			break;
		case BUTTON_RANGE_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 1), nullptr };
			break;
		case BUTTON_NINJA_ATTACKRATE_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 2), nullptr };
			break;
		case BUTTON_MAX_CAP:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 9), nullptr };
			break;
		case BUTTON_COST_DECREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 8), nullptr };
			break;
		case BUTTON_COOKIE_ATTACKRATE_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 3), nullptr };
			break;
		case BUTTON_SPEED_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 4), nullptr };
			break;
		case BUTTON_COOLDOWN_DECREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 5), nullptr };
			break;
		case BUTTON_HEALING_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 6), nullptr };
			break;
		case BUTTON_DAMAGE_INCREASE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 7), nullptr };
			break;

		case DESC_HEALTH_INCREASE_1:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f), nullptr };
			break;
			case DESC_HEALTH_INCREASE_2:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 8), nullptr };
			break;
			case DESC_RANGE_INCREASE_1:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f,1 ), nullptr };
			break;
			case DESC_RANGE_INCREASE_2:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 9), nullptr };
			break;
			case DESC_ATTACKRATE_INCREASE_1:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 2), nullptr };
			break;
			case DESC_ATTACKRATE_INCREASE_2:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 3), nullptr };
			break;
			case DESC_SPEED_INCREASE:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 4), nullptr };
			break;
			case DESC_COOLDOWN_DECREASE:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 5), nullptr };
			break;
			case DESC_HEALING_INCREASE:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 6), nullptr };
			break;
			case DESC_DAMAGE_INCREASE:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 7), nullptr };
			break;
			case DESC_COST_DECREASE:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 10), nullptr };
			break;
			case DESC_MAX_CAP_INCREASE:
				graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 12.0f, 11), nullptr };
			break;
		case GENERAL_STARS_LEFT:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_stars_left.png") , Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case BUTTON_RANGE_INCREASE_2:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_upgrade, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 6.0f, 1.0f / 12.0f, 10), nullptr };
			break;

		case TUTORIAL_SPEECH_0:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_tutorial_speech, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 1.0f / 4.0f, 0), nullptr };
			break;
		case TUTORIAL_SPEECH_1:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_tutorial_speech, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 1.0f / 4.0f, 1), nullptr };
			break;
		case TUTORIAL_SPEECH_2:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_tutorial_speech, Mesh_Load_Square(1.0f, 1.0f, 1.0f / 12.0f, 1.0f / 4.0f, 2), nullptr };
			break;
		case CURSOR:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/cursor.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;

		case HEALTH:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_base_health.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f), nullptr };
			break;

		case BUTTON_TOWER_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_tower,Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f/6.0f), nullptr };
			break;

		case BUTTON_TOWER_SWINGING:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 1), nullptr };
			break;

		case BUTTON_TOWER_POISON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 2), nullptr };
			break;

		case BUTTON_TOWER_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 3), nullptr };
			break;

		case BUTTON_TOWER_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 4), nullptr };
			break;
		case BUTTON_TOWER_CLOSE:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_tower, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f / 6.0f, 5), nullptr };
			break;
		case GENERAL_RING:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_ring.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case DESC_TOWER_SHOOTER:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_tower, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f/6.0f), nullptr };
			break;
		case DESC_TOWER_SWINGING:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_tower, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 6.0f, 1), nullptr };
			break;
		case DESC_TOWER_POISON:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_tower, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 6.0f, 2), nullptr };
			break;
		case DESC_TOWER_SLOW:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_tower, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 6.0f, 3), nullptr };
			break;
		case DESC_TOWER_STUN:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_desc_tower, Mesh_Load_Square(1.0f, 1.0f, 1.0f, 1.0f / 6.0f, 4), nullptr };
			break;
		case GAME_STAT:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/game_stat.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f), nullptr };
			break;

		case BUTTON_YES:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_quit, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.5f), nullptr };
			break;

		case BUTTON_NO:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_quit , Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.5f, 1), nullptr };
			break;
		case BUTTON_RESUME:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_state_pause, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f), nullptr };
			break;
		case BUTTON_RESTART:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_state_pause, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 1), nullptr };
			break;
		case BUTTON_QUIT:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_state_pause, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 2), nullptr };
			break;
		case BUTTON_LEVEL_SELECT:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_end_game, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f), nullptr };
			break;
		case BUTTON_RESTART_2:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_end_game, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 1), nullptr };
			break;
		case BUTTON_SHOP:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_end_game, Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.25f, 2), nullptr };
			break;
		case BUTTON_NEXT_LEVEL:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_end_game_next_level.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f), nullptr };
			break;
		case BUTTON_PAUSE:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_pause.png"), Mesh_Load_Square(1.0f, 1.0f, 0.25f, 1.0f), nullptr };

			break;
		case BUTTON_TIME_ADJUST:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/button_time_adjust.png"), Mesh_Load_Square(1.0f, 1.0f, 1.0f/6.0f, 1.0f), nullptr };
			break;
		// TUTORIAL 0 SPEECH
		case TUTORIAL_SPEECH_01:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_01.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_02:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_02.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_03:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_03.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_04:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_04.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_05:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_05.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_06:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_06.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_07:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_07.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_08:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_08.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_09:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_09.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_10:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_10.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_11:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_11.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case TUTORIAL_SPEECH_12:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/general_tutorial_12.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case CONFIRMATION:
			graphics_list_.at(TYPE) = new GraphicsData{ Texture_Load("Resources/Graphics/confirmation.png"), Mesh_Load_Square(1.0f, 1.0f), nullptr };
			break;
		case BUTTON_Y:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_yn,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.5f), nullptr };
			break;
		case BUTTON_N:
			graphics_list_.at(TYPE) = new GraphicsData{ pTex_button_yn,  Mesh_Load_Square(1.0f, 1.0f, 0.25f, 0.5f, 1), nullptr };
			break;



		}
}

/******************************************************************************/
/*!
Unloads all the textures and meshes loaded when exiting application
*/
/******************************************************************************/
void Graphics_Manager::Unload_Graphics()
{
	// Loop through every individual graphics
	for (unsigned i = 0; i < graphics_list_.size(); ++i)
	{
		if (graphics_list_.at(i))
		{
			// Everything before this object is a shared texture
			if (i <= BUTTON_N)
				graphics_list_.at(i)->Free_Graphics_Data(false);

			else graphics_list_.at(i)->Free_Graphics_Data(true);

			delete graphics_list_.at(i);

			graphics_list_.at(i) = nullptr;
		}
	}
	
	// Frees all the shared textures
	AEGfxTextureUnload(pTex_button_yn);
	AEGfxTextureUnload(pTex_granny);
	AEGfxTextureUnload(pTex_kid);
	AEGfxTextureUnload(pTex_button);
	AEGfxTextureUnload(pTex_main_menu_button);
	AEGfxTextureUnload(pTex_level_selection_button);
	AEGfxTextureUnload(pTex_granny_desc);
	AEGfxTextureUnload(pTex_granny_tower);
	AEGfxTextureUnload(pTex_kid_tower);
	AEGfxTextureUnload(pTex_wave_flag);
	AEGfxTextureUnload(pTex_path);
	AEGfxTextureUnload(pTex_button_volume);
	AEGfxTextureUnload(pTex_button_player_data);
	AEGfxTextureUnload(pTex_button_bgm_sfx);
	AEGfxTextureUnload(pTex_button_play_data);
	AEGfxTextureUnload(pTex_general_upgrade_panel);
	AEGfxTextureUnload(pTex_button_upgrade);
	AEGfxTextureUnload(pTex_desc_upgrade);
	AEGfxTextureUnload(pTex_tutorial_speech);
	AEGfxTextureUnload(pTex_button_tower);
	AEGfxTextureUnload(pTex_desc_tower);
	AEGfxTextureUnload(pTex_button_quit);
	AEGfxTextureUnload(pTex_button_state_pause);
	AEGfxTextureUnload(pTex_button_end_game);
	AEGfxTextureUnload(pTex_projectile_melee);
	pTex_granny = nullptr;
	pTex_kid = nullptr;
	pTex_button = nullptr;
	pTex_main_menu_button = nullptr;
	pTex_level_selection_button = nullptr;
	pTex_granny_desc = nullptr;
	pTex_granny_tower = nullptr;
	pTex_kid_tower = nullptr;
	pTex_wave_flag = nullptr;
	pTex_path = nullptr;
	pTex_button_volume = nullptr;
	pTex_button_bgm_sfx = nullptr;
	pTex_button_player_data = nullptr;
	pTex_button_play_data = nullptr;
	pTex_general_upgrade_panel = nullptr;
	pTex_button_upgrade = nullptr;
	pTex_desc_upgrade = nullptr;
	pTex_tutorial_speech = nullptr;
	pTex_button_tower = nullptr;
	pTex_desc_tower = nullptr;
	pTex_button_quit = nullptr;
	pTex_button_state_pause = nullptr;
	pTex_button_end_game = nullptr;
	pTex_projectile_melee = nullptr;
	pTex_button_yn = nullptr;
}
