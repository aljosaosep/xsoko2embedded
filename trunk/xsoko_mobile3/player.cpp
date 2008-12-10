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

/* 
 * Codename: xSoko
 * File: player.cpp
 *
 * Summary:
 * Includes player methods implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 */

//#include "object.h"
//#include "player.h"

#include "stdafx.h"

namespace PacGame
{
      namespace GameClasses
      {
          namespace GameObjects
          {
              PPlayer::PPlayer(PCore *core) //  constructor
              { 
                  this->core = core;
                  this->id = 1;
                  this->bombs = 0;
              } 
              
              PPlayer::PPlayer(int i, int j, PCore *core)
              {
                   this->i = i;
                   this->j = j;
                   this->core = core;
                   this->id = 1;
                   this->bombs = 0;
              }

              // setters
              void PPlayer::setBombs(unsigned _bombs)
              {
                   bombs = _bombs;
              }

              // getters
              unsigned short PPlayer::getBombs()
              {
                   return bombs;
              }


              // etc
              void PPlayer::incBombs()
              {
                   bombs++;
              }
              
              void PPlayer::decBombs()
              {
                  this->bombs--;
              }

              // ===== FUNCTIONS TO OVERRIDE ===== //
              void PPlayer::draw() 
              {
                    glColor4f(1.0, 1.0, 1.0, 0.8);
                    glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(6));
                 //   this->core->getRenderer()->drawSphere(0.0, 0.0, 0.5);
					this->core->getRenderer()->drawCube(0.0,0.0,1.0);

              }
              
              void PPlayer::print()
              {
           //       cout<<"|_PLYR";
              }              
          }
      }
}
