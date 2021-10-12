#include "GameObject.h"

typedef class GraphicsManager GraphicsManager;

#ifndef BASE_H
#define BASE_H

class Base : public GameObject
{
private:
	int HP;				// Base HP
	Base * base;		// Memory allocation

public:
	// Default constructor
	Base::Base();
	// Constructor for initialising stats and graphics
	Base::Base(GraphicsManager list, float x, float y, SIDES side);
	~Base();
	void Update();
	void Draw();
	void Free();

	int Get_HP();
	void Set_HP(int hp);
	void Base_Damaged();
};

#endif BASE_H
