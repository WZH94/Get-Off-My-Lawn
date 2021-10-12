#include "Shooting.h"
#include "GraphicsManager.h"
#include "Players.h"
#include "ObjectManager.h"
#include "CombatSystem.h"
#include "ObjectManager.h"
#include "Soldier.h"
#include "Collision.h"
#include "RenderManager.h"

Shooting::Shooting()
{

}

Shooting::Shooting(GraphicsManager gList, float x, float y, UNIT_TYPES type, SIDES side)
	: Tower(GraphicsList[type], x, y, type)
{
	Reset_Cooldown();

	Set_Cost(100);
	Set_Health(50);
	Set_Attack_Rate(1.0f);
	Set_Attack_Power(5);
	Set_Attack_Cooldown(0);
	Set_Range(50.0f);
	Set_Tower_Type(SINGLE_TARGET);

	Set_Object_Type(TOWER);
	Set_Side(side);
	Set_Radius(20.0f);
}
Shooting::~Shooting()
{

}

void Shooting::Update(void)
{
	// Check if object has died
	if (Get_Health() <= 0)
	{
		if (this->Get_Side() == KIDS)
			players.Lunch_Money_Gain(loot_);

		Death_List.push_back(this);
	}

	else
	{
		// Checks if there are any units in range that it can attack
		GameObject * checkEnemy;

		checkEnemy = Check_Nearest(*this, this->Get_Range(), SOLDIER);
		if (checkEnemy)
		{
			// Check if unit is ready to attack
			if (Cooldown_Is_Ready(*this))
			{
				Soldier * enemy_target = dynamic_cast <Soldier *>(checkEnemy);

				Damage(*enemy_target, Get_Attack_Power());

				// Resets the attacker's cooldown to 0s
				Set_Attack_Cooldown(0);
				// Resets the attacker's start time in system seconds
				Set_Cooldown_Start_Time();
			}

			// Not ready to attack, advance cooldown
			else Advance_Cooldown(*this);
		}

		else
		{
			// Advances cooldown even if it is not attacking anything
			if (!Cooldown_Is_Ready(*this))
				Advance_Cooldown(*this);
		}
	}
}

void Shooting::Draw()
{
	Render_Object(*this);
}

void Shooting::Free()
{

}
