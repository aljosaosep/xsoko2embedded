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
 * File: commonStructures.h
 *
 * Summary:
 * contains functions and structures, that aren't file-specific
 * e.g generic stuff
 *
 * Author: Aljosa Osep 2007-2008
 * Modified:
*/

#ifndef __COMMON_STRUCTURES_H
#define __COMMON_STRUCTURES_H

//#include <GL/glfw.h>
#include <sstream>

using namespace std;

namespace PacGame
{
      namespace Aliases
      {
          enum PDirection
          {
              left, right, up, down
          };
      }

      namespace Structures
      {
          // structure used to describe bomb state, when bomb is dropped
          struct PDroppedBomb
          {
              double dropTime;  // time bomb has been dropped
              int i, j;  // index of bomb

	///		  !!!!!!!!! TODO
        //      PDroppedBomb(int i, int j) : dropTime(glfwGetTime()), i(i), j(j) {}  // constructor
          };

      }
      
      namespace Functions
      {
       
      }
}

#endif
