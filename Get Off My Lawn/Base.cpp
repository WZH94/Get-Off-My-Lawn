#include "Base.h"
#include "GraphicsManager.h"
#include "RenderManager.h"
#include "ObjectList.h"

// Default constructor
Base::Base()
{

}

// Constructor for initialising stats and graphics
Base::Base(GraphicsManager list, float x, float y, SIDES side)
	:
	GameObject(side, x, y, 200.0f, BASE, G_BASE),
	HP {20}
{
}

// Default destructor
Base::~Base()
{

}

void Base::Update()
{

}

void Base::Draw()
{
	Render_Object(*this);
}

int Base::Get_HP()
{
	return HP;
}

void Base::Set_HP(int hp)
{
	HP = hp;
}

void Base::Base_Damaged()
{
	--HP;
}

void Base::Free()
{
	delete base;
}