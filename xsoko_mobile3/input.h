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
 * File:   input.h
 * Author: aljosa
 *
 * Input class; provides interface for interaction
 * with input devices
 *
 * Created on July 20, 2008, 5:50 PM
 */

#ifndef __INPUT_H
#define	__INPUT_H

#include "level.h"

using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
    namespace GameClasses
    {
        class PInputSystem
        {
        private: 
            PLevel *level;    // level object
       //     bool visible;
            
        public:
            
            // constructors
            PInputSystem(PLevel *level) : level(level) { }
            PInputSystem() : level(NULL) { }
            
            // process function
            void process(int key);
            
            // setters
            void setLevel(PLevel *level);
            
            // getters
            PLevel* getLevel() const;
        }; 
    }
}

#endif	/* _INPUT_H */

