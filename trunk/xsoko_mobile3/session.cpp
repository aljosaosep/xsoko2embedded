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
    /*    PGameSession::PGameSession(PLevel *level, PInputSystem *input) : level(level), camera(level->getGameCoreHandle()->getCamera()), input(input), moves(0),  rotations_per_tick(0.1), gameWin(createGameMenu())
        {}*/

	//	PGameSession::PGameSession(PLevel *level, PInputSystem *input) : level(level), camera(level->getGameCoreHandle()->getCamera()), input(input), moves(0),  rotations_per_tick(0.1)
     //   {}

		PGameSession::PGameSession(PLevel *level, PInputSystem *input)
		{
			this->level = level;
			this->input = input;
			this->player = level->getPlayerHandle();
			this->camera = level->getGameCoreHandle()->getCamera();
		}
        
     /*   PGameSession::PGameSession() : level(NULL), player(NULL), camera(NULL), input(NULL),  moves(0),rotations_per_tick(0.1), gameWin(createGameMenu())
        {}*/



/*		void PGameSession::wrapperTocallMainLoop(void *object)
		{
			PGameSession *myself = (PGameSession*)object;
			myself->mainLoop();
		} */
            
		float angle = 0.0;
        void PGameSession::mainLoop()
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

		//   this->camera->fitCameraToLevel(this->level->getWidth(), this->level->getHeight());

		   gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(), 
                     this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(), 
                     this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

		   glRotatef(-180.0, 0.0, 0.0, 1.0);
           this->level->draw();

		   if(this->level->getWonFlag())
		   {
			   MessageBox(NULL, _T("You won! :)"), _T("Congradulations!"), NULL);
			   this->level->setWonFlag(false);
			   this->resetLevel();
		   }

		//   this->level->getGameCoreHandle()->getRenderer()->drawText(0.0,0.0, "howdy!!!!!!");

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
                Messages::initMessage("Game session", false);
                return false;
            }
            else
                Messages::initMessage("Game session", true);*/
            


   //         this->mainLoop();  // embedded port: mainloop is now integrated into glut
            return true;
        }
        
        // setters
        // sets session's level
   /*     void PGameSession::setLevel(PLevel *level)
        {
            this->level = level;
            this->player = level->getPlayerHandle();
            this->camera = level->getGameCoreHandle()->getCamera();
        //    level->initialize();
        }*/
        
        
        void PGameSession::setInput(PInputSystem *input)
        {
            this->input = input;
        }
        
        // sets session's score
        void PGameSession::setScore(unsigned score)
        {
            this->score = score;
        }
        
     /*   void PGameSession::setGameEnd()
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
        unsigned PGameSession::getScore() const
        {
            return this->score;
        }
        
        PGameSession::~PGameSession()
        {
        //    SetGameSession(NULL);   // !!!!!!!!
        //    delete gameWin;
        }
        
     /*   PGuiSession::PGuiSession(int width, int height){
            initSuccess = false;
            if(InitGUI("data/GUI.tga","data/font.tga")){
                canQuit = false;
                setCallBacks();
                SetGuiSession(this);
                levelSession.setInput(&input);
                //glfwDisable(GLFW_MOUSE_CURSOR);
                glResizeWnd(width,height);
                
                mainWin = createMainMenu();
                setMainWindow(mainWin);
                
                initSuccess = true;
            }
        }
        
        bool PGuiSession::run(){
            if(!initSuccess)
                return false;
            
            double lastTime = glfwGetTime();
            int fps = 0;
            while(!canQuit){
                if(glfwGetTime()-lastTime>=1){
                    cout << "FPS: " << fps << endl;
                    fps = 0;
                    lastTime = glfwGetTime();
                } else
                    fps++;
                // clear the buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity();
                glTranslatef(0, 0, -4);
                // draw the figure
                RenderGUI();
                glfwSwapBuffers();
            }
            return true;
        }
        
        void PGuiSession::setCallBacks(){
            glfwSetMouseButtonCallback(onMouseClick);
            glfwSetMousePosCallback(onMouseMove);
            glfwSetWindowSizeCallback(glResizeWnd);
        }
        
        void PGuiSession::removeCallBacks(){
            glfwSetMouseButtonCallback(NULL);
            glfwSetMousePosCallback(NULL);
            glfwSetWindowSizeCallback(NULL);
        }
        
        void PGuiSession::Quit(){
            canQuit = true;
        }
        
        void PGuiSession::LoadLevel(string levelPath){
            //removeCallBacks();
            
            //move to better place
            glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
            glLoadIdentity();                                                         // Reset The Projection Matrix
            // Calculate The Aspect Ratio Of The Window
            gluPerspective(45.0f,640.0f/480,0.1f,100.0f);
            glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
            glLoadIdentity();
            
            PLevel level(levelPath);
            // input object
            input.setLevel(&level);
            // make session
            levelSession.setLevel(&level);
            levelSession.run();
            
            setMainWindow(mainWin);            
            //setCallBacks();
        }
        
        Window* PGuiSession::getMainWindow(){
            return mainWin;
        }
        
        PGuiSession::~PGuiSession(){
            SetGuiSession(NULL);
            DestroyGUI();
            removeCallBacks();
            glfwEnable(GLFW_MOUSE_CURSOR);
            delete mainWin;
        }*/
    }
}
