#pragma once

#include <GL/glut.h>

#include <vector>
#include "point2D.h"

class Projectile
{
public:

	Point2D m_location;
	Point2D m_heading;

	Projectile();
	Projectile(Point2D location, Point2D heading);
	void drawProjectile();
};

