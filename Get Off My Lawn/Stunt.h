#include "Tower.h"

#ifndef STUNT_H
#define STUNT_H

class Stunt : public Tower
{
private:
	// some code
public:
	// some code
	Stunt();
	Stunt(GraphicsManager list, float x, float y, UNIT_TYPES t);
	~Stunt();
};
#endif STUNT_H
