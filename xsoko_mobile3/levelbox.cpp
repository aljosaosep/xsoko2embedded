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
 * Codename: xSoko
 * File: levelbox.cpp
 *
 * Summary:
 * Includes levelbox objects implementation
 *
 * Author: Aljosa Osep 2008
*/

#include "levelbox.h"
#include "level.h"

#include "stdafx.h"


namespace PacGame
{
    namespace GameClasses
    {
        namespace GameObjects
        {
            /*****************************************
             PLevelBox methods
             *****************************************/			  
            void PLevelObject::setIndex(int i, int j) // index setter
            {
                    this->i = i;
                    this->j = j;
            }

            void PLevelObject::setI(int i)  // i index setter
            {
                    this->i = i;
            }

            void PLevelObject::setJ(int j)  // j index setter
            {
                    this->j = j;
            }
            
            void PLevelObject::toogleBombActivity()
            {
                this->containsActiveBomb == false ? this->containsActiveBomb = true : this->containsActiveBomb = false;
            }

            int PLevelObject::getI() const  // i index getter
            {
                    return this->i;
            }

            int PLevelObject::getJ() const  // j index getter
            {
                    return this->j;
            }
            
            bool PLevelObject::isActiveBomb() const
            {
                return this->containsActiveBomb;
            }

            unsigned short PLevelObject::getId() const
            {
                return id;
            }

            void PLevelObject::print()
            {

			    file.open("coredump.txt", ios::out | ios::app);
                file<<this->id<<' ';
				file.close();
            }

            /*****************************************

             * MATRIX I. ELEMENTS METHODS IMPLEMENTATION
             *
             *****************************************/

            /*****************************************
             PTeleport methods
             *****************************************/
            // setters
            void PTeleport::setId(int id)
            {
                this->teleport_id = id;
            }

            void PTeleport::setChildTeleport(PTeleport *child)
            {
                this->childTeleport = child;
            }

            // getters
            int PTeleport::getId() 
            {
                return this->teleport_id;
            }

            PTeleport* PTeleport::getChildTeleport() const
            {
                return this->childTeleport;
            }

            void PTeleport::draw()
            {
                glColor4f(0.0, 0.0, 1.0, 0.4);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(TELEPORT_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);   
            }

            void PTeleport::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| T"<<this->teleport_id<<' ';
				file.close();
            }

            short PTeleport::isPlayerMovePossible()
            {
                /// tmp
                return 3;            
            }

            /*****************************************
             PFloor methods
             *****************************************/	
            void PFloor::draw()
            {
                glColor4f(1.0, 1.0, 1.0,1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(FLOOR_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
            }

            void PFloor::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"|     ";
				file.close();
            }

            short PFloor::isPlayerMovePossible() 
            {
                return 2;
            }
            /*****************************************
             POnewayFloor methods
             *****************************************/	       
            void POnewayFloor::draw()
            {
                glColor4f(1.0, 1.0, 1.0,1.0);
                switch(this->dir)
                {
                        case Aliases::left:
                            glRotatef(180.0, 0.0, 0.0, 1.0);
                            break;

                        case Aliases::up:
                            glRotatef(90.0, 0.0, 0.0, 1.0);
                            break;

                        case Aliases::down:
                            glRotatef(-90.0, 0.0, 0.0, 1.0);
                            break;
                }
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(OW_FLOOR_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
            }

            void POnewayFloor::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| OWF ";
				file.close();
            }      

            short POnewayFloor::isPlayerMovePossible() 
            {
                return 5;
            }

            Aliases::PDirection POnewayFloor::getDirection()
            {
                return this->dir;
            }

            void POnewayFloor::setDirection(Aliases::PDirection dir)
            {
                this->dir = dir;
            }

            /*****************************************
             PSolidWall methods
             *****************************************/	    
            void PSolidWall::draw()
            {
                glColor4f(0.9, 0.9, 0.9,1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(S_WALL_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PSolidWall::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| SW  ";
				file.close();
            }

            short PSolidWall::isPlayerMovePossible() 
            {
                return 0;
            }

            /*****************************************
             PUnsolidWall methods
             *****************************************/	
            void PUnsolidWall::draw()
            {
                glColor4f(0.7, 0.6, 0.6,1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(U_WALL_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PUnsolidWall::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| USW ";
				file.close();
            }  

            short PUnsolidWall::isPlayerMovePossible() 
            {
                return 0;
            }        
            /*****************************************
             PBridge methods
             *****************************************/	 
            void PBridge::draw()
            {
                glColor4f(1.0, 1.0, 1.0, 0.8);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(BRIDGE_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);

            }

            void PBridge::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"|  B  ";
				file.close();
            } 

            short PBridge::isPlayerMovePossible() 
            {
                return 2;
            }

            /*****************************************
             PVoid methods
             *****************************************/	
            void PVoid::draw() { }

            void PVoid::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"|     ";
				file.close();
            } 

            short PVoid::isPlayerMovePossible() 
            {
                return 0;
            }

            /*****************************************
             PCubeHolder methods
             *****************************************/	   
            void PCubeHolder::draw()
            {
                glColor4f(1.0, 0.4, 0.4,1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(CUBE_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
            }

            void PCubeHolder::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| CH  ";
				file.close();
            }  

            short PCubeHolder::isPlayerMovePossible() 
            {
                return 6;
            }

            /*****************************************
             * MATRIX II. ELEMENTS METHODS IMPLEMENTATION
             *
             *****************************************/
            /*****************************************
             PCube methods
             *****************************************/	  
            void PCube::draw()
            {
                glColor4f(1.0, 1.0, 1.0,1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(CUBE_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PCube::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"|  C  ";
				file.close();
            } 

            short PCube::isPlayerMovePossible() 
            {

                return 2;
            }

            /*****************************************
             POnewayCube methods
             *****************************************/	 
            void POnewayCube::draw()
            {
                glColor4f(1.0, 1.0, 1.0,1.0);
                switch(this->dir)
                {
                        case Aliases::left:
                            glRotatef(180.0, 0.0, 0.0, 1.0);
                            break;

                        case Aliases::up:
                            glRotatef(90.0, 0.0, 0.0, 1.0);
                            break;

                        case Aliases::down:
                            glRotatef(-90.0, 0.0, 0.0, 1.0);
                            break;
                }
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(OW_CUBE_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void POnewayCube::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| OWC ";
				file.close();
            } 

            short POnewayCube::isPlayerMovePossible() 
            {
                return 3;
            }

            PDirection POnewayCube::getDirection()
            {
                return this->dir;
            }

            /*****************************************
             PBomb methods
             *****************************************/	 
            void PBomb::draw()
            {
                glColor4f(1.0, 1.0, 1.0,1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(BOMB_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PBomb::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"|  B  ";
				file.close();
            } 

            short PBomb::isPlayerMovePossible() 
            {
                return 4;
            } 
            
            /*****************************************
             PDetonatedBomb methods
             *****************************************/
            void PDetonatedBomb::draw() { /* override */ }
            
            void PDetonatedBomb::print()
            {
				file.open("coredump.txt", ios::out | ios::app);
                file<<"| D_B ";
				file.close();
            }
            
            short PDetonatedBomb::isPlayerMovePossible() 
            { 
                return 0; 
            } 
        }
    }
}

