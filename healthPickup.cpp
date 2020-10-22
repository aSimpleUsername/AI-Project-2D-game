#include "healthPickup.h"

HealthPickup::HealthPickup()
	: m_isActive(false), m_location(Point2D(0.0, 0.0)), m_timerActive(false),
		m_timer(0), m_healValue(50)
{

}

void HealthPickup::drawHealthPickup()
{
	// white box
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(m_location.x - 0.1, m_location.y + 0.1);		// top left corner
	glVertex2f(m_location.x + 0.1, m_location.y + 0.1);		// top right corner
	glVertex2f(m_location.x + 0.1, m_location.y - 0.1);		// bottom right corner
	glVertex2f(m_location.x - 0.1, m_location.y - 0.1);		// bottom left corner
	glEnd();

	// green cross (vertical)
	glColor3f(0.0f, 0.8f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(m_location.x - 0.03, m_location.y + 0.1);		// top left corner
	glVertex2f(m_location.x + 0.03, m_location.y + 0.1);		// top right corner
	glVertex2f(m_location.x + 0.03, m_location.y - 0.1);		// bottom right corner
	glVertex2f(m_location.x - 0.03, m_location.y - 0.1);		// bottom left corner
	glEnd();

	// green cross(horizontal)
	glBegin(GL_POLYGON);
	glVertex2f(m_location.x - 0.1, m_location.y + 0.03);		// top left corner
	glVertex2f(m_location.x + 0.1, m_location.y + 0.03);		// top right corner
	glVertex2f(m_location.x + 0.1, m_location.y - 0.03);		// bottom right corner
	glVertex2f(m_location.x - 0.1, m_location.y - 0.03);		// bottom left corner
	glEnd();

	// black outline
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_location.x - 0.1, m_location.y + 0.1);		// top left corner
	glVertex2f(m_location.x + 0.1, m_location.y + 0.1);		// top right corner
	glVertex2f(m_location.x + 0.1, m_location.y - 0.1);		// bottom right corner
	glVertex2f(m_location.x - 0.1, m_location.y - 0.1);		// bottom left corner
	glEnd();
}
