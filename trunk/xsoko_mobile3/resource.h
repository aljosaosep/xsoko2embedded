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
 * File:   resource.h
 * Author: aljosa
 *
 * Created on August 24, 2008, 8:41 PM
 */

#ifndef __RESOURCE_H
#define	__RESOURCE_H

#include "renderer/texture.h"

#define ELEMENTS_TEXTURES 12

using namespace PacGame::RenderMaschine;

namespace PacGame
{
    namespace GameClasses
    {
        class PResourceManager
        {
        private:
            PTexture *textures[ELEMENTS_TEXTURES];
            
        public:
            PResourceManager();
            ~PResourceManager();
            bool loadTextureResource(PTexture **res, string file);
            bool loadTextureResource(int offset, string file);
            
            PTexture* getTextureResource(int offset);
            unsigned getTextureTesourceId(int offset);

            void release();
        }; 
    }
}

#endif	/* _RESOURCE_H */
