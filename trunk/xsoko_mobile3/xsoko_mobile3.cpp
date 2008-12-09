// xsoko_mobile3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

// using namespace std;
using namespace PacGame::GameClasses;
using namespace PacGame::RenderMaschine;

PLevel *level = new PLevel("test.lvl");
PInputSystem *input = new PInputSystem(level);
PGameSession *session = new PGameSession(level, input);



void drawWrapper()
{
	session->mainLoop();
}

void inputWrapper(int key, int x, int y)
{
	input->process(key);
}

void calculatePerspective(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspectivef(45.0f, 1.0f * width / height, 1.0f, 100.0f); // !!!! 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int _tmain(int argc, char* argv[])
{

//	session->initialize();
    // game and window creation
    PGame pacgame(800, 600, "xSoko project");
 
    // game initialization
 /*   if(!pacgame.initGame(argc, argv))
    {
        PacGame::Messages::initMessage("game", false); 
        return -1;
    }*/

	PacGame::Messages::mainTitleMessage();



	glutInit(&argc, argv);
	PacGame::Messages::initMessage("GLUT", true);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	PacGame::Messages::initMessage("display mode", true);

	glutInitWindowSize(800, 600);                     // !!!
	glutCreateWindow("xsoko2embedded");
	PacGame::Messages::initMessage("window", true);



	level->initialize();
//	session->initialize();

	// run game
 //   pacgame.run();

	glutSpecialFunc(inputWrapper);

	glutDisplayFunc(drawWrapper);
	glutReshapeFunc(calculatePerspective);

	PacGame::Messages::infoMessage("Entering main loop...");
	glutMainLoop();


    



//	session->run();
    
    //delete guiSession;

	return 0;
}




