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
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "level.h"

//#include "session.h"


#include <cstdio>
#include <cmath>

#include "stdafx.h"

namespace PacGame
{
    namespace GameClasses
    {
		PGameSession::PGameSession(PLevel *level, PInputSystem *input)
		{
			this->level = level;
			this->input = input;
			this->player = level->getPlayerHandle();
			this->camera = level->getGameCoreHandle()->getCamera();
//			this->gui = new PGuiEmbedded;
		}
        
		PGameSession::PGameSession() 
        {
			this->level = NULL;
			this->player = NULL;
			this->camera = NULL;
			this->input = NULL;  
//			this->moves = 0;
//			this->rotations_per_tick = 0.1; 
		//	this->gui = new PGuiEmbedded;
		}



/*		void PGameSession::wrapperTocallMainLoop(void *object)
		{
			PGameSession *myself = (PGameSession*)object;
			myself->mainLoop();
		} */
            
		float angle = 0.0;
        void PGameSession::mainLoop(bool renderGame)
        {
            /* the time of the previous frame
            double old_time = glfwGetTime();   

             
            while(1)
            {
                // calculate time elapsed, and the amount by which stuff rotates
         //       double current_time = glfwGetTime(),
          //      delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
                
         //     cout<<"FPS: "<<(double) frames /  old_time<<endl;
        //        this->level->processBombs(current_time);
         //       old_time = current_time;
                
                // is game over? or level done?
                if(this->level->getEndgameFlag() || forceQuit)
                    break;

            } */

		   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		   glLoadIdentity();


		   if(renderGame) // in this case, do game rendering!!!
		   {
			   gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(), 
						 this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(), 
						 this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

			   glRotatef(-180.0, 0.0, 0.0, 1.0);
			   this->level->draw();

			   if(this->level->getWonFlag())
			   {
				   MessageBox(NULL, _T("You won! :)"), _T("Congratulations!"), NULL);
				   this->level->setWonFlag(false);
				   this->resetLevel();
			   }
		   }
		   else // otherwise, do GUI
		//	   this->gui->drawMainMenu(0.0,0.0,0.5);
		   {
			   // draws all the text
			   glColor4f(1.0, 0.0,0.0,1.0);
			   glutTrueTypeString(L"Arial", 20, 2, 0, 270, L"xSoko2embedded");
			   glColor4f(0.0, 1.0,0.0,0.5);
			   glutTrueTypeString(L"Arial", 8, 2, 0, 260, L"xSoko port to ARM platform");

			   glColor4f(1.0, 1.0,1.0,1.0);
			   glutTrueTypeString(L"Arial", 10, 2, 0, 230, L"Author: Aljoša Ošep");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 215, L"Supervisor: Kimmo Salmenjoki");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 200, L"aljosa.osep@gmail.com");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 185, L"kimmo.salmenjoki@seamk.fi");

			   glutTrueTypeString(L"Arial", 10, 2, 0, 150, L"University of Applied Sciences");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 135, L"School of Technology, Seinajoki");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 120, L"Finland");

			   glutTrueTypeString(L"Arial", 10, 2, 0, 90, L"University of Maribor");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 75, L"FERI");
			   glutTrueTypeString(L"Arial", 10, 2, 0, 60, L"Slovenia");

			   glColor4f(0.0, 0.0,1.0,1.0);
			   glutTrueTypeString(L"Arial", 10, 1|4, 0, 30, L"http://code.google.com/xsoko");
			   glutTrueTypeString(L"Arial", 10, 1|4, 0, 15, L"http://code.google.com/xsoko2embedded");
		   }

		   glFlush ();
		   glutSwapBuffers();
        }
        
        void PGameSession::Quit()
		{
            forceQuit = true;
        }
        
        void PGameSession::resetLevel(){
            level->reset();
        }
        

        bool PGameSession::initialize()
        {    
			// may be obsolete xsoko2embedded
            return true;
        }
        
        bool PGameSession::run()
        {
            // first, we init level, because witohut it, there is no game
			level->initialize();
       //     if(!level->initialize())
		//	{
		//		MessageBox(NULL, _T("Error, level init failed"), _T("Error"), NULL); // WINDOWS SPECIFIC !!!
          //      return false;
		//	}
            forceQuit = false;
        //    setMainWindow(gameWin);

//            SetGameSession(this);    !!!!!!!!!1

        //    input->setGameMenuVisible(false);
            //gameWin->setVisible(false);
            // next, we initiate session

     /*       if(!this->initialize())
            {
                //Messages::initMessage("Game session", false);
                return false;
            }
            else
                //Messages::initMessage("Game session", true);*/
            


   //         this->mainLoop();  // embedded port: mainloop is now integrated into glut
            return true;
        }
        
        // setters
        // sets session's level
        void PGameSession::setLevel(PLevel *level)
        {
            this->level = level;
            this->player = level->getPlayerHandle();
            this->camera = level->getGameCoreHandle()->getCamera();
        //    level->initialize();
        }
        
        
        void PGameSession::setInput(PInputSystem *input)
        {
            this->input = input;
        }
        
        // sets session's score
   /*     void PGameSession::setScore(unsigned score)
        {
            this->score = score;
        }*/
        
     /*  void PGameSession::setGameEnd()
        {
            this->isGameRunning = false;
        }*/
        
        // getters
        // return current level
        PLevel* PGameSession::getLevel() const
        {
            return this->level;
        }
        
        // returns score
     /*   unsigned PGameSession::getScore() const
        {
            return this->score;
        }*/
        
        PGameSession::~PGameSession()
        {
        //    SetGameSession(NULL);   // !!!!!!!!
        //    delete gameWin;
        }
    }
}
