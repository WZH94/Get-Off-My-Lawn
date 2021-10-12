/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Soldier.cpp
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Soldier class.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Soldier.h"         // Function declarations
#include "GraphicsManager.h" // Graphics manager
#include "LevelData.h"       // Level data
#include "CombatSystem.h"    // Combat functions
#include "LogicComponents.h" // Logic components

/******************************************************************************/
/*!
Default Constructor for Soldier Class
*/
/******************************************************************************/
Soldier::Soldier()
// members initialization list
	:
	speed_{},
	category_{},
	is_stunned_{ false },
	stun_start_time_{ 0.0 },
	stun_recovery_time_{ 0.0 },
	is_poisoned_{ false },
	poison_start_time_{ 0.0 },
	poison_recovery_time_{ 0.0 },
	poison_flag_{ 0 },
	is_slowed_{ false },
	slow_start_time_{ 0.0 },
	slow_recovery_time_{ 0.0 },
	is_buffed_{ false },
	bubble_counter_{ 0.0f }
{
	Set_Texture_Change(0.125f );
	Set_Texture_Timer(0.05f);
	Set_Texture_Width(0.125f);
}

/******************************************************************************/
/*!
Constructor for Soldier Class
*/
/******************************************************************************/
Soldier::Soldier(
	float speed, SOLDIER_TYPE category,
	bool is_aoe, int health, int cost, int loot, int attack_power, float attack_rate, float range,
	SIDES side, float x, float y, float scale_x, float scale_y, OBJECT_TYPES object_type, UNIT_TYPES unit_type)

	:
	Combatant(
		is_aoe,			// Whether AOE or not
		health,			// Health
		cost,			// Cost
		loot,			// Loot
		attack_power,	// Damage
		attack_rate,	// Attack speed
		range,			// Range, will be added on with unit's radius

		side,			// Which side this unit is on
		x, y,			// Spawn position
		scale_x,			// Scale/Radius of object
		scale_y,
		object_type,	// What type of object it is
		unit_type		// What specific type of unit it is
	),
	speed_{ speed },
	category_{ category },
	is_stunned_{ false },
	stun_start_time_{ 0.0 },
	stun_recovery_time_{ 0.0 },
	is_poisoned_{ false },
	poison_start_time_{ 0.0 },
	poison_recovery_time_{ 0.0 },
	poison_flag_{ 0 },
	is_slowed_{ false },
	slow_start_time_{ 0.0 },
	slow_recovery_time_{ 0.0 },
	is_buffed_{ false },
	bubble_counter_ { 0.0f }
{
	vel_.x = speed;
	vel_.y = speed;

	// Sets the nodes it starts from depending if the unit is a grandma or kid
	if (side_ == GRANDMA)
		// If grandma set from the start
		move_target_ = logic_components.object_manager->Get_Path(1);

	else if (side_ == KIDS)
	{
		int end = logic_components.object_manager->Get_Size_Path_List();

		// If kids set from the end
		move_target_ = logic_components.object_manager->Get_Path(end - 2);
	}

}

/******************************************************************************/
/*!
Default Destructor for Soldier Class
*/
/******************************************************************************/
Soldier::~Soldier()
{
}

/******************************************************************************/
/*!
"Update" function of Soldier class
*/
/******************************************************************************/
void Soldier::Update()
{
}

/******************************************************************************/
/*!
"Draw" function of Soldier class
*/
/******************************************************************************/
void Soldier::Draw()
{
}

/******************************************************************************/
/*!
"Free" function of Soldier class
*/
/******************************************************************************/
void Soldier::Free()
{
}

/******************************************************************************/
/*!
Gets the speed of the soldier
*/
/******************************************************************************/
float const Soldier::Get_Speed() const
{
	return speed_;
}

/******************************************************************************/
/*!
Set the speed of the soldier
*/
/******************************************************************************/
void Soldier::Set_Speed(float input_speed)
{
	speed_ = input_speed;
}

/******************************************************************************/
/*!
Gets the x-directional speed
*/
/******************************************************************************/
float Soldier::Get_x_Speed() const
{
	return vel_.x;
}

/******************************************************************************/
/*!
Sets the x-directional speed
*/
/******************************************************************************/
void Soldier::Set_x_Speed(float speed)
{
	vel_.x = speed;
}

/******************************************************************************/
/*!
Gets the y-directional speed
*/
/******************************************************************************/
float Soldier::Get_y_Speed() const
{
	return vel_.y;
}

/******************************************************************************/
/*!
Sets the y-directional speed
*/
/******************************************************************************/
void Soldier::Set_y_Speed(float speed)
{
	vel_.y = speed;
}

/******************************************************************************/
/*!
Get the category of the soldier
*/
/******************************************************************************/
SOLDIER_TYPE const Soldier::Get_Category() const
{
	return category_;
}

/******************************************************************************/
/*!
Set the category of the soldier
*/
/******************************************************************************/
void Soldier::Set_Category(SOLDIER_TYPE input_category)
{
	category_ = input_category;
}

/******************************************************************************/
/*!
Gets the stun status of the soldier
*/
/******************************************************************************/
bool Soldier::Get_is_Stunned()const
{
	return is_stunned_;
}

/******************************************************************************/
/*!
Sets the stun status of the soldier
*/
/******************************************************************************/
void Soldier::Set_is_Stunned(bool status)
{
		is_stunned_ = status;
}

/******************************************************************************/
/*!
Gets the stun start time of the soldier
*/
/******************************************************************************/
double Soldier::Get_Stun_Start_Time()const
{
	return stun_start_time_;
}

/******************************************************************************/
/*!
Sets the stun start time of the soldier
*/
/******************************************************************************/
void Soldier::Set_Stun_Start_Time()
{
	stun_recovery_time_ = 0;
}

/******************************************************************************/
/*!
Gets the stun timer of the soldier
*/
/******************************************************************************/
double Soldier::Get_Stun_Recovery_Time()const
{
	return stun_recovery_time_;
}

/******************************************************************************/
/*!
Sets the stun timer of the soldier
*/
/******************************************************************************/
void Soldier::Set_Stun_Recovery_Time(double timer)
{
	stun_recovery_time_ += timer;
}

/******************************************************************************/
/*!
Gets the poison status of the soldier
*/
/******************************************************************************/
bool Soldier::Get_is_Poisoned()const
{
	return is_poisoned_;
}

/******************************************************************************/
/*!
Sets the poison status of the soldier
*/
/******************************************************************************/
void Soldier::Set_is_Poisoned(bool status)
{
	is_poisoned_ = status;
}

/******************************************************************************/
/*!
Gets the poison start time of the soldier
*/
/******************************************************************************/
double Soldier::Get_Poison_Start_Time()const
{
	return poison_start_time_;
}

/******************************************************************************/
/*!
Sets the poison start time of the soldier
*/
/******************************************************************************/
void Soldier::Set_Poison_Start_Time()
{
	poison_recovery_time_ = 0;
}

/******************************************************************************/
/*!
Gets the poison timer of the soldier
*/
/******************************************************************************/
double Soldier::Get_Poison_Recovery_Time()const
{
	return poison_recovery_time_;
}

/******************************************************************************/
/*!
Sets the poison timer of the soldier
*/
/******************************************************************************/
void Soldier::Set_Poison_Recovery_Time(double timer)
{
	poison_recovery_time_ += timer;
}

/******************************************************************************/
/*!
Gets the slow status of the soldier
*/
/******************************************************************************/
bool Soldier::Get_is_Slowed()const
{
	return is_slowed_;
}

/******************************************************************************/
/*!
Sets the slow status of the soldier
*/
/******************************************************************************/
void Soldier::Set_is_Slowed(bool status)
{
	is_slowed_ = status;
}

/******************************************************************************/
/*!
Gets the slow start time of the soldier
*/
/******************************************************************************/
double Soldier::Get_Slow_Start_Time()const
{
	return slow_start_time_;
}

/******************************************************************************/
/*!
Sets the slow start time of the soldier
*/
/******************************************************************************/
void Soldier::Set_Slow_Start_Time()
{
	slow_recovery_time_ = 0;
}

/******************************************************************************/
/*!
Gets the slow timer of the soldier
*/
/******************************************************************************/
double Soldier::Get_Slow_Recovery_Time()const
{
	return slow_recovery_time_;
}

/******************************************************************************/
/*!
Sets the slow timer of the soldier
*/
/******************************************************************************/
void Soldier::Set_Slow_Recovery_Time(double timer)
{
	slow_recovery_time_ += timer;
}

/******************************************************************************/
/*!
Gets the attack buff status of the soldier
*/
/******************************************************************************/
bool Soldier::Get_is_Buffed()const
{
	return is_buffed_;
}

/******************************************************************************/
/*!
Sets the stun status of the soldier
*/
/******************************************************************************/
void Soldier::Set_is_Buffed(bool status)
{
	is_buffed_ = status;
}


/******************************************************************************/
/*!
Gets the poison flag of the soldier
*/
/******************************************************************************/
int Soldier::Get_Poison_Flag()const
{
	return poison_flag_;
}

/******************************************************************************/
/*!
Sets the poison flag of the soldier
*/
/******************************************************************************/
void Soldier::Set_Poison_Flag(int status)
{
	poison_flag_ = status;
}

/******************************************************************************/
/*!
Gets the bubble timer counter of the soldier
*/
/******************************************************************************/
float Soldier::Get_Bubble_Counter()const
{
	return bubble_counter_;
}

/******************************************************************************/
/*!
Sets the bubble timer counter of the soldier
*/
/******************************************************************************/
void Soldier::Set_Bubble_Counter(float time)
{
	bubble_counter_ += time;
}

/******************************************************************************/
/*!
Gets the next movement node
*/
/******************************************************************************/
Path * Soldier::Get_Move_Target() const
{
	return move_target_;
}

/******************************************************************************/
/*!
Sets the next movement node
*/
/******************************************************************************/
void Soldier::Set_Move_Target(Path * target)
{
	move_target_ = target;
}

/******************************************************************************/
/*!
Handles all the status effects of the soldier
*/
/******************************************************************************/
void Soldier::Status_Updates()
{
	//Checks if the object has been stunned
	if (is_stunned_)
	{
		Recover_From_Stun(*this);
	}
	//Checks if the object has been stunned
	if (is_poisoned_)
	{
		Recover_From_Poison(*this);
	}
	//Checks if the object has been stunned
	if (is_slowed_)
	{
		Recover_From_Slow(*this);
	}
	return;
}