/*
 * codename: xSoko2embedded
 * Copyright (C) Aljosa Osep 2008 <aljosa.osep@gmail.com> 
 * University of Applied Sciences, School of Technology, Seinajoki, Finland
 * Supervisor: Kimmo Salmenjoki <kimmo.salmenjoki@seamk.fi>
 *
 * based on xSoko PC game by Aljosa Osep, Jernej Skrabec, Jernej Halozan <jernej.skrabec@gmail.com>,<jernej.halozan@gmail.com>
 * 
 * xSoko2embedded project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko2embedded project is distributed in the hope that it will be useful, but
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

using namespace PacGame::GameClasses;
//using namespace PacGame::RenderMaschine;


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





	glutSpecialFunc(inputWrapper);

	glutDisplayFunc(drawWrapper);
	glutReshapeFunc(calculatePerspective);

	glutIdleFunc(idle);

	glutCreateMenu(menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Run", 2);
	glutAddMenuEntry("Reset level", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON); 

	//runLevel("string filename");

	PacGame::Messages::infoMessage("Entering main loop...");
	glutMainLoop();

	return 0;
}




