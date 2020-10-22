#include "projectile2D.h"

Projectile::Projectile()
{
	m_location = Point2D(double(0.0), double(0.0));
	m_heading = Point2D(double(0.0), double(0.0));
}

Projectile::Projectile(Point2D location, Point2D heading)
{
	m_location = location;
	m_heading = heading;
}


void Projectile::drawProjectile()
{
	m_location.x += m_heading.normalise().x * 0.1;
	m_location.y += m_heading.normalise().y * 0.1;

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_location.x, m_location.y);
	glVertex2f(m_location.x - m_heading.normalise().x * 0.1, m_location.y - m_heading.normalise().y * 0.1);
	glEnd();
}