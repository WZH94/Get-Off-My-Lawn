/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Projectiles.h
\author Wong Zhihao | Sng Zhi Ren Zachary | Tan Zhi Quan
\par    email: zhihao.wong\@digipen.edu	| z.sng\@digipen.edu | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng | zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief	
This file contains the declarations for Projectiles and their targeting.

Functions include:
Projectile()
Get_Speed
Get_x_Speed
Set_x_Speed
Get_y_Speed
Set_y_Speed
Update()
*/
/******************************************************************************/

#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "GameObject.h"

typedef class Combatant Combatant;

class Projectile : public GameObject
{
protected:

	bool active_;			// Whether projectile is active in play
	bool target_is_dead_;	// Whether target is dead or alive
	bool target_flag_;		// Whether the target's data has been saved after it has died so it does not keep reinitialising
	float speed_;			// Speed of the projectile
	int damage_;			// Damage of the projectile, taken from unit that shot it
	long long target_ID_;	// ID of the projectile's target
	AEVec2 vel_;			// Velocity of the object

	// The stats of the target, in case it dies
	struct Target_Stats
	{
		AEVec2 pos_;
		SIDES unit_side_;
		OBJECT_TYPES object_type_;
		float radius_;
	} Target_Stats;

	// Pointer to the target it is travelling to
	Combatant * target_;

	void Select_SFX();
public:

	//////////////////////////////
	//Contructors for projectiles

	// Default construct for inactive projectiles when creating level
	Projectile();
	Projectile(float x, float y, UNIT_TYPES type, SIDES side, int damage, GameObject & target);

	void Set_Active(UNIT_TYPES type, float x, float y, int damage, GameObject & target);

	void Set_Inactive();

	bool Get_Active() const;

	//Get the speed of the projectile
	float Get_Speed() const;
	void Set_Speed(float);

	//Get the x-directional speed of the projectile
	float Get_x_Speed() const;
	//Set the x-directional speed of the projectile
	void Set_x_Speed(float speed);

	//Get the y-directional speed of the projectile
	float Get_y_Speed() const;
	//Set the y-directional speed of the projectile
	void Set_y_Speed(float speed);

	// Update logic of the object
	void Update(void);
};
#endif PROJECTILES_H
