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
 * File: game.h
 *
 * Summary:
 * Includes game core class definition
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 * Jernej October 5 2008
 */

#ifndef __GAME_H
#define __GAME_H

#include "messages.h"
#include "session.h"
#include "input.h"
#include "renderer/renderer.h"

using namespace PacGame::RenderMaschine;

namespace PacGame
{
	namespace GameClasses
	{
		struct lvlInfo
		{
			string name;
			int id;

			lvlInfo(string name, int id) : name(name), id(id) {}
		};



		bool gameRunning = true;
		void releaseAndQuit();
		void runLevel(string filename);
		void drawWrapper();
		void inputWrapper(int key, int x, int y);
		void menu(int entry);
		void calculatePerspective(int width, int height);
		void idle();
		int readLevelCfg(vector<lvlInfo> &lvl);
		void createMenu();
      }       
}

#endif
