#include "Stunt.h"
#include "GraphicsManager.h"

Stunt::Stunt()
{

}
Stunt::Stunt(GraphicsManager list, float x, float y, UNIT_TYPES t)
{
	Set_x(x);
	Set_y(y);
	Set_Texture(list.Get_Texture());
	Set_Render_Mesh(list.Get_Render_Mesh());
	Set_CollisionMesh(list.Get_Collision_Mesh());
	Set_Object_Type(TOWER);
	Set_Unit_Type(t);
	Set_Side(NONE);
}
Stunt::~Stunt()
{

}