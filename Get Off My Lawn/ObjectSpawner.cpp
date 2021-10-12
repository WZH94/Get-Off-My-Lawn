/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   ObjectSpawner.cpp
\author Wong Zhihao (80%)| Ngm Hui Min, Lois (10%)| Sng Zhi Ren Zachary (10%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu | z.sng\@digipen.edu	
\par    DigiPen login: zhihao.wong | lois.ngm | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file handles the spawning of every objects in the game. Allocates memory as well.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.

*/
/******************************************************************************/

#include "ObjectSpawner.h"		// Function declarations
#include "GraphicsManager.h"	// Graphics list
#include "LogicComponents.h"	// Logic Components
#include "GameObject.h"			// GameObject type
#include "SystemComponents.h"	// System components

#include "GameStateList.h"		// Game state enums
#include "Button.h"				// Button class
#include "DescriptionButton.h"	// Description button class
#include "SoldierButton.h"		// Soldier button class
#include "MojoButton.h"			// Mojo button class
#include "PlayerData.h"			// Player data class

// Unit includes
#include "ObjectList.h"


/******************************************************************************/
/*!
	Spawns normal objects such as soldiers and bases.
*/
/******************************************************************************/
void Spawn_Object(UNIT_TYPES type, float x, float y)
{
	switch (type)
	{
		//Bases
	case G_BASE: {
		GameObject * gBase = new GameObject{
			GRANDMA,
			x, y,
			200.0f,
			200.0f,
			BASE,
			G_BASE
		};
		logic_components.object_manager->Insert_Object(gBase);
		break; }

	case K_BASE: {
		GameObject * kBase = new GameObject{
			KIDS,
			x, y,
			200.0f,
			200.0f,
			BASE,
			K_BASE
		};
		logic_components.object_manager->Insert_Object(kBase);
		break; }

				 //Grannies
	case G_S_SHOOTER: {
		GameObject * gShooter = new Normal{
			60.0f,					// Speed		

			false,					// Not AOE
			45,						// Health
			10,						// Cost
			0,						// Loot
			5,						// Damage
			playdata.Get_Shooter_Upgrade() == 2 ? 0.9f : 1.2f,		// Attack speed
			playdata.Get_Shooter_Upgrade() ? 80.0f : 60.0f,	// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gShooter);
		break; }

	case G_S_TANK: {
		GameObject * gTank = new Normal{
			playdata.Get_Tank_Upgrade() ? 60.0f : 45.0f,	// Speed		

			false,					// Not AOE
			playdata.Get_Tank_Upgrade() == 2 ? 100 : 80,		// Health
			20,						// Cost
			0,						// Loot
			4,						// Damage
			1.5f,					// Attack speed
			1.0f,					// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gTank);
		break; }

	case G_S_SPEED: {
		GameObject * gRacer = new Rusher{
			playdata.Get_Speed_Upgrade() == 2 ? 240.0f : 120.0f,		// Speed		

			false,					// Not AOE
			playdata.Get_Speed_Upgrade() ? 20 : 10,				// Health
			20,						// Cost
			0,						// Loot
			0,						// Damage
			0.0f,					// Attack speed
			0.0f,					// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gRacer);
		break; }

	case G_S_SABOTEUR: {
		GameObject * gNinja = new Rusher{
			playdata.Get_Saboteur_Upgrade() ? 80.0f : 60.0f,		// Speed		

			false,					// Not AOE
			35,						// Health
			35,						// Cost
			0,						// Loot
			5,						// Damage
			playdata.Get_Saboteur_Upgrade() == 2 ? 0.7f : 1.0f,			// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gNinja);
		break; }

	case G_S_SLOW: {
		GameObject * gSlow = new Anti_Rusher{
			60.0f,					// Speed		

			false,					// Not AOE
			50,						// Health
			50,						// Cost
			0,						// Loot
			playdata.Get_Slow_Upgrade() == 2 ? 8 : 5,						// Damage
			0.6f,					// Attack speed
			playdata.Get_Slow_Upgrade() ? 80.0f : 60.0f,				// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gSlow);
		break; }

	case G_S_ATTACKSPEEDUP: {
		GameObject * gKungFu = new Anti_Rusher{
			60.0f,					// Speed		

			false,					// Not AOE
			playdata.Get_Bruiser_Upgrade() ? 120 : 100,					// Health
			100,					// Cost
			0,						// Loot
			playdata.Get_Bruiser_Upgrade() == 2 ? 12 : 10,						// Damage
			0.5f,					// Attack speed
			1.0f,					// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gKungFu);
		break; }

	case G_S_STUN: {
		GameObject * gStun = new Anti_Rusher{
			60.0f,					// Speed		

			true,					// Not AOE
			50,						// Health
			75,						// Cost
			0,						// Loot
			playdata.Get_Stun_Upgrade() ? 15 : 12,					// Damage
			4.0f,					// Attack speed
			playdata.Get_Stun_Upgrade() == 2 ? 80.0f : 60.0f,			// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gStun);
		break; }

	case G_S_HEALER: {
		GameObject * gHeal = new Support{
			60.0f,					// Speed		

			false,					// Not AOE
			60,						// Health
			80,						// Cost
			0,						// Loot
			playdata.Get_Heal_Upgrade() == 2 ? -15 : -10,			// Damage
			3.0f,					// Attack speed
			playdata.Get_Heal_Upgrade() ? 80.0f : 60.0f,		// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gHeal);
		break; }

	case G_S_ATTACKBUFF: {
		GameObject * gBuff = new Support{
			60.0f,					// Speed		

			true,					// Not AOE
			playdata.Get_Buff_Upgrade() ? 75 : 60,						// Health
			90,						// Cost
			0,						// Loot
			2,						// Damage
			0.4f,					// Attack speed
			playdata.Get_Buff_Upgrade() == 2 ? 80.0f : 60.0f,					// Range, will be added on with unit's radius

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(gBuff);
		break; }

						 //Kids
	case K_S_SHOOTER: {
		GameObject * kShooter = new Normal{
			60.0f,					// Speed		

			false,					// Not AOE
			20,						// Health
			0,						// Cost
			10,						// Loot
			2,						// Damage
			0.6f,					// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kShooter);
		break; }

	case K_S_TANK: {
		GameObject * kTank = new Normal{
			45.0f,					// Speed		

			false,					// Not AOE
			50,					    // Health
			0,						// Cost
			30,						// Loot
			2,						// Damage
			1.2f,					// Attack speed
			4.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kTank);
		break; }

	case K_S_SPEED: {
		GameObject * kRacer = new Rusher{
			120.0f,					// Speed		

			false,					// Not AOE
			10,						// Health
			0,						// Cost
			10,						// Loot
			0,						// Damage
			0.0f,					// Attack speed
			0.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kRacer);
		break; }

	case K_S_SABOTEUR: {
		GameObject * kSabo = new Rusher{
			60.0f,					// Speed		

			false,					// Not AOE
			25,						// Health
			0,						// Cost
			25,						// Loot
			3,						// Damage
			1.0f,					// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kSabo);
		break; }

	case K_S_ATTACKSPEEDUP: {
		GameObject * kAttack = new Anti_Rusher{
			60.0f,					// Speed		

			false,					// Not AOE
			40,						// Health
			0,						// Cost
			40,						// Loot
			5,						// Damage
			0.5f,					// Attack speed
			4.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kAttack);
		break; }

	case K_S_STUN: {
		GameObject * kStun = new Anti_Rusher{
			60.0f,					// Speed		

			true,					// Not AOE
			25,						// Health
			0,						// Cost
			35,						// Loot
			10,						// Damage
			4.0f,					// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kStun);
		break; }

	case K_S_SLOW: {
		GameObject * kSlow = new Anti_Rusher{
			60.0f,					// Speed		

			false,					// Not AOE
			25,						// Health
			0,						// Cost
			20,						// Loot
			2,						// Damage
			0.4f,					// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kSlow);
		break; }

	case K_S_HEALER: {
		GameObject * kHeal = new Support{
			60.0f,					// Speed

			false,					// Not AOE
			25,						// Health
			0,						// Cost
			30,						// Loot
			-7,						// Damage
			1.5f,					// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kHeal);
		break; }

	case K_S_ATTACKBUFF: {
		GameObject * kBuff = new Support{
			60.0f,					// Speed

			true,					// Not AOE
			25,						// Health
			0,						// Cost
			40,						// Loot
			2,						// Damage
			0.4f,					// Attack speed
			60.0f,					// Range, will be added on with unit's radius

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			34.0f,					// Scale/Radius of object
			34.0f,
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(kBuff);
		break; }

	case K_S_BIGBOB: {
		switch (gAEGameStateCurr)
		{
		case GS_LEVEL_2: {
			GameObject * kBob2 = new Anti_Rusher{
				30.0f,					// Speed

				false,					// Not AOE
				300,					// Health
				0,						// Cost
				0,						// Loot
				20,						// Damage
				0.5f,					// Attack speed
				10.0f,					// Range, will be added on with unit's radius

				KIDS,					// Which side this unit is on
				x, y,					// Spawn position
				68.0f,					// Scale/Radius of object
				68.0f,					// Scale/Radius of object
				type					// What specific type of unit it is
			};
			logic_components.object_manager->Insert_Object(kBob2);
			break; }
		case GS_LEVEL_4: {
			GameObject * kBob4 = new Anti_Rusher{
				30.0f,					// Speed

				false,					// Not AOE
				500,					// Health
				0,						// Cost
				0,						// Loot
				40,						// Damage
				0.5f,					// Attack speed
				10.0f,					// Range, will be added on with unit's radius

				KIDS,					// Which side this unit is on
				x, y,					// Spawn position
				68.0f,					// Scale/Radius of object
				68.0f,					// Scale/Radius of object
				type					// What specific type of unit it is
			};
			logic_components.object_manager->Insert_Object(kBob4);
			break; }
		case GS_LEVEL_6: {
			GameObject * kBob6 = new Anti_Rusher{
				30.0f,					// Speed

				false,					// Not AOE
				750,					// Health
				0,						// Cost
				0,						// Loot
				40,						// Damage
				0.5f,					// Attack speed
				10.0f,					// Range, will be added on with unit's radius

				KIDS,					// Which side this unit is on
				x, y,					// Spawn position
				68.0f,					// Scale/Radius of object
				68.0f,					// Scale/Radius of object
				type					// What specific type of unit it is
			};
			logic_components.object_manager->Insert_Object(kBob6);
			break; }
		case GS_LEVEL_8: {
			GameObject * kBob8 = new Anti_Rusher{
				30.0f,					// Speed

				false,					// Not AOE
				1000,					// Health
				0,						// Cost
				0,						// Loot
				50,						// Damage
				0.5f,					// Attack speed
				10.0f,					// Range, will be added on with unit's radius

				KIDS,					// Which side this unit is on
				x, y,					// Spawn position
				68.0f,					// Scale/Radius of object
				68.0f,					// Scale/Radius of object
				type					// What specific type of unit it is
			};
			logic_components.object_manager->Insert_Object(kBob8);
			break; }
		case GS_LEVEL_10: {
			GameObject * kBob10 = new Anti_Rusher{
				30.0f,					// Speed

				false,					// Not AOE
				1250,					// Health
				0,						// Cost
				0,						// Loot
				50,						// Damage
				0.5f,					// Attack speed
				10.0f,					// Range, will be added on with unit's radius

				KIDS,					// Which side this unit is on
				x, y,					// Spawn position
				68.0f,					// Scale/Radius of object
				68.0f,					// Scale/Radius of object
				type					// What specific type of unit it is
			};
			logic_components.object_manager->Insert_Object(kBob10);
			break; }
		default: {
			GameObject * kBob = new Anti_Rusher{
				30.0f,					// Speed

				false,					// Not AOE
				500,					// Health
				0,						// Cost
				0,						// Loot
				40,						// Damage
				0.5f,					// Attack speed
				10.0f,					// Range, will be added on with unit's radius

				KIDS,					// Which side this unit is on
				x, y,					// Spawn position
				68.0f,					// Scale/Radius of object
				68.0f,					// Scale/Radius of object
				type					// What specific type of unit it is
			};
			logic_components.object_manager->Insert_Object(kBob);
			break; }
		};
		break; }

					 //Buttons
	case G_BUTTON_1:
	case G_BUTTON_2:
	case G_BUTTON_3:
	case G_BUTTON_4:
	case G_BUTTON_5:
	case G_BUTTON_6:
	case G_BUTTON_7:
	case G_BUTTON_8:
	case G_BUTTON_9: {
		GameObject * UI_Button = new SoldierButton{ x, y, 60.0f, 60.0f, type, 0.25f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case START_BUTTON:
	case OPTIONS_BUTTON:
	case CREDITS_BUTTON:
	case QUIT_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 192.0f, 96.0f, type, 0.25f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case GAME_STAT: 
	{
		GameObject * UI_Button = new GameObject{ NONE, x, y, 400.0f, 400.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Alive(false);
		break; 
	}
	case BUTTON_YES:
	case BUTTON_NO:
	{
		GameObject * UI_Button = new Button{ x, y, 100.0f,100.0f, type, 0.25f };
		Button * button = dynamic_cast<Button*>(UI_Button);
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Alive(false);
		button->Set_Active(PAUSED);
		break;
	}


	case GRANNY_MOJO: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 25.0f, 25.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }

	case DECREASE_VOLUME_BUTTON:
	case INCREASE_VOLUME_BUTTON:
	{
		GameObject * UI_Button = new Button{ x, y, 96.0f, 96.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case FULLSCREEN_BUTTON: {
		float texture_start = (full_screen) ? 0.5f : 0.0f;
		GameObject * UI_Button = new Button{ x, y, 96.0f, 96.0f, type, 1.0f/6.0f , texture_start};
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }

	case FULLSCREEN:
	{
		GameObject * UI_Button = new GameObject{NONE, x, y, 192.0f, 96.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case VOLUME_BAR:
	{
		GameObject * UI_Button = new GameObject{NONE, x, y, 350.0f, 96.0f, GENERAL, type };
		if(y== 50.0f)
			UI_Button->Set_Texture_Change(system_components.audio_manager->Get_Music_Volume() * 5.0f/6.0f);
		else
			UI_Button->Set_Texture_Change(system_components.audio_manager->Get_SFX_Volume() * 5.0f / 6.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case BGM_BUTTON:
	case SFX_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 96.0f, 96.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case DELETE_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 64.0f, 64.0f, type, 0.25f};
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case NEW_GAME:
	case PLAYER_1:
	case PLAYER_2:
	case PLAYER_3: {
		GameObject * UI_Button = new Button{ x, y, 300.0f, 300.0f, type, 0.25f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case LEVEL_1_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(0) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_2_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(1) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_3_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(2) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_4_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(3) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_5_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(4) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_6_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(5) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_7_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(6) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_8_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(7) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_9_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(8) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LEVEL_10_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type, 1.0f / 12.0f };
		UI_Button->Set_Start_Texture(playdata.Get_Level_Stars(9) * 3 * 1.0f / 12.0f);
		logic_components.object_manager->Insert_Object(UI_Button);
		break;
	}
	case LOCKED_LEVEL: {
		GameObject * UI_Button = new Button{ x, y, 128.0f, 192.0f, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case LOCKED_GRANNY: {
		GameObject * UI_Button = new Button{ x, y, 60.0f, 60.0f, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case BACK_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 64.0f, 64.0f, type, 0.25f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case SHOP_BUTTON: {
		GameObject * UI_Button = new Button{ x, y, 256.0f, 64.0f, type, 0.25f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case ICON_KID: {
		GameObject * UI_Button = new GameObject{KIDS, x, y, 30.0f, 30.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case ICON_GRANNY: {
		GameObject * UI_Button = new GameObject{ GRANDMA, x, y, 30.0f, 30.0f, GENERAL, type,};
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case UI_PANEL: {
		GameObject * UI_Button = new GameObject{NONE, x, y, 1200.0f, 150.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case WAVE_BAR: {
		GameObject * UI_Button = new GameObject{NONE, x, y, 1100.0f, 34.375f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case WAVE_FILLER: {
		GameObject * UI_Button = new GameObject{NONE, x, y, 0.0f, 20.0f, DESCRIPTION, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case WAVE_FLAG_BOSS:
	case WAVE_FLAG: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 30.0f, 60.0f, DESCRIPTION, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case LEVEL_MULTIPLIER: {
		GameObject * UI_Button = new MojoButton{ x, y, 100.0f, 50.0f, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }

	case BLACK_SCREEN: {
		GameObject *black_screen_fade = new BlackScreen{ NONE, x, y, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, TYPE_BLACK_SCREEN_FADE, type };
		logic_components.object_manager->Insert_Object(black_screen_fade);
		GameObject *black_screen_tint = new BlackScreen{ NONE, x, y, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, TYPE_BLACK_SCREEN_TINT, type };
		logic_components.object_manager->Insert_Object(black_screen_tint);
	}
					   break;

	case LEVEL1_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 2160.0f, 2160.0f, BACKGROUND, type };


		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }
							break;
	case DIGIPEN_LOGO_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 1200.0f, 600.0f, BACKGROUND, type };
		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }

	case TEAM_LOGO_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 1200.0f, 600.0f, BACKGROUND, type };
		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }

	case MAIN_MENU_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 1200.0f, 600.0f, BACKGROUND, type };


		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }
							   break;

	case CREDITS_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 1200.0f, 600.0f, BACKGROUND, type };
		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }
	case UPGRADE_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 1200.0f, 600.0f, BACKGROUND, type };


		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }
	case OPTIONS_BACKGROUND: {
		//SIDES side, float x, float y, float scale, OBJECT_TYPES object_type, UNIT_TYPES unit_type, Graphics_Manager gList
		GameObject *background_image = new GameObject{ NONE, x, y, 1200.0f, 600.0f, BACKGROUND, type };


		//GameObject * gBase = new Base{ GraphicsList[type], x, y, GRANDMA };
		logic_components.object_manager->Insert_Object(background_image);
		break; }

	case G_T_SHOOTING: {
		GameObject * T_Shooting = new Single_Target{
			35,						// Health
			100,					// Cost
			0,						// Loot
			5,						// Damage
			1.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			60.0f,					// Scale/Radius of object
			60.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(T_Shooting);
		break;
	}
	case G_T_SWING: {
		GameObject * T_Swing = new AreaOfEffect{
			30,						// Health
			200,					// Cost
			0,						// Loot
			6,						// Damage
			2.5f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			60.0f,					// Scale/Radius of object
			60.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(T_Swing);
		break;
	}
	case G_T_POISON: {
		GameObject * T_Poison = new Poison{
			25,						// Health
			150,					// Cost
			0,						// Loot
			5,						// Damage
			1.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			60.0f,					// Scale/Radius of object
			60.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(T_Poison);
		break;
	}
	case G_T_SLOW: {
		GameObject * T_Slow = new SlowDown{
			30,						// Health
			150,					// Cost
			0,						// Loot
			5,						// Damage
			1.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			60.0f,					// Scale/Radius of object
			60.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(T_Slow);
		break;
	}
	case G_T_STUN: {
		GameObject * T_Stun = new AreaOfEffect{
			30,						// Health
			200,					// Cost
			0,						// Loot
			10,						// Damage
			4.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			GRANDMA,				// Which side this unit is on
			x, y,					// Spawn position
			60.0f,					// Scale/Radius of object
			60.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(T_Stun);
		break;
	}
				   //Kids Tower
	case K_T_SHOOTING: {
		GameObject * K_T_Shooting = new Single_Target{
			35,						// Health
			0,						// Cost
			30,						// Loot
			5,						// Damage
			1.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			40.0f,					// Scale/Radius of object
			40.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(K_T_Shooting);
		break;
	}
	case K_T_POISON: {
		GameObject * K_T_Poison = new Poison{
			35,						// Health
			0,						// Cost
			30,						// Loot
			5,						// Damage
			1.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			40.0f,					// Scale/Radius of object
			40.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(K_T_Poison);
		break;
	}
	case K_T_SWING: {
		GameObject * K_T_Swing = new AreaOfEffect{
			35,						// Health
			0,						// Cost
			30,						// Loot
			5,						// Damage
			1.5f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			KIDS,				// Which side this unit is on
			x, y,					// Spawn position
			40.0f,					// Scale/Radius of object
			40.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(K_T_Swing);
		break;
	}
	case K_T_SLOW: {
		GameObject * K_T_Slow = new SlowDown{
			35,						// Health
			0,					// Cost
			30,						// Loot
			5,						// Damage
			1.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			KIDS,				// Which side this unit is on
			x, y,					// Spawn position
			40.0f,					// Scale/Radius of object
			40.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(K_T_Slow);
		break;
	}
	case K_T_STUN: {
		GameObject * K_T_Stun = new AreaOfEffect{
			35,						// Health
			0,						// Cost
			30,						// Loot
			5,						// Damage
			4.0f,					// Attack speed
			90.0f,					// Range, will be added on with unit's 

			KIDS,					// Which side this unit is on
			x, y,					// Spawn position
			40.0f,					// Scale/Radius of object
			40.0f,					// Scale/Radius of object
			type					// What specific type of unit it is
		};
		logic_components.object_manager->Insert_Object(K_T_Stun);
		break;
	}


	case GENERAL_GRANNY_UPGRADE_1: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.0f);
		break; }
	case GENERAL_GRANNY_UPGRADE_2: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.1f);
		break; }
	case GENERAL_GRANNY_UPGRADE_3: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.2f);
		break; }
	case GENERAL_GRANNY_UPGRADE_4: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.3f);
		break; }
	case GENERAL_GRANNY_UPGRADE_5: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.4f);
		break; }
	case GENERAL_GRANNY_UPGRADE_6: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.5f);
		break; }
	case GENERAL_GRANNY_UPGRADE_7: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.6f);
		break; }
	case GENERAL_GRANNY_UPGRADE_8: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.7f);
		break; }
	case GENERAL_GRANNY_UPGRADE_9: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.8f);
		break; }
	case GENERAL_GRANNY_UPGRADE_10: {
		GameObject * UI_Button = new GameObject{ NONE, x, y, 100.0f, 300.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		UI_Button->Set_Start_Texture(0.9f);
		break; }
	case BUTTON_HEALTH_INCREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// TANK TIER 1
		if (x == -420.0f)
		{
			if (playdata.Get_Tank_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);
		}
		// SPEED TIER 1
		if (x == -300.0f)
		{
			if (playdata.Get_Speed_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);

		}
		// BRUISER TIER 1
		if (x == 60.0f)
		{
			if (playdata.Get_Bruiser_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);

		}
		// BUFF TIER 1
		if (x == 420.0f)
		{
			if (playdata.Get_Buff_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);
		}
		break;
	}
	case BUTTON_RANGE_INCREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// SHOOTER TIER 1
		if (x == -540.0f)
		{
			if (playdata.Get_Shooter_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);
		}
		// SLOW TIER 1	
		if (x == -60.0f)
		{
			if (playdata.Get_Slow_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);
		}
		// SASSY TIER 1
		if(x == 180.0f)
		{
			if (playdata.Get_Stun_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);
		}
		// YOGA TIER 1
		if(x == 300.0f)
		{
			if (playdata.Get_Heal_Upgrade() >= 1)
				button->Set_Active(BOUGHT);
			else if (!playdata.Get_Stars_Collected())
				button->Set_Active(LOCKED);
		}
		break;
	}
	case BUTTON_NINJA_ATTACKRATE_INCREASE: 
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button); 
		// SABOTEUR TIER 1
		if (playdata.Get_Saboteur_Upgrade() >= 1)
			button->Set_Active(BOUGHT);
		else if (!playdata.Get_Stars_Collected())
			button->Set_Active(LOCKED);
		break;
	}
	case BUTTON_MAX_CAP:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// MOJO MULTIPLIER TIER 1
		if (playdata.Get_Money_Rate_Upgrade() >= 1)
			button->Set_Active(BOUGHT);
		else if (!playdata.Get_Stars_Collected())
			button->Set_Active(LOCKED);
		break;
	}
	case BUTTON_COOKIE_ATTACKRATE_INCREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// SHOOTER TIER 2
		if (playdata.Get_Shooter_Upgrade() == 2)
			button->Set_Active(BOUGHT);
		else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Shooter_Upgrade())
			button->Set_Active(LOCKED);
		break;
	}
	case BUTTON_SPEED_INCREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// TANK TIER 2
		if (playdata.Get_Tank_Upgrade() == 2)
			button->Set_Active(BOUGHT);
		else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Tank_Upgrade())
			button->Set_Active(LOCKED);
		break;
	}
	case BUTTON_COOLDOWN_DECREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// SPEED TIER 2
		if (x == -300.0f)
		{
			if (playdata.Get_Speed_Upgrade() == 2)
				button->Set_Active(BOUGHT);
			else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Speed_Upgrade())
				button->Set_Active(LOCKED);
		}
		// SABOTEUR TIER 2
		if (x == -180.0f)
		{
			if (playdata.Get_Saboteur_Upgrade() == 2)
				button->Set_Active(BOUGHT);
			else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Saboteur_Upgrade())
				button->Set_Active(LOCKED);
		}
		break;
	}
	case BUTTON_DAMAGE_INCREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// SLOW TIER 2
		if (x == -60.0f)
		{
			if (playdata.Get_Slow_Upgrade() == 2)
				button->Set_Active(BOUGHT);
			else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Slow_Upgrade())
				button->Set_Active(LOCKED);
		}
		// BRUISER TIER 2
		if (x == 60.0f)
		{
			if (playdata.Get_Bruiser_Upgrade() == 2)
				button->Set_Active(BOUGHT);
			else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Bruiser_Upgrade())
				button->Set_Active(LOCKED);
		}
		// STUN TIER 2
		if (x == 180.0f)
		{
			if (playdata.Get_Stun_Upgrade() == 2)
				button->Set_Active(BOUGHT);
			else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Stun_Upgrade())
				button->Set_Active(LOCKED);
		}
		break;
	}
	case BUTTON_HEALING_INCREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// HEAL TIER 2
		if (playdata.Get_Heal_Upgrade() == 2)
			button->Set_Active(BOUGHT);
		else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Heal_Upgrade())
			button->Set_Active(LOCKED);
		break;
	}
	case BUTTON_RANGE_INCREASE_2:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f/6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// BUFF TIER 2
		if (playdata.Get_Buff_Upgrade() == 2)
			button->Set_Active(BOUGHT);
		else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Buff_Upgrade())
			button->Set_Active(LOCKED);
		break; 
	}
	case BUTTON_COST_DECREASE:
	{
		GameObject * UI_Button = new DescriptionButton{ x, y, 80.0f, 80.0f, type, 1.0f / 6.0f };
		logic_components.object_manager->Insert_Object(UI_Button);
		DescriptionButton* button = dynamic_cast<DescriptionButton*>(UI_Button);
		// GRANNY MOJO TIER 2
		if (playdata.Get_Money_Rate_Upgrade() == 2)
			button->Set_Active(BOUGHT);
		else if (playdata.Get_Stars_Collected() <= 1 || !playdata.Get_Money_Rate_Upgrade())
			button->Set_Active(LOCKED);
		break;
	}
	case GENERAL_STARS_LEFT: {
		GameObject * UI_Button = new GameObject{NONE, x, y, 200.0f, 50.0f, GENERAL, type };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }

	case CURSOR:
	{
		GameObject * cursor = new GameObject{ NONE, x, y, 50.0f, 50.0f, TYPE_CURSOR, type };
		logic_components.object_manager->Insert_Object(cursor);
		cursor->Set_Texture_Width(0.5f);
		break;
	}
	case HEALTH:
	{
		if (y == -205.0f)
		{
			GameObject * base_health = new GameObject{ GRANDMA, x, y, 30.0f, 30.0f, GENERAL, type };
			logic_components.object_manager->Insert_Object(base_health);
		}
		else 
		{
			GameObject * base_health = new GameObject{ KIDS, x, y, 30.0f, 30.0f, GENERAL, type };
			logic_components.object_manager->Insert_Object(base_health);
		}
		break;
	}
	case BUTTON_PAUSE: {
		GameObject * UI_Button = new Button{ x, y, 60.0f, 60.0f, type, 0.25f };
		logic_components.object_manager->Insert_Object(UI_Button);
		break; }
	case BUTTON_TIME_ADJUST: {
		GameObject * button = new Button{ x, y, 60.0f, 60.0f, type, 1.0f/6.0f };
		logic_components.object_manager->Insert_Object(button);
		break; }
							 // SPAWN TUTORIAL 0
	case TUTORIAL_SPEECH_01:
	case TUTORIAL_SPEECH_02:
	case TUTORIAL_SPEECH_03:
	case TUTORIAL_SPEECH_04:
	case TUTORIAL_SPEECH_05:
	case TUTORIAL_SPEECH_06:
	case TUTORIAL_SPEECH_07:
	case TUTORIAL_SPEECH_08:
	case TUTORIAL_SPEECH_09:
	case TUTORIAL_SPEECH_10:
	case TUTORIAL_SPEECH_11:
	case TUTORIAL_SPEECH_12:
	{
		GameObject * tutorial = new GameObject{ NONE, x, y, 400.0f, 200.0f, DESCRIPTION, type };
		tutorial->Set_Alive(false);
		logic_components.object_manager->Insert_Object(tutorial);
	}
		break;
	}
}

/******************************************************************************/
/*!
					Spawns Projectiles
*/
/******************************************************************************/

void Spawn_Projectile(UNIT_TYPES type, float x, float y, int damage, GameObject & target)
{
	logic_components.object_manager->Create_Projectile(type, x, y, damage, target);
}

/******************************************************************************/
/*!
			Spawns Particle Emitter
*/
/******************************************************************************/
void Spawn_Particle_Emitter(float x, float y, UNIT_TYPES particletype, float range, float lifetime)
{
	logic_components.object_manager->Activate_Particle_Emitter(particletype, x, y, range, lifetime);
}

/******************************************************************************/
/*!
				Create Paths
*/
/******************************************************************************/
// Creates the paths that soldiers will travel on in a level
void Create_Path(Orientation orientation, UNIT_TYPES type)
{
	Path* new_path = nullptr;
	unsigned number_of_paths = logic_components.object_manager->Get_Size_Path_List();

	// Check if this is the first path being created
	if (number_of_paths == 0)
		// Set it to not have a parent
		new_path = new Path(number_of_paths, nullptr, orientation, type);

	// Create path as per normal
	else {
		Path* parent_path = logic_components.object_manager->Get_Path(number_of_paths - 1);

		new_path = new Path(number_of_paths, parent_path, orientation, type);
	}

	// Object manager will handle destruction of this object
	logic_components.object_manager->Insert_Object(new_path);
}

/******************************************************************************/
/*!
			Create Wave indicator
*/
/******************************************************************************/
void Create_Wave_Indicator(const int max_waves) 
{
	Spawn_Object(WAVE_BAR, 0.0f, -140.0f);

	for (int i = max_waves - 1; i > 0; --i) {
		Spawn_Object(WAVE_FLAG, 65.0f + (1100.0f / max_waves * (max_waves - i)) - 600.0f, -120.0f);
	}
	Spawn_Object(WAVE_FLAG_BOSS, 60.0f + 1100.0f - 600.0f, -120.0f);
	//-541.0f
	Spawn_Object(WAVE_FILLER, -540.0f, -140.0f);
}
