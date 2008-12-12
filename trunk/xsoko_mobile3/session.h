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
 * File:   session.h
 * Author: aljosa
 *
 * Created on July 18, 2008, 11:42 AM
 * Changed by Jernej, October 5, 2008
 * Changed by Aljosa for xSoko2embedded, December 08
 */

#ifndef __SESSION_H
#define	__SESSION_H

#include "level.h"
#include "renderer/renderer.h"
#include "input.h"
#include "gui.h"

using namespace PacGame::RenderMaschine;
using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
    namespace GameClasses
    {
        class PGameSession
        {
        private:
            PLevel *level; 
            PPlayer *player;   
            PCamera *camera;
			//PGuiEmbedded *gui;
            //unsigned score;
            
            PInputSystem *input;
            //unsigned moves;  
            //double rotations_per_tick;
     //       Window* gameWin;
            bool forceQuit;


						

        public:
			void (*displayFuncPtr)(PLevel*);
			void linkRenderFunctionPointer();
		//	static void wrapperTocallMainLoop(void *object);

            // constructors & destructor
            PGameSession(PLevel *level, PInputSystem *input);
            PGameSession();
            ~PGameSession();
            
            // methods
            bool run();
            bool initialize();
            void mainLoop(bool renderGame);
            void Quit();
            void resetLevel();
            
            // setters
            void setLevel(PLevel *level);
            void setScore(unsigned score);
            void setInput(PInputSystem *input);
            
            // getters
            PLevel *getLevel() const;
            unsigned getScore() const;
        };
    }
}



#endif	/* _SESSION_H */

