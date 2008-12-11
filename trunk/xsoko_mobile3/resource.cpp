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

#include "resource.h"

#include "stdafx.h"


namespace PacGame
{
    namespace GameClasses
    {
        /******************************
         * PTextureManager resources
         *****************************/
        PResourceManager::PResourceManager()
        {
            for(int i=0; i<ELEMENTS_TEXTURES; textures[i++]=NULL); 
        }
        
        PResourceManager::~PResourceManager()
        {
            this->release();
        }
        
        bool PResourceManager::loadTextureResource(PTexture **res, string file)
        {
            *res = new PTexture(file);
            
            if(!(*res)->makeTgaTexture(false))
       //     if(!(*res)->load())
            {
                cout<<"Error loading "<<(*res)->getFilename()<<endl;  // failed
                (*res)->release();
                delete [] (*res);
                (*res) = NULL;
                return false;
            }
            
            return true;
        }
        
        bool PResourceManager::loadTextureResource(int offset, string file)
        {
            textures[offset] = new PTexture(file);
            if(!((textures[offset])->makeTgaTexture(false)))
            {
                cout<<"Error loading "<<textures[offset]->getFilename()<<endl;  // failed
                (textures[offset])->release();
                delete [] textures[offset];
                textures[offset] = NULL;
                return false;
            }

            return true;
        }
        
        // getters
        PTexture* PResourceManager::getTextureResource(int offset)
        {
            return this->textures[offset];
        }
        
        unsigned PResourceManager::getTextureTesourceId(int offset)
        {
            return this->textures[offset]->getId();
        }
        
        void PResourceManager::release()
        {
            // release textures
            for(int i=0; i<ELEMENTS_TEXTURES; i++)
            {
                if(this->textures[i]!=NULL)
                {
					
                    textures[i]->release();
                    delete textures[i];
                    textures[i] = NULL;
                }
            }
        }
    }
}
