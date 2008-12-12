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

/* 
 * Codename: xSoko
 * File: game.cpp
 *
 * Summary:
 * Includes game core implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 */

//#include "game.h"
#include "stdafx.h"


namespace PacGame
{
	namespace GameClasses
	{
		PLevel *level=NULL;//("\\Program Files\\xsoko\\data\\test.lvl");

		PInputSystem *input=NULL;// = new PInputSystem(level);
		PGameSession *session=new PGameSession; //= new PGameSession(level, input);


		vector<lvlInfo> levels;
		int levelNum = 0;

		int readLevelCfg(vector<lvlInfo> &lvl)
		{
			int lvlCnt=0;

			fstream lvlCfg;
			lvlCfg.open("\\Program Files\\xsoko\\data\\levels.cfg", ios::in);

			if(!lvlCfg.is_open())
			{
				//Messages::errorMessage("Level config missing! You can't play game without it. Exiting...");
				releaseAndQuit();
			}

			string line;

			while(!lvlCfg.eof())
			{
		
				getline(lvlCfg, line);
				//Messages::infoMessage(line);
				lvl.push_back(lvlInfo(line, 4+lvlCnt));
				lvlCnt ++;
			}

			return lvlCnt;
		}



		void releaseAndQuit()

		{	
			if(level!=NULL)
			{
				level->releaseLevel();

				if(level->getGameCoreHandle() != NULL)
				{
					level->getGameCoreHandle()->release();
					delete level->getGameCoreHandle();
				}

			//	delete level;   // do something with that!
			}

			if(input!=NULL)
				delete input;

			if(session!=NULL)
				delete session;

			exit(0); 

		}

		void runLevel(string filename)
		{
			PLevel *oldLevelPtr=NULL;
			if(level != NULL)
			{
				level->releaseLevel();
				oldLevelPtr = level;
		//		delete level;          /// !!!!
		//		level = NULL;
			}
			
			level = new PLevel("\\Program Files\\xsoko\\data\\"+filename);

			if(input == NULL)
				input = new PInputSystem(level);
			else
				input->setLevel(level);

	/*		if(session == NULL)
				session = new PGameSession(level, input);
			else
			{*/
				session->setInput(input);
				session->setLevel(level);


		//	}

			if(!level->initialize())
			{
				MessageBox(NULL, _T("Level loading failed. Level data or texture missing or corrupt. Exiting..."), _T("Error"), NULL);
				releaseAndQuit();
				exit(0);
			}

			session->getLevel()->getGameCoreHandle()->getCamera()->fitCameraToLevel(session->getLevel()->getWidth(), session->getLevel()->getHeight());

				/*if(oldLevelPtr!=NULL)
				{
					delete oldLevelPtr;
					oldLevelPtr = NULL;
				}*/                        // ---> analyse that !!!!
		}

		void drawWrapper()
		{
			if(level!=NULL)  // we have level?
				session->mainLoop(true); // yes - call session mainLoop with doGame=true
			else
				session->mainLoop(false); // otherwise, tell mainLoop to draw just a GUI
		}

		void inputWrapper(int key, int x, int y)
		{
			if(input!=NULL)
				input->process(key);
		}


		void optionsMenuCb(int entry)
		{
			//readLevelCfg(levels);
			switch(entry)
			{
			case 1 : 
				releaseAndQuit();
				break;

			case 2:
				//gameRunning = !gameRunning;
				if(level != NULL)
					level->reset();
				break;

		//	case 3:
		//		level->reset();
		//		break;
			}
		}

		void levelsMenuCb(int entry)
		{
			runLevel(levels[entry-4].name);
		}

		void createMenu()
		{
			int levelsMenu;
			levelNum = readLevelCfg(levels);

			levelsMenu = glutCreateMenu(levelsMenuCb);
			for(int i=0; i<levelNum; i++)
				glutAddMenuEntry(levels[i].name.c_str(), levels[i].id);

			glutCreateMenu(optionsMenuCb);

			glutAddSubMenu("Levels", levelsMenu);
			glutAddMenuEntry("Reset level", 2);
			glutAddMenuEntry("Quit", 1);

			glutAttachMenu(GLUT_LEFT_BUTTON); 
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

		void idle()
		{
			glutPostRedisplay();
		}
	}
}

