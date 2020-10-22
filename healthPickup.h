#pragma once

#include <GL/glut.h>
#include "point2D.h"


class HealthPickup
{
public:
	const int m_healValue;		// how much the health pack heals
	bool m_isActive;			// if the health pack is available
	bool m_timerActive;			// if the timer has been started

	Point2D m_location;
	double m_timer;

	HealthPickup();
	void drawHealthPickup();	
};

