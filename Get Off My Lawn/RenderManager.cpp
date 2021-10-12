/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   RenderManager.cpp
\author Wong Zhihao		(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of Rendering functions to render
things out into the game.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "RenderManager.h"		// Function declarations
#include "SystemComponents.h"	// Components
#include "LogicComponents.h"	// Components
#include "ObjectList.h"			// Object enums

/******************************************************************************/
/*!
Renders a given object in the game. Called during Game State Draw
*/
/******************************************************************************/
void Render_Object(GameObject & object)
{
	// Gets the object's texture
	AEGfxTexture * texture = object.Get_Texture();
	// Gets the object's render mesh
	AEGfxVertexList * renderMesh = object.Get_Render_Mesh();

	// If a mesh exists
	if (renderMesh)
	{
		float texture_change = object.Get_Texture_Change();

		if (texture)
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		else
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);

		// Render the texture mesh
		// Set position for object
		AEGfxSetTransform(object.Get_Matrix().m);
		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);


		// Sets the texture of object
		AEGfxTextureSet(texture, texture_change, 0.0f);

		//set transparency
		if (object.Get_Object_Type() == TYPE_BLACK_SCREEN_FADE)
			AEGfxSetTransparency(logic_components.object_manager->Get_Black_Screen(true)->Get_Transparency());
		else if (object.Get_Object_Type() == TYPE_BLACK_SCREEN_TINT)
			AEGfxSetTransparency(logic_components.object_manager->Get_Black_Screen(false)->Get_Transparency());
		else
			AEGfxSetTransparency(1.0f);


		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(renderMesh, AE_GFX_MDM_TRIANGLES);
	}
}

/******************************************************************************/
/*!
Renders particles in the game
*/
/******************************************************************************/
void Render_Particle(Particle & particle)
{
	// Gets the object's texture
	AEGfxTexture * texture = particle.Get_Texture();
	// Gets the object's render mesh
	AEGfxVertexList * renderMesh = particle.Get_Render_Mesh();

	float texture_change = particle.Get_Texture_Change();

	AEGfxSetBlendMode(AE_GFX_BM_ADD);
	// Check if object has texture
	if (texture)
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	else
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetTransform(particle.Get_Matrix().m);
	// No tint
	float tint = particle.Get_Tint();
	if (particle.Get_Unit_Type() == PARTICLE_SMOKE)
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	else
		AEGfxSetTintColor(tint, tint, tint, 1.0f);
	particle.Change_Tint(-((system_components.framerate_manager->Get_Game_Time()) / particle.Get_Initial_Lifetime()));


	// Sets the texture of object
	AEGfxTextureSet(texture, texture_change, 0.0f);
	//set transparency
	AEGfxSetTransparency(particle.Get_Transparency());
	particle.Change_Transparency(-((system_components.framerate_manager->Get_Game_Time()) / particle.Get_Initial_Lifetime()));

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(renderMesh, AE_GFX_MDM_TRIANGLES);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

/******************************************************************************/
/*!
	Renders particles in the game without fading
*/
/******************************************************************************/
void Render_Particle_Without_Fade(Particle & particle)
{
	// Gets the object's texture
	AEGfxTexture * texture = particle.Get_Texture();
	// Gets the object's render mesh
	AEGfxVertexList * renderMesh = particle.Get_Render_Mesh();

	float texture_change = particle.Get_Texture_Change();

	// Check if object has texture
	if (texture)
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	else
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetTransform(particle.Get_Matrix().m);
	// No tint
	float tint = particle.Get_Tint();
	AEGfxSetTintColor(tint, tint, tint, 1.0f);

	// Sets the texture of object
	AEGfxTextureSet(texture, texture_change, 0.0f);
	//set transparency
	AEGfxSetTransparency(particle.Get_Transparency());

	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(renderMesh, AE_GFX_MDM_TRIANGLES);
}

/******************************************************************************/
/*!
Prints text in game
*/
/******************************************************************************/
void Print_Text(u32 fontID, char strBuffer[], s32 x, s32 y, f32 red, f32 green, f32 blue)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(NULL, 0.0f, 0.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxPrint(fontID, strBuffer, x, y, red, green, blue);
}

/******************************************************************************/
/*!
	Animates soldiers by changing their texture
*/
/******************************************************************************/
void Animate_Soldier(Soldier & soldier)
{
	// Handles how often the texture changes
	soldier.Set_Texture_Timer(soldier.Get_Texture_Timer() - (system_components.framerate_manager->Get_Game_Time()));
	if (soldier.Get_Texture_Timer() < 0)
	{
		soldier.Set_Texture_Change(soldier.Get_Texture_Change() + soldier.Get_Texture_Width());
		soldier.Set_Texture_Timer(0.05f);
	}
	if (soldier.Get_Texture_Change() >= 1)
	{
		soldier.Set_Texture_Change(0.0f);
	}
}

/******************************************************************************/
/*!
	Animates towers by changing their texture
*/
/******************************************************************************/
void Animate_Tower(Tower & tower)
{
	// Texture changes only when attacking
	if (tower.Get_Attacking()) {
		tower.Set_Texture_Timer(tower.Get_Texture_Timer() - (system_components.framerate_manager->Get_Game_Time()));
		if (tower.Get_Texture_Timer() < 0.0f)
		{
			tower.Set_Texture_Change(tower.Get_Texture_Change() + tower.Get_Texture_Width());
			tower.Set_Texture_Timer(1.0f);
		}
		if (tower.Get_Texture_Change() > 0.5f)
		{
			tower.Set_Texture_Change(0.0f);
		}
	}

	// Change texture based on tower HP
	else
	{
		if (tower.Get_Health() < (tower.Get_Max_Health() / 2))
			tower.Set_Texture_Change(tower.Get_Texture_Width() * 3);
		else
			tower.Set_Texture_Change(0.0f);
	}
}