#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>

#include "gameEntity2D.h"
#include "healthPickup.h"
#include "userInterface.h"

bool* specialKeyStates = new bool[256];     // doing key presses this way allows multiple presses at once
std::vector<GameEntity2D*> enemies;
int max_enemies = 2;

GameEntity2D player(Point2D(0.0, -3.0));
HealthPickup health;
UserInterface ui;


void changeSize(int w, int h)
{
    // Prevent a divide by zero when window is too short
    // you can't make a window of zero width
    if(h==0)
        h = 1;
    float ratio = 1.0 * (w/h);
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset Matrix
    glLoadIdentity();
    // Set the viewport to ve the entire window
    glViewport(0, 0, w, h);
    // Set the correct perspective
    gluPerspective(45, ratio, 1, 1000);

    // Get back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

//runs the program at 60fps on all systems
void timerCallback(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timerCallback, 1);
}

void myInit(void)
{
    glClearColor(0.7, 0.7, 0.7, 1.0);       //draw on grey background

    glMatrixMode(GL_PROJECTION);        //switch matrix to projection mode
    glLoadIdentity();       //load identity matrix as the projection matrix

    //set up an orthographic projection in 2D with a clipping rectangle
    //which has its lower left corner at the origin 0.0,0.0)
    gluOrtho2D(0.0, 700.0, 0.0, 700.0);

    glMatrixMode(GL_MODELVIEW);     //switch matrix mode back to "model view"

    glutTimerFunc(1000 / 60, timerCallback, 1);
}

void initKeyStates()
{
    for (int i = 0; i < 256; i++)
        specialKeyStates[i] = false;
}

void initEntities(void)
{   
    player.m_health = 100;

    for (int i = 0; i < max_enemies; ++i)
    {
        enemies.push_back(new GameEntity2D(Point2D::randomPoint(-5, 5, 0, 5)));
        enemies[i]->setTimer(glutGet(GLUT_ELAPSED_TIME));
        enemies[i]->m_healthPickup = &health;       // every entity has the adress to the same health info
        enemies[i]->m_topSpeed = 0.03f;
        enemies[i]->m_fireRate = 750 + (50 * i);    // slightly different fire rate makes game more interesting
        enemies[i]->m_health = 50;                  // 5 hits to kill
    }

    health.m_isActive = false;
}

void processNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)   //escape
    {
        for (int i = 0; i < enemies.size(); ++i)
            delete enemies[i];
        exit(0);
    }

    if (key == ' ')  //space
        player.shoot();  

    if (key == 'r' || key == 'R')       //reset
    {
        for (int i = 0; i < enemies.size(); ++i)
            delete enemies[i];
        enemies.clear();
        initEntities();
    }
}

void specialKeyPressed(int key, int x, int y)
{
    specialKeyStates[key] = true;       // set current state to pressed
}

void specialKeyUp(int key, int x, int y)
{
    specialKeyStates[key] = false;      // set current state to up
}

void processSpecialKeys()
{
    if(specialKeyStates[GLUT_KEY_UP])
        player.accelerate(player.m_topSpeed);

    if (specialKeyStates[GLUT_KEY_DOWN])
        player.accelerate(-player.m_topSpeed);

    if (!specialKeyStates[GLUT_KEY_UP] && !specialKeyStates[GLUT_KEY_DOWN])
        player.decelerate();

    if (specialKeyStates[GLUT_KEY_LEFT])
        player.rotateEntity(player.m_rotationSpeed);

    if (specialKeyStates[GLUT_KEY_RIGHT])
        player.rotateEntity(-player.m_rotationSpeed);
}


// if health is not active, sets timer for 5 secconds before re activating
void drawHealth(void)
{
    if (health.m_isActive)
    {
        health.drawHealthPickup();
    }
    else if (health.m_timerActive)
    {
        if (glutGet(GLUT_ELAPSED_TIME) > health.m_timer)
        {
            health.m_location = Point2D::randomPoint(-5, 5, -5, 5);
            health.m_isActive = true;
            health.m_timerActive = false;
        }
    }
    else
    {
        health.m_timer = glutGet(GLUT_ELAPSED_TIME) + 5000;
        health.m_timerActive = true;
    }
}

void drawPlayer(void)
{
    if (player.m_health > 0)
    {
        player.drawEntity();
        player.drawProjectiles();

        if (player.getCenter().distance(health.m_location) < 0.15 && health.m_isActive)
        {
            health.m_isActive = false;
            player.m_health += health.m_healValue;
        }
    }
}

void drawEnemies(void)
{
    for (int i = 0; i < enemies.size(); ++i)
    {
        enemies[i]->updateEnemyPosition(&player);

        enemies[i]->stateMachine();
        enemies[i]->setColour(0.7, 0.0f, 0.0f);
        enemies[i]->drawEntity();
        enemies[i]->drawProjectiles();
    }
}

void drawUserInterface(void)
{
    ui.playerHealth(player.m_health);
    ui.level(max_enemies / 2);
    ui.remainingEnemies(enemies.size());
    ui.info();

    if (player.m_health <= 0)
        ui.deathScreen();
}

void hitRegistration(void)
{
    for (int i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i]->getState() == DEAD)
            enemies.erase(enemies.begin() + i);
        else
        {
            if (player.m_health > 0)
                player.checkHit(enemies[i]);

            enemies[i]->checkHit(&player);
        }
    }
}

void renderScene(void)
{

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(0.0f, 0.0f, 15.0f,        //issue with gluortho2D so this is how I'm setting scale of game
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0, 0.0f);

    drawHealth();

    if (player.m_health > 0)
    {
        processSpecialKeys();
        drawPlayer();
    }

    if (!enemies.empty())
    {
        drawEnemies();
        hitRegistration();
    }
    else
    {
        max_enemies += 2;
        initEntities();
    }

    drawUserInterface();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100,100);
    glutCreateWindow("AI project"); 
    glutReshapeFunc(changeSize);
    
    myInit();
    initEntities();

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);    // reshapes with the window to avoid distortion

    // Interaction
    initKeyStates();
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyUp);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
