#pragma once
#ifndef GAMEENTITY2D_H
#define GAMEENTITY2D_H

#include <GL/glut.h>
#include <math.h>
#include "point2D.h"
#include "projectile2D.h"
#include "healthPickup.h"

#define DEAD	0
#define PATROL	1
#define ATTACK	2
#define EVADE	3
#define HEAL	4

class GameEntity2D
{
public:
	Point2D m_point1;		// top center
	Point2D m_point2;		// bottom left
	Point2D m_point3;		// bottom right

	double m_topSpeed;		
	double m_rotationSpeed;		
	double m_fireRate;			// millesecconds
	int m_health;
	HealthPickup* m_healthPickup;

	// constructors
	GameEntity2D(Point2D location);

	//setters and getters
	inline int getState() { return m_state; }
	inline void setState(int state) { m_state = state; }
	inline Point2D getCenter() { return m_center; }
	inline Point2D getPoint1() { return m_point1; }
	inline void setColour(float red, float green, float blue) { m_red = red, m_green = green, m_blue = blue; }
	inline void setTimer(double curTime) { m_timer = curTime; }

	void drawEntity();

	void rotateEntity(double rotationSpeed);		// player controlled
	
	void accelerate(float TopSpeed);
	void decelerate();

	void shoot();
	void drawProjectiles();
	void checkHit(GameEntity2D* target);			//checks if projectiles have hit the target
	
	void stateMachine();
	
	void updateEnemyPosition(const GameEntity2D* enemy);		//updates location of target


private:
	static const int MAX_PROJECTILES = 5;
	int m_state;

	Point2D m_center;
	Point2D m_heading;			//forward vector
	float m_angle;				// angle from 0-360 degrees

	float m_red, m_green, m_blue;		//colour of entity

	double m_acceleration;
	Point2D m_patrolTarget;

	Point2D m_EnemyPosition;
	Point2D m_EnemyHeading;

	int m_projectileCount;
	Projectile m_projectiles[MAX_PROJECTILES];		//array of projectiles			
	float m_flash;

	double m_timer;

	void calculateHeading();

	//steering behaviours
	void seek(Point2D targetPosition);										// heads directly towards target postion
	void pursue(Point2D evaderPosition, Point2D evaderHeading);				// simmilar to seek but uses target heading to lead the target
	void patrol(double xmin, double xmax, double ymin, double ymax);		// patrol within specified bounds (bounds currently hard coded in)
};

#endif // !GAMEENTITY_H