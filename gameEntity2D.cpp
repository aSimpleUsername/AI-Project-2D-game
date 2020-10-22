#include "gameEntity2D.h"

GameEntity2D::GameEntity2D(Point2D location)
    : m_acceleration(0.0), m_angle(0.0), m_state(PATROL), m_topSpeed(0.05), m_rotationSpeed(0.05),
    m_red(0.0), m_green(0.0), m_blue(0.0), m_projectileCount(0), m_flash(0.0), m_fireRate(500), 
    m_timer(0.0), m_health(100)
{
    m_center = location;
    m_point1 = Point2D(location.x + 0, location.y + 0.2);     //top of triangle
    m_point2 = Point2D(location.x - 0.1, location.y - 0.1);   //bottom left
    m_point3 = Point2D(location.x + 0.1, location.y - 0.1);   //bottom right

    m_patrolTarget = Point2D(0.0, 0.0);
}

void GameEntity2D::drawEntity()
{
    if (m_flash > 0)
    {
        glColor3f(m_red + m_flash, m_green + m_flash, m_blue + m_flash);
        m_flash = m_flash - 0.1;
    }
    else
        glColor3f(m_red + m_flash, m_green + m_flash, m_blue + m_flash);

    glBegin(GL_TRIANGLES);
    glVertex2f(m_point1.x, m_point1.y);
    glVertex2f(m_point2.x, m_point2.y);
    glVertex2f(m_point3.x, m_point3.y);
    glEnd();

}

void GameEntity2D::updateEnemyPosition(const GameEntity2D* enemy)
{
    m_EnemyPosition = enemy->m_center;
    m_EnemyHeading = enemy->m_heading;
}

void GameEntity2D::calculateHeading()
{
    // heading is the direction from the center to point one
    m_heading = m_point1 - m_center; 
}

void GameEntity2D::rotateEntity(double rotationSpeed)
{

    //point 1
    double x1 = m_point1.x - m_center.x;
    double y1 = m_point1.y - m_center.y;

    double x2 = x1 * cos(rotationSpeed) - y1 * sin(rotationSpeed);
    double y2 = x1 * sin(rotationSpeed) + y1 * cos(rotationSpeed);

    m_point1.x = x2 + m_center.x;
    m_point1.y = y2 + m_center.y;

    //point2
    x1 = m_point2.x - m_center.x;
    y1 = m_point2.y - m_center.y;

    x2 = x1 * cos(rotationSpeed) - y1 * sin(rotationSpeed);
    y2 = x1 * sin(rotationSpeed) + y1 * cos(rotationSpeed);

    m_point2.x = x2 + m_center.x;
    m_point2.y = y2 + m_center.y;

    //point3
    x1 = m_point3.x - m_center.x;
    y1 = m_point3.y - m_center.y;

    x2 = x1 * cos(rotationSpeed) - y1 * sin(rotationSpeed);
    y2 = x1 * sin(rotationSpeed) + y1 * cos(rotationSpeed);

    m_point3.x = x2 + m_center.x;
    m_point3.y = y2 + m_center.y;
    
}

void GameEntity2D::accelerate(float topSpeed)
{
    calculateHeading();
    if (topSpeed > 0 && m_acceleration < topSpeed)
        m_acceleration += 0.001;

    if (topSpeed < 0 && m_acceleration > topSpeed)
        m_acceleration -= 0.001;
    
    m_point1 = m_point1 + m_heading.normalise() * m_acceleration;
    m_point2 = m_point2 + m_heading.normalise() * m_acceleration;
    m_point3 = m_point3 + m_heading.normalise() * m_acceleration;
    m_center = m_center + m_heading.normalise() * m_acceleration;
}

void GameEntity2D::decelerate()
{
    calculateHeading();
    if (m_acceleration > 0)
        m_acceleration -= 0.001;

    if (m_acceleration < 0)
        m_acceleration += 0.001;

    m_point1 = m_point1 + m_heading.normalise() * m_acceleration;
    m_point2 = m_point2 + m_heading.normalise() * m_acceleration;
    m_point3 = m_point3 + m_heading.normalise() * m_acceleration;
    m_center = m_center + m_heading.normalise() * m_acceleration;
}

void GameEntity2D::shoot()
{
    if (m_projectileCount == MAX_PROJECTILES - 1)
        m_projectileCount = 0;

    m_projectiles[m_projectileCount].m_location = m_point1;
    m_projectiles[m_projectileCount].m_heading = m_heading;

    ++m_projectileCount;
}

void GameEntity2D::drawProjectiles()
{
    for (int i = 0; i < MAX_PROJECTILES; ++i)
        m_projectiles[i].drawProjectile();
}

void GameEntity2D::checkHit(GameEntity2D* target)
{
    for (int j = 0; j < MAX_PROJECTILES; ++j)
    {
        if (m_projectiles[j].m_location.distance(target->getCenter()) < target->getCenter().distance(target->getPoint1()))
        {
            target->m_flash = 1;
            target->m_health -= 10;
            m_projectiles[j].m_location = Point2D(0.0, 0.0);
            m_projectiles[j].m_heading = Point2D(0.0, 0.0);
        }
    }
}

void GameEntity2D::stateMachine()
{
    // Death State
    if (m_health <= 0)
        m_state = DEAD;

    // Patrol State
    if (m_state == PATROL)
    {
        patrol(-5.5, 5.5, -5.5, 5.5);
        accelerate(m_topSpeed / 2);

        if (m_center.distance(m_EnemyPosition) < 2.0)   //attack if close to enemy
            m_state = ATTACK;
      
        if (m_flash > 0)        // attack if hit
            m_state = ATTACK;
    }
    
    // Attack State
    if (m_state == ATTACK)
    {
        pursue(m_EnemyPosition, m_EnemyHeading);
        if (glutGet(GLUT_ELAPSED_TIME) > m_timer)
            shoot();

        if (m_center.distance(m_EnemyPosition) > 2.0)
            accelerate(m_topSpeed);
        else if (m_center.distance(m_EnemyPosition) < 1.5)   //back up if player gets too close
            accelerate(-m_topSpeed);
        else
            decelerate();

        if (m_health <= 20)
            m_state = HEAL;
    }
    if (glutGet(GLUT_ELAPSED_TIME) > m_timer)
        m_timer += m_fireRate;

    // Heal state
    if (m_state == HEAL)
    {
        if (m_healthPickup->m_isActive)
        {
            seek(m_healthPickup->m_location);
            accelerate(m_topSpeed);
            if (m_center.distance(m_healthPickup->m_location) < 0.15)
            {
                m_healthPickup->m_isActive = false;
                m_health += m_healthPickup->m_healValue;
                m_state = ATTACK;
            }
        }
        else
            m_state = ATTACK;
    }
}

void GameEntity2D::seek(Point2D targetPosition)
{
    Point2D newHeading = (targetPosition - m_center).normalise();

    if (m_heading.angle() > newHeading.angle())       //turn left
    {
        if (m_heading.angle() - newHeading.angle() > M_PI)        // makes it smooth if angle goes from 360 - 0 degreees
            rotateEntity(-0.075);
        else
            rotateEntity(0.075);
    }

    if (m_heading.angle() < newHeading.angle())       //turn right
    {
        if (m_heading.angle() - newHeading.angle() < -M_PI)       //  makes it smooth if angle goes from 360 - 0 degreees
            rotateEntity(0.075);
        else
            rotateEntity(-0.075);
    }
}

void GameEntity2D::pursue(Point2D evaderPosition, Point2D evaderHeading)
{
    Point2D toEvader = evaderPosition - m_center;

    double relativeHeading = m_heading.dot(evaderHeading);

    // if evader directly in front, seek normally
    // else predict offset to pursue
    if ((toEvader.dot(m_heading) > 0) && (relativeHeading < -0.95))
        seek(evaderPosition);
    else
        seek(evaderPosition + (evaderHeading * (toEvader.length() - 1.75))*5);     // -1.75 because distance enemy stays away from you, 5* to make the lead greater  
}

void GameEntity2D::patrol(double xmin, double xmax, double ymin, double ymax)
{
    if(m_patrolTarget == Point2D(0.0, 0.0) || m_center.distance(m_patrolTarget) < 0.5)
        m_patrolTarget = Point2D::randomPoint(xmin, xmax, ymin, ymax);

    seek(m_patrolTarget);
}