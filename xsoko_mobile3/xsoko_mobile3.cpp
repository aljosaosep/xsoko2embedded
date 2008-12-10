/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep 2008 <aljosa.osep@gmail.com>
 * 
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// xsoko_mobile3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

// using namespace std;
using namespace PacGame::GameClasses;
using namespace PacGame::RenderMaschine;

PLevel *level = new PLevel("\\Program Files\\xsoko\\data\\test.lvl");

PInputSystem *input = new PInputSystem(level);
PGameSession *session = new PGameSession(level, input);

bool gameRunning = true;



void drawWrapper()
{
	if(gameRunning)
		session->mainLoop();
}

void inputWrapper(int key, int x, int y)
{
	input->process(key);
}

void menu(int entry)
{
	switch(entry)
	{
	case 1 : 
		exit(0); 
		level->releaseLevel();
		break;

	case 2:
		gameRunning = !gameRunning;
		break;

	case 3:
		level->reset();
		break;
	}
}

void calculatePerspective(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspectivef(45.0f, 1.0f * width / height, 1.0f, 100.0f); // !!!! 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set camera
	session->getLevel()->getGameCoreHandle()->getCamera()->fitCameraToLevel(session->getLevel()->getWidth(), session->getLevel()->getHeight());
}

void runLevel(string filename)
{
}

int _tmain(int argc, char* argv[])
{
/*	char buff[50];
	LPWSTR str;
	str = GetCommandLine();
	MessageBox(NULL, GetCommandLine(), _T("ecika"), NULL);*/

	PacGame::Messages::mainTitleMessage();

	glutInit(&argc, argv);
	PacGame::Messages::initMessage("GLUT", true);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	PacGame::Messages::initMessage("display mode", true);

	glutInitWindowSize(800, 600);                     // !!!
	glutCreateWindow("xsoko2embedded");
	PacGame::Messages::initMessage("window", true);

	if(!level->initialize())
	{
		MessageBox(NULL, _T("Level loading failed. Level data or texture missing or corrupt. Exiting..."), _T("Error"), NULL);
	//	level->releaseLevel();
		exit(0);
	}



	glutSpecialFunc(inputWrapper);

	glutDisplayFunc(drawWrapper);
	glutReshapeFunc(calculatePerspective);

	glutCreateMenu(menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Run", 2);
	glutAddMenuEntry("Reset level", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON); 

	PacGame::Messages::infoMessage("Entering main loop...");
	glutMainLoop();

	return 0;
}




