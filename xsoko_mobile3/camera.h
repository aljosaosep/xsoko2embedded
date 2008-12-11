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
 * File:   camera.h
 * Author: aljosa
 *
 * Created on September 7, 2008, 4:34 PM
 *
 * Inspired by camera tutorial by Allen Sherrod
 * www.UltimateGameProgramming.com
 */

#ifndef __CAMERA_H
#define	__CAMERA_H

#include <cmath>
#include "vector.h"

#define UP 0.1
#define DOWN -0.1
#define LEFT 0.1
#define RIGHT -0.1


namespace PacGame
{
    namespace GameClasses
    {
        class PCamera
        {
        private:
			float cameraRotateValue;

        public:
            void setCamera(PVector3D view, PVector3D position, PVector3D up);
            void moveCamera(float direction);
            void rotateCamera(float angle, PVector3D speed);
            void fitCameraToLevel(int width, int height);

			void setRotateValue(float val);
			float getRotateValue();

			void rotateViewX(float val);
			void rotateViewY(float val);
            
            PVector3D position;
            PVector3D view;
            PVector3D up;
        };
        
    }
}



#endif	/* _CAMERA_H */

