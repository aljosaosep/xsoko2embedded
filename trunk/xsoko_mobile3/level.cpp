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
 * Codename: xSoko
 * File: level.h
 *
 * Summary:
 * Includes level class implementation, abstratct grid element imp., and
 * several others level struct classes implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Aljosa 2008
 */



//#include "object.h"
/*#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>*/

//#include "level.h"


#include "stdafx.h"


using namespace PacGame::GameClasses::GameObjects;

using namespace std;

namespace PacGame
{
      namespace GameClasses
      {
          // globals
           //PVoid *globalVoid = new PVoid; 
 
           /*****************************************
           PLevel methods
           *****************************************/
          
          /*****************************************************************
           * Function reads two-digit number from stream pointer current
           * position and skips one character, it is suitable for our
           * level format only.
           *****************************************************************/
          inline int PLevel::returnNumberFromFile(ifstream &file)
          {
              char buff[3]; // char buffer for our number, before it is being parsed into integer
              char c;       // strage for single character
              file.get(c);  // we read first digit
              if(!(c >= '0' && c <= '9')) // if it isn't a digit, we return an error
                  return -1;
              else
                  buff[0] = c; // otherwise, we store it into buffer
                  
              file.get(c); // we read next character
              
              if(c >= '0' && c <= '9') // if it is a digit ...
              {
                  buff[1] = c;  // we also store it into buffer
                  buff[2] = '\0'; // and then we close string, because we need two-digit numbers only
                  file.get();  // we skip one character(space)
              }
              else // if second character isn't digit
                  buff[1] = '\0';  // we just close string
 
              return atoi(buff);  // we return number read from file, parsed into integer
          }
  
          /*****************************************************************
           * Function validates level format with checking + sign
           * position.
           *****************************************************************/
          inline bool PLevel::checkPosition(ifstream &file)
          {
              char c; // single character buffer
              file.get(c); // read +  sign

              if(c!='+') // checks if our position is valid
              {
                  //Messages::errorMessage("Invalid level data."); 
                  return false;                      
              }

              file.get(); // skip newline
              return true; // position is ok
          }

           /*****************************************************************
           * Function loops through level and finds teleport with
           * given id. It returns pointer to that teleport.
           *****************************************************************/
          inline PTeleport *PLevel::returnTeleport(int id)
          {
              for(unsigned i=0; i<teleports.size(); i++) // loops thorough vector
                  if(teleports[i]->getId() == id)  // if teleport's id matches id we're lookin' for
                      return teleports[i];  // then return it's address
         
              return NULL; // otherwise return NULL
          }
         
           /*****************************************************************
           * Function attaches object to another element in matrix
           * releases node from original element in matrix
           * and changes indexes
           *****************************************************************/          
          inline void PLevel::reattachNode(int i, int j, int i2, int j2, PLevelObject *obj)
          {
              data[i2][j2]->attachToRoot(data[i][j]->returnFirstChild());
              data[i][j]->unlinkFirstChild();
              
              if(data[i][j]->getId()==BRIDGE)
              {
                  if(obj->getId() == 1)
                  {
                      delete data[i][j];
                      data[i][j] = new PVoid;
                  }
              }
              obj->setIndex(i2, j2);
          }
          

           /*****************************************************************
           * Function checks in player has moved all cubes to their 
           * spaces
           *****************************************************************/ 
          inline bool PLevel::isLevelDone()
          {
              for(unsigned i=0; i<this->holds.size(); i++)  // we loop thorough all holders in level
              { 
                  if(this->holds[i]->returnFirstChild()==NULL) // if hold has no child
                      return false;  // level cant be done!

                  else if(((static_cast<PLevelObject*>(this->holds[i]->returnFirstChild()))->getId() < 2) 
                          || ((static_cast<PLevelObject*>(this->holds[i]->returnFirstChild()))->getId() >6))
                      return false; // on this holder there is no valid cubes (valid cubes has id's: 2-normal, 3...6-oneway cubes)
              }
              
              return true; // otherwise, player won :)
          }
          
           /*****************************************************************
           * Function checks if move is possible; if it is, processes it
           *****************************************************************/
          inline bool PLevel::checkAndApply(int i2, int j2, PLevelObject *obj, PDirection dir)
          {
              // i2 and j2 are indexes of field, we re checking; so if on field with idexes i2 and j2 is empty
              // (has nothing attached to it), then we move our object(obj) to i2, j2
              
              // checks if indexes are valible; it prevents index-out-of-range error
              if((unsigned)i2 >  (this->width-1)|| i2<0 || (unsigned)j2 > (this->height-1) || j2<0)
                  return false;

              int i = obj->getI(), j = obj->getJ(); // gets source object indexes, object, that we're moving
              
              // is move absolutely possible?
              if(data[i2][j2]->isPlayerMovePossible()==1)  // it is!
              {
                  reattachNode(i, j, i2, j2, obj);  // so we just do it ;) we move object from indexes i, j to i2, j2
                  return true;
              }
              
              //////// TELEPORT
              else if(data[i2][j2]->isPlayerMovePossible()==3)  
              {
                  // it - I index of dest teleport
                  // jt-  J index of dest teleport
                  int it = (static_cast<PTeleport*>(data[i2][j2]))->getChildTeleport()->getI(), 
                          jt = (static_cast<PTeleport*>(data[i2][j2]))->getChildTeleport()->getJ();
                  
                  if(data[it][jt]->returnFirstChild()!=NULL) // if there is object alredy on teleport
                  {
                      // code prevents crashing, if player attempts to teleport object to tepelport, where is
                      // player currently located
                      if(static_cast<PLevelObject*>(data[it][jt]->returnFirstChild())->getId() == 1)
                          return false;
                      
                      if(this->moveObject(dir, static_cast<PLevelObject*>(data[it][jt]->returnFirstChild())))  // try to move it
                      {
						// Object on teleport moved. Reattaching node ... 
                          reattachNode(i, j, it, jt, obj);   //  then move player to teleport
                          return true;
                      }
                  }
                  else  // there is no object attached to teleport, that's ok
                  {
      //              // Cool, there's no object on teleport, so beam it up
                      reattachNode(i, j, it, jt, obj);  // so we just move player to dest teleport ;)
                      return true;
                  }
              }  /// END OF TELEPORT SECTION

              // CONDITIONALLY POSSIBLE MOVES
              else if(data[i2][j2]->isPlayerMovePossible()==2  && (!data[i2][j2]->isActiveBomb()))  // move is conditionally possible; we check children
              {
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      return true;
                  }
                  
                  // case, there is normal cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  {
                      // CUBE-MOVE CODE GOES HERE
                      if(this->moveObject(dir, static_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // it is, we move object
                          return true;   
                      }
                  }  
                  
                  // case, there is oneway cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 3 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  { 
                      if(static_cast<POnewayCube*>(data[i2][j2]->returnFirstChild())->getDirection()==dir)
                      {
                          // CUBE-MOVE CODE GOES HERE
                          if(this->moveObject(dir, static_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                          {
                              reattachNode(i, j, i2, j2, obj);   // it is, we move object
                              return true;   
                          }
                      }
                  } 
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 4) // there is a bomb
                  {
                      if(obj->getId()==1) // is object a player ?
                      {
                      //    data[i2][j2]->releaseFirstChild(); // release picking bomb object
                      //    data[i2][j2]->unlinkFirstChild();
                          data[i2][j2]->releaseFirstChildObject();
                          this->player->incBombs();  // increase bombs
                          reattachNode(i, j, i2, j2, obj);   // move
           //               cout<<"St. bomb:"<<this->player->getBombs()<<endl;
                      }
                  }
              }    
          /*    else if(1)
              {
              Aliases::PDirection dirrr = static_cast<POnewayFloor*>(data[i2][j2])->getDirection();
              cout<<"stupid"<<endl;
              }*/
              // CONDITIONALLY POSSIBLE MOVE - ONEWAY FLOOR    // T O D O    FFIIIXX
              else if((data[i2][j2]->isPlayerMovePossible()==5) && (dir ==  (static_cast<POnewayFloor*>(data[i2][j2])->getDirection())))  // move is conditionally possible; we check children
              {
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      return true;
                  }
                  
                  // case, there is normal cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  {
                      // CUBE-MOVE CODE GOES HERE
                      if(this->moveObject(dir, static_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // it is, we move object
                          return true;   
                      }
                  }  
                  
                  // case, there is oneway cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 3 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  { 
                      if(static_cast<POnewayCube*>(data[i2][j2]->returnFirstChild())->getDirection()==dir)
                      {
                          // CUBE-MOVE CODE GOES HERE
                          if(this->moveObject(dir, static_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                          {

                              reattachNode(i, j, i2, j2, obj);   // it is, we move object
                              return true;   
                          }
                      }
                  } 
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 4) // there is a bomb
                  {
                    //  cout<<"idproblem"<<endl;
                      if(obj->getId()==1) // is object a player ?
                      {
                      //    data[i2][j2]->releaseFirstChild(); // release picking bomb object
                          data[i2][j2]->releaseList();
                          this->player->incBombs();  // increase bombs
                          reattachNode(i, j, i2, j2, obj);   // move
                      }
                  }
              }
             
              
              else if(data[i2][j2]->isPlayerMovePossible()==6)  // move is conditionally possible; we check children; thid id cubeholder case
              {                                             // only diffrence between causal conditional move and move to cubeHolder is
                                                             // that in this case, after we move cube to cube holder, we check if level has been done
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      if(this->isLevelDone())
                      {
                          this->endgameFlag = true;
														// do I need both?
						  this->wonFlag = true;
                          //Messages::infoMessage("You won!!!!! :))))");

						  /////// TODO
						  // place some YOU WON code here
						  /// ;)
						  ///////
					//	  MessageBox(NULL, _T("You won! :)"), _T("Congradulations!"), NULL);
                      }
                      return true;
                  }
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2 && (obj->getId()==1))  // na polju je kocka - poskusimo premaknit!
                  {
                      // koda za premik kocke
                      if(this->moveObject(dir, static_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                          if(this->isLevelDone())
                          {
                          this->endgameFlag = true;
														// do I need both?
						  this->wonFlag = true;
                           //   Messages::infoMessage("You won!!!!! :))))");

						  /////// TODO
						  // place some YOU WON code here
						  /// ;)
						  ///////
						//	  MessageBox(NULL, _T("You won! :)"), _T("Congradulations!"), NULL);
                          }
                          return true;                         
                      }
                  }   
              }
              
              return false; // to avoid warning
          }
          
          // gameplay related
           /*****************************************************************
           * Function moves object to antoher field if it is possible;
           * successful move returns true, unsuccessfull false
           *****************************************************************/
         bool PLevel::moveObject(PDirection dir, PLevelObject *obj)
          {
                  switch(dir)
                  {
                      case Aliases::left:
                          if(!checkAndApply(obj->getI(), obj->getJ()-1, obj, Aliases::left))
                              return false;
                          break;
                          
                      case Aliases::right:
                          if(!checkAndApply(obj->getI(), obj->getJ()+1, obj, Aliases::right))
                              return false;
                          break;  
                          
                      case Aliases::up:
                          if(!(checkAndApply(obj->getI()-1, obj->getJ(), obj, Aliases::up)))
                                  return false;
                          break;
                          
                      case Aliases::down:
                          if(!(checkAndApply(obj->getI()+1, obj->getJ(), obj, Aliases::down)))
                              return false;                      
                          break;                        
                  }
                  return true;              
          }
          
          // level functions implementation goes here! ;)
          
          /**************************************************************
           * Function reads file data form file, given by filename 
           * variable into level class
           **************************************************************/
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::loadLevelFromFile()
          {
              int tmsize; // teleport matrix size
              PObject *p = NULL; // our pobject pointer; for creating dynamic objects
              ifstream level; // file handle
              level.open(this->filename.c_str(), ios::in);  // opens level
         
              if(!level.is_open())  // checks if file is properly open
              {
				//  MessageBox(NULL, _T("file NOT found!"), _T(":("), NULL);
				  //Messages::errorMessage("Level file not found!");
                  return false;  // if it isn't, end routine
              }

              
              // everything went ok so far
              Messages::infoMessage("Loading level data... please wait.");
              while(!level.eof()) // we read file 'till the end
              {
                  // first read dimension
                  height = this->returnNumberFromFile(level); // dimensions are first two numbers
                  width = this->returnNumberFromFile(level);
                  
                  int num = 0;  // number that we get from file
                  
                  // considering dimension, we read first matrix
                  for(unsigned i=0; i<width; i++)  
                  {
                      for(unsigned j=0; j<height; j++)
                      {
                          num = returnNumberFromFile(level);  // we read number from file and store it into num
                          
                          if(num!=-1)  // we check if data is valid
                          {
                              // teleport case
                              if(num >= 9) // if it is > 11, then it is an teleport id
                              {
                                  data[i][j] = new PTeleport(i, j, this->gameCore, num); // create object
                                  
                                  if((resourceHandle->getTextureResource(TELEPORT_RES))==NULL)  // texture isn't in memory yet?
                                      resourceHandle->loadTextureResource(TELEPORT_RES, "\\Program Files\\xsoko\\data\\test.tga");  // load it!
								  /// dynamic->static
                                  (static_cast<PTeleport*>(data[i][j]))->setId(num);                // set its id
                            //      (static_cast<PTeleport*>(data[i][j]))->
                              //    data[i][j] = teleport;               // attach it on level
                                  this->teleports.push_back(static_cast<PTeleport*>(data[i][j])); // push teleport info on vector
                              }
                              
                              switch(num)  // if it is, we create suitable object
                              {
                                  case FLOOR:
                                      data[i][j] = new PFloor(this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                            resourceHandle->loadTextureResource(FLOOR_RES, "\\Program Files\\xsoko\\data\\floor.tga");  // load it!
                                      
                                      break;
                                      
                             /*     case OW_FLOOR:
                                      data[i][j] = new POnewayFloor(this->gameCore);
                                      break;*/
                                      
                                  case S_WALL:
                                      data[i][j] = new PSolidWall(this->gameCore);   
                                      if((resourceHandle->getTextureResource(S_WALL_RES))==NULL)
                                          resourceHandle->loadTextureResource(S_WALL_RES, "\\Program Files\\xsoko\\data\\wall.tga"); 

                                      break;
                                      
                                  case BRIDGE:
                                      data[i][j] = new PBridge(this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(BRIDGE_RES))==NULL)  // texture isn't in memory yet?
                                            resourceHandle->loadTextureResource(BRIDGE_RES, "\\Program Files\\xsoko\\data\\bridge.tga");  // load it!
                                      
                                      break;  
                                      
                                  case VOID:
                                      data[i][j] = new PVoid;
                                      break;
                                      
                                  case CUBE_PLACE:
                                      data[i][j] = new PCubeHolder(this->gameCore);
									  /// dynamic->static
										this->holds.push_back(static_cast<PCubeHolder*>(data[i][j])); // adds cuneHolder to holds array
                                      break;    
                                      
                                  case OW_FLOOR_L:
                                      data[i][j] = new POnewayFloor(this->gameCore, 5);
                                      static_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::left);
                                   //   data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "\\Program Files\\xsoko\\data\\onewayfloor.tga");  // load it!
                                      
                                 //     data[i][j]->add(NULL);
                                      break;
                                      
                                  case OW_FLOOR_R:
                                      data[i][j] = new POnewayFloor(this->gameCore, 6);
                                      static_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::right);
                                  //    data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "\\Program Files\\xsoko\\data\\onewayfloor.tga");  // load it!
                                      
                                 //     data[i][j]->add(NULL);
                                      break;
                                      
                                      
                                  case OW_FLOOR_U:
                                      data[i][j] = new POnewayFloor(this->gameCore, 7);
                                      static_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::up);
                                  //    data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "\\Program Files\\xsoko\\data\\onewayfloor.tga");  // load it!
                                      
                                 //     data[i][j]->add(NULL);
                                      break;
                                      
                                  case OW_FLOOR_D:
                                      data[i][j] = new POnewayFloor(this->gameCore, 8);
                                      static_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::down);
                                 //     data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "\\Program Files\\xsoko\\data\\onewayfloor.tga");  // load it!
                                      
                                //      data[i][j]->add(NULL);
                                      break;
                                      
                              }
                          }
                          else  // if it isn't, we return error
                          {
                              //Messages::errorMessage("Invalid level data.");
                              return false;
                          }
                      }
                  }
                  
                  // first matrix shoud be in memory by now.
                  if(!checkPosition(level))
                      return false;

                  // we continue with second matrix
                  for(unsigned i=0; i<width; i++)
                  {
                      for(unsigned j=0; j<height; j++)
                      {
                          num = returnNumberFromFile(level);
                          if(num!=-1)
                          {

                              
                              switch(num)
                              {                                              
                                  case PLAYER:
                                      p = new PPlayer(i, j, this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(PLAYER_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(PLAYER_RES, "\\Program Files\\xsoko\\data\\player.tga");  // load it!
                                      /// dynamic->static
                                      this->player = static_cast<PPlayer*>(p); // set class player pointer to player element
                                      data[i][j]->add(p);
//                                      second_matrix[i][j] = PLAYER;
                                      break;
                                      
                                  case CUBE:
                                      p = new PCube(i, j, this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(CUBE_RES, "\\Program Files\\xsoko\\data\\crate.tga");  // load it!

                                      data[i][j]->add(p);
 //                                     second_matrix[i][j] = CUBE;
                                      break;
                                      
                                  case OW_CUBE_L:
                                      p = new POnewayCube(Aliases::left, i, j, 3, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "\\Program Files\\xsoko\\data\\onewaycube.tga");  // load it!
                                     
                                      break; 
                                      
                                  case OW_CUBE_R:
                                      p = new POnewayCube(Aliases::right, i, j, 4, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "\\Program Files\\xsoko\\data\\onewaycube.tga");  // load it!
                                      break; 
                                      
                                  case OW_CUBE_U:
                                      p = new POnewayCube(Aliases::up, i, j, 5, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "\\Program Files\\xsoko\\data\\onewaycube.tga");  // load it!
                                      break;  
                                      
                                  case OW_CUBE_D:
                                      p = new POnewayCube(Aliases::down, i, j, 6, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "\\Program Files\\xsoko\\data\\onewaycube.tga");  // load it!
                                      break;
                                      
                                  case BOMB:
                                      p = new PBomb(i, j, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(BOMB_RES))==NULL)  // texture isn't in memory yet?
                                               resourceHandle->loadTextureResource(BOMB_RES, "\\Program Files\\xsoko\\data\\bomb.tga");  // load it!
                                      break; 
                                      
                                  case U_WALL:
                                      p = new PUnsolidWall(this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(U_WALL_RES))==NULL)
                                          resourceHandle->loadTextureResource(U_WALL_RES, "\\Program Files\\xsoko\\data\\unsolidwall.tga"); 
                                      break; 

                                      
                                  default:   // in
                                      data[i][j]->add(NULL);
                              }
                          }
                          else
                          {
                              //Messages::errorMessage("Invalid level data.");
                              return false;
                          }
                      }
                  }   

                  // second matrix should be in memory by now
                  // now validate
                  if(!checkPosition(level))
                      return false;

                  // validation went ok; now we read teleport relationship matrix
                  tmsize = returnNumberFromFile(level);
                  
                  for(int i=0; i<tmsize; i++)
                  {
                      PTeleport *childTeleport;  // teleprot we're attaching
                      PTeleport *parentTeleport; // parent teleport

                      parentTeleport = returnTeleport(returnNumberFromFile(level)); // get parent teleport
                      int tmp_i = parentTeleport->getI();
                      int tmp_j = parentTeleport->getJ();
                      
                      childTeleport = returnTeleport(returnNumberFromFile(level));  // get child teleport

                      if(parentTeleport!=NULL && childTeleport!=NULL)  // if teleports has been found
                      {
                    //      parentTeleport->add(childTeleport);  // attach them
                          parentTeleport->setChildTeleport(childTeleport);                      
                          //cout<<"Teleport "<<childTeleport->getId()<<" attached to teleport "<<parentTeleport->getId()<<endl;
                      }
                      else
                      {
                          //Messages::errorMessage("Invalid level data.");
                          return false;
                      }
                                        
                  }
                  // teleports.clear(); // clear teleport vector, since they are by now in memory and no longer needed
                  break;   
              }
              
              //Messages::infoMessage("Level data successfully loaded from file.");
              level.close();
              return true; // everything went ok
          }
          
          
          /**************************************************************
           * Function which reset level data 
           **************************************************************/
          void PLevel::reset()
          {
              releaseLevel();
              teleports.clear();
              holds.clear();
              endgameFlag = false;
              loadLevelFromFile();
			  this->getGameCoreHandle()->getCamera()->fitCameraToLevel(this->width, this->height);
          }
          
           /**************************************************************
           * Function returns pointer to player in level
           **************************************************************/
          PPlayer* PLevel::getPlayerHandle()
          {
              return this->player;
          }
  
          /**************************************************************
           * Function return endgame flag state
           **************************************************************/
          bool PLevel::getEndgameFlag()
          {
              return this->endgameFlag;
          }

		  /**************************************************************
           * Function return won flag state
           **************************************************************/
          bool PLevel::getWonFlag()
          {
              return this->wonFlag;
          }

		  /**************************************************************
           * Function sets won flag state
           **************************************************************/
		  void PLevel::setWonFlag(bool val)
		  {
			  this->wonFlag = val;
		  }
          
          
          /**************************************************************
           * Function initiates level
           * work in progress
           **************************************************************/
          bool PLevel::initialize()
          {
              if(!this->loadLevelFromFile())
              {
				  //Messages::errorMessage("Level loading from file failed.");
                  return 0;
              }

              // by now, matrix should be initialized with proper classes, if it went ok this far
              // try to initialize core
              if(!this->gameCore->init())
              {
                  this->gameCore->release();
                  Messages::initMessage("Game core", false);
              }
              else
                  //Messages::initMessage("Game core", true);

			  // set rotate value for camera
			//  this->gameCore->getCamera()->setRotateValue(1.0);
              
              // temporary, dump memory state
              this->print();
              
			  //Messages::initMessage("Level", true);
              return true; // everything went ok
          }
          
          /**************************************************************
           * Function draws level with OpenGL into a window
           **************************************************************/
          void PLevel::draw()
          {
              glPushMatrix();
                  for(unsigned i=0; i<this->width; i++)
                  {
                      for(unsigned j=0; j<this->height; j++)
                      {
                          PObject *obj = data[i][j]->returnFirstChild(); 
                          if(obj!=NULL) // if there is boject binded
                          {
                              glPushMatrix();
                              glTranslatef((float)i, (float)j, 0.0);
                              obj->draw(); // prints it
                              glPopMatrix();
                          }
                          else
                              if(data[i][j]!=NULL)
                              {
                                  glPushMatrix();
                                  glTranslatef((float)i, (float)j, 0.0);
                                  data[i][j]->draw();  // otherwise, print object
                                  glPopMatrix();
                              }
                          
                          // draw activated bombs, if there are any
                          if(this->bombs.size()>0)
                          {
                              for(unsigned i=0; i<bombs.size(); i++)
                              {
                                  
                                  glPushMatrix();
                                  glTranslatef((float)this->bombs[i]->i, (float)this->bombs[i]->j, 0.0);
                         //         glColor3f(1.0, 0.0, 0.0);
                                  glBindTexture(GL_TEXTURE_2D, this->resourceHandle->getTextureTesourceId(BOMB_RES));
                                  this->gameCore->getRenderer()->drawCube(0.0, 0.0, 0.5);
                                  glPopMatrix();
                              }
                          }
                      }
                  }
              glPopMatrix();  
          }
          
          /**************************************************************
           * Function dumps level data into console
           * consider it as an alternative render function :D
           **************************************************************/
          void PLevel::print()
          {
			  fstream file;
			  file.open("coredump.txt", ios::out | ios::app);
              file<<endl;
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++)
                  {          
					  PLevelObject *obj = static_cast<PLevelObject*>(data[i][j]->returnFirstChild()); 
                      if(obj!=NULL) // if there is boject binded
                      {
                          obj->print(); // prints it
                     //     file<<"ACTIVE BOMB: "<<obj->isActiveBomb()<<false;
                      }
                      else
                          if(data[i][j]!=NULL)
                            
                              data[i][j]->print();  // otherwise, print object
                  }
                  file<<'|'<<endl;
              }
              file<<endl; 
			  file.close();
          }
          
     
          
           /**************************************************************
           * releaseLevel()
           * clear all level data from memory
           **************************************************************/          
          void PLevel::releaseLevel()
          {
              for(unsigned i=0; i<width; i++)  
              {
                  for(unsigned j=0; j<height; j++)
                  {
					 // data[i][j]->
                      delete data[i][j];
                      data[i][j] = NULL; 
                  }
              }
              delete player;
			  this->gameCore->getResources()->release();
              //Messages::infoMessage("Level data successfully released from memory.");              
          }
          
          
          unsigned PLevel::getWidth()
          {
              return this->width;
          }
          
          unsigned PLevel::getHeight()
          {
              return this->height;
          }
          
           /**************************************************************
           * Dropped Bombs
           * functions manages them
           **************************************************************/ 
          void PLevel::processBombs(double current_time)
          {
                if(this->bombs.size() != 0)  // are there any bombs to trigger?
                {
                    // get addres of bomb that was released first(is first in the list)
                    PDroppedBomb* firstDroppedBomb = this->bombs[0];
                    // apparently they are!
/*                    if(round(current_time-firstDroppedBomb->dropTime) == 3)  // is it time to trigger bomb yet?
                    {    
                        // check bomb surrounding fields
                        this->checkAndApplyBombBlast(firstDroppedBomb->i-1, firstDroppedBomb->j);
                        this->checkAndApplyBombBlast(firstDroppedBomb->i+1, firstDroppedBomb->j);
                        this->checkAndApplyBombBlast(firstDroppedBomb->i, firstDroppedBomb->j-1);
                        this->checkAndApplyBombBlast(firstDroppedBomb->i, firstDroppedBomb->j+1);
                        
                        // remove first dropped bomb
                        this->bombs.erase(this->bombs.begin());
                        data[firstDroppedBomb->i][firstDroppedBomb->j]->toogleBombActivity();
                    }*/ /// round problem?!? FIXME
                }              
          }
          
          bool PLevel::addDroppedBomb(int i, int j)
          {
              if(!data[i][j]->isActiveBomb())
              {
                  //cout<<"I can attach bomb here ;)"<<endl;
            //      data[i][j]->attachToRoot(new PacGame::GameClasses::GameObjects::PDetonatedBomb());
                  data[i][j]->toogleBombActivity();
//                  this->bombs.push_back(new PDroppedBomb(i, j));
                  return true;
              }
              return false;
          }
          
          void PLevel::checkAndApplyBombBlast(int i, int j)
          {
              if(data[i][j]->returnFirstChild() != NULL)
              {
				  //  DYNAMIC->STATIC
                  if((static_cast<PLevelObject*>(this->data[i][j]->returnFirstChild())->getId())==U_WALL)  // is there unsolidWall ?
                  {
                      data[i][j]->releaseFirstChildObject();
                  } 
              }
          }
          
          
          ///// temporary?
          PCore* PLevel::getGameCoreHandle()
          {
              return this->gameCore;
          }
 
          /**************************************************************
           * Destructor
           * clear all level data from memory
           **************************************************************/ 
          PLevel::~PLevel()
          {
              this->gameCore->deinit();
              this->releaseLevel();
          }
          
          
          short PLevel::isPlayerMovePossible() { return 0; }  // blind function, just for overwrtie; DO NOT attempt to implement it and escpecially,
                                                              // do not use it in LEVEL class context!
    }
}
