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
 * File: messages.cpp
 *
 * Summary:
 * Includes message function implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Jernej Haložan 2008
 * Aljosa 2008
*/


#include "stdafx.h"

#include "messages.h"            
namespace PacGame
{
    namespace Messages 
    {
		fstream file;
        /*******************************************
         * initMessage()
         * set isSucces true, if initialization went ok
         * otherwise false
         * text desribes what are you initialising
         *******************************************/
        void initMessage(string text, bool isSuccess)
        {

			file.open("coredump.txt", ios::out | ios::app);
            isSuccess ? file<<"Initializing "<<text<<" ........... OK"<<endl : file<<"Initializing "<<text<<" ........... FAILED"<<endl;
			file.close();
        }

         /*******************************************
          * errorMesage()
          * If cause is known, pass error desc. 
          *******************************************/
        void errorMessage(string text) 
        {
			file.open("coredump.txt", ios::out | ios::app);
            file<<"Error: "<<text<<endl;
			file.close();
        }

         /*******************************************
         * errorIndexOutOfRange()
         * if it comes to index out of range error
         *******************************************/
        void errorIndexOutOfRange() 
        {
			file.open("coredump.txt", ios::out | ios::app);
            file<<"Error: index out of range!"<<endl;
			file.close();
        }

         /*******************************************
         * errorUnknown()
         * if cause in unknown, there is no description 
         * needed.
         *******************************************/
        void errorUnknown() 
        {
			file.open("coredump.txt", ios::out | ios::app);
            file<<"Error: unknown!"<<endl;
			file.close();
        }

         /*******************************************
         * infoMessage()
         * informs engine state about something
         * for debugging purposes
         *******************************************/
        void infoMessage(string text) 
        {
			file.open("coredump.txt", ios::out | ios::app);
            file<<"Info: "<<text<<endl;
			file.close();
        }

         /*******************************************
         * infoTexture()
         * informs that texture was loaded.
         *******************************************/
        void infoTexture(string text) 
        {
			file.open("coredump.txt", ios::out | ios::app);
            file<<"Info: Tga file "<<text<<" was successfully loaded."<<endl;
			file.close();
        }

         /*******************************************
         * mainTitleMessage()
         * fancy stuff :D
         *******************************************/
        void mainTitleMessage() 
        {
			file.open("coredump.txt", ios::out | ios::app);
            file<<"======================================"<<endl;
            file<<"==        CODENAME: xSoko mobile    =="<<endl;
            file<<"==          Text output             =="<<endl;
            file<<"======================================"<<endl;
            file<<endl;
			file.close();
        }
    }
}
