/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
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

/* 
 * File:   input.cpp
 * Author: aljosa
 *
 * Created on July 20, 2008, 5:50 PM
 * Ported to mobile platform on December 8 2008
 */

//#include "level.h"
//#include "input.h"
#include "stdafx.h"

using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
    namespace GameClasses
    {
        void PInputSystem::process(int key)
        {
			switch(key)
			{
			case GLUT_KEY_UP:
				glutIgnoreKeyRepeat(true);
				this->level->moveObject(Aliases::up, this->level->getPlayerHandle());  // move object player up
				break;

			case GLUT_KEY_DOWN:
				glutIgnoreKeyRepeat(true);
				this->level->moveObject(Aliases::down, this->level->getPlayerHandle()); // move object player down  
				break;

			case GLUT_KEY_LEFT:
				glutIgnoreKeyRepeat(true);
				this->level->moveObject(Aliases::left, this->level->getPlayerHandle()); // move object player left 
				break;

			case GLUT_KEY_RIGHT:
				glutIgnoreKeyRepeat(true);
				this->level->moveObject(Aliases::right, this->level->getPlayerHandle()); // move object player right
				break;
			}

					/*else if((glfwGetKey('D') == GLFW_PRESS) && (glfwGetKey('D') == GLFW_RELEASE))
					{
						if(this->level->getPlayerHandle()->getBombs() > 0)
						{
							if(this->level->addDroppedBomb(this->getLevel()->getPlayerHandle()->getI(), this->getLevel()->getPlayerHandle()->getJ()))
							{
						//        this->level->
								this->level->getPlayerHandle()->decBombs();
							}

						}
					  //  this->level->setDetonatedBomb()
					}*/
				
        } 
		
        
        // setters
        void PInputSystem::setLevel(PLevel *level)
        {
            this->level = level;
        }
        
        // getters
        PLevel* PInputSystem::getLevel() const
        {
            return this->level;
        }	
    }
}