#include "userInterface.h"

void UserInterface::playerHealth(int playerHealth)
{
    if (playerHealth < 0)       //prevents health going into negatives after death
        playerHealth = 0;

    std::string string = "Health: " + std::to_string(playerHealth);
    renderText(10, 10, GLUT_BITMAP_HELVETICA_18, string);
}

void UserInterface::level(int level)
{
    std::string string = "Level: " + std::to_string(level);
    renderText(320, 675, GLUT_BITMAP_TIMES_ROMAN_24, string);
}

void UserInterface::remainingEnemies(int numEnemies)
{
    std::string string = "Enemies remaining: " + std::to_string(numEnemies);
    renderText(270, 660, GLUT_BITMAP_9_BY_15, string);
}

void UserInterface::info()
{
    std::string string[] = { "SHOOT: Space Bar", "MOVE:  Arrow keys", "RESET:  'R'" };

    for (int i = 0; i < 3; ++i)
        renderText(580, 35 - i * 15, GLUT_BITMAP_HELVETICA_12, string[i]);
}

void UserInterface::deathScreen()
{
    std::string string1 = "DEFEAT";
    std::string string2 = "PRESS 'R' TO RESTART LEVEL";
    std::string string3 = "TIP:";
    std::string string4[] = {"Enemies will only attack if you get too close or attack" , "them first so try picking them off one at a time."};

    renderText(305, 420, GLUT_BITMAP_TIMES_ROMAN_24, string1);      // DEFEAT
    renderText(260, 400, GLUT_BITMAP_HELVETICA_12, string2);        // Press 'R' to restart level
    renderText(344, 355, GLUT_BITMAP_HELVETICA_10, string3);        // TIP:
    
    for (int i = 0; i < 2; ++i)
        renderText(245, 340 - i * 15, GLUT_BITMAP_HELVETICA_10, string4[i]);
}

void UserInterface::renderText(float x, float y, void* font, std::string string)
{
    // Switch to window coordinates to render
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);

    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2i(x, y);  // or wherever in window coordinates
    for (int i = 0; i < string.size(); ++i) {
        glutBitmapCharacter(font, string[i]);
    }

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}