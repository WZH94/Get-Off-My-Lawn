#ifndef SHOOTING_H
#define SHOOTING_H

#include "Tower.h"

typedef class GraphicsManager GraphicsManager;
typedef enum SIDES SIDES;

class Shooting : public Tower
{
private:
	// some code
public:
	// some code
	Shooting();
	Shooting(GraphicsManager, float, float, UNIT_TYPES, SIDES);
	~Shooting();

	void Update(void);
	void Draw();
	void Free();
};
#endif SHOOTING_H
