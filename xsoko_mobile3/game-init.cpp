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
 * File: game-funcinit.cpp
 *
 * Summary:
 * Includes engine initialization methods implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 * Jernej Skrabec June 19 2008
 */

//#include "game.h"

#include "stdafx.h"

/*namespace PacGame
{
      namespace GameClasses
      {
		  /// Aljosa 2008
		  // it is out of class so it can be passed as parameter to glut function
		  void calculatePerspective(int width, int height)
		  {
			  glMatrixMode(GL_PROJECTION);
			  glLoadIdentity();

			  glViewport(0, 0, width, height);
			  gluPerspectivef(45.0f, 1.0f * width / height, 1.0f, 100.0f);

			  glMatrixMode(GL_MODELVIEW);
			  glLoadIdentity();
		  }

		  

          // other
          bool PGame::initGame(int &argc, char* argv[])
          {

		//	  glutReshapeFunc(calculatePerspective);
              return true;
          }
      }
}*/
