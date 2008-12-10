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
 * File: renderer.h
 *
 * Summary:
 * Includes level renderer classes definition
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa 2008
*/

#ifndef __RENDERER_H
#define __RENDERER_H

//#include <GL/glfw.h>
#include <stdio.h>
#include <string>
#include "../CommonStructures.h"
#include "../messages.h"

using namespace PacGame::Structures;

namespace PacGame
{

  namespace RenderMaschine
  { 
    /**********************************************************
    * PRenderer
    *
    * Class for drawing stuff
    * --------------------------------------------------------
    * Aljosa 2007-2008
    * ********************************************************/
    class PRenderer
    {
    private:
        // light properties
        float lightAmbient[4];
        float lightDiffuse[4];
        float lightPosition[4];  

    public:
        // constructor
        PRenderer();

        // system functions
        bool init();
        void deinit();

        // getters
        float* getLightPosition();

        // functions that are drawing stuff
        void drawBackground();
        void drawSkyDome();
        void drawCube(float x, float y, float size);
		void drawSphere(float x, float y, float size);
        void drawFloor(float x, float y, float size);
		void drawText(float x, float y, string text);
    };
  }
}

#endif
