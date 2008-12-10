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
 * File: level.h
 *
 * Summary:
 * Includes level class definition, abstratct grid element def., and
 * several others level struct classes definitions
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Aljosa 2008
*/

#ifndef __LEVEL_H
#define __LEVEL_H

#include <string>
#include <vector>
//#include <deque>
#include "object.h"
#include "CommonStructures.h"
#include "player.h"
#include "core.h"

using namespace PacGame::GameClasses::GameObjects;
using namespace PacGame::Functions;
using namespace PacGame::Aliases;
using namespace PacGame::RenderMaschine;


// MATRIKA 1
#define FLOOR 0 
#define S_WALL 1 //  (PSolidWall)
#define BRIDGE 2 // (PBridge)
#define VOID 3 // (PVoid) 
#define CUBE_PLACE 4
#define OW_FLOOR_L 5 // (POneWayFloor)
#define OW_FLOOR_R 6 // (POneWayFloor)
#define OW_FLOOR_U 7 // (POneWayFloor)
#define OW_FLOOR_D 8 // (POneWayFloor)
#define TELEPORT 9 // (PTeleport)


// MATRIKA 2
#define NO_CHILD 0
#define PLAYER 1 // (PPlayer)
#define CUBE 2 // (PCube)
#define OW_CUBE_L 3 // (POnewayCube)
#define OW_CUBE_R 4 // (POnewayCube)
#define OW_CUBE_U 5 // (POnewayCube)
#define OW_CUBE_D 6 // (POnewayCube)
#define BOMB 7 // (PBomb)
#define U_WALL 8 // (PUnsolidWall)
#define D_BOMB 9 // (PDetonatedBomb)

// id's of resourcev for objects
#define FLOOR_RES 0
#define S_WALL_RES 1 
#define BRIDGE_RES 2 
#define CUBE_PLACE_RES 3
#define OW_FLOOR_RES 4
#define TELEPORT_RES 5
#define PLAYER_RES 6
#define CUBE_RES 7
#define OW_CUBE_RES 8
#define BOMB_RES 9
#define U_WALL_RES 10

namespace PacGame
{

      namespace GameClasses
      {
                  
               /**********************************************************
               * PLevel
               *
               * Represents a whole level, including its data
               * --------------------------------------------------------
               * Aljosa 2007 - 2008
               * ********************************************************/
              class PLevel : public PObject
              {
              private:
                  string filename;                   // level filename
                  PLevelObject* data[30][30];        // actual level data
                  int second_matrix[30][30];         // presentation of second matrix with id
                  vector<PTeleport*> teleports;      // vector of teleport pointers
                  unsigned width, height;            // level dimensions
                  PPlayer *player;                   // player instance 
                  vector<PCubeHolder*> holds;        // vector contains all cube holders in level; it helps to determine when level is finished
                  PCore *gameCore;                   // game core object
                  PResourceManager *resourceHandle;  // shortcut to resources
                  bool endgameFlag;

				  bool wonFlag;
                  
                  vector<PDroppedBomb*> bombs;   // list of currently dropped bombs
                 
              public:
                  PLevel(string filename) : filename(filename),  width(0), height(0), player(NULL),  gameCore(new PCore), resourceHandle(this->gameCore->getResources()), endgameFlag(false), wonFlag(false) {} // default constructor
                  virtual ~PLevel();
                  
                  // gameplay related
                  bool moveObject(PDirection dir, PLevelObject *obj);
                  inline bool checkAndApply(int i2, int j2, PLevelObject *obj, PDirection dir);
                  inline void reattachNode(int i, int j, int i2, int j2, PLevelObject *obj);
                  inline bool isLevelDone(); // checks if all cubes are in places
                  
                  // level data manipulation
                  bool loadLevelFromFile(); // loads level from txt file into structure, stores level widthm height into class properties
                  bool saveStateToFile(string filename);   // exports level state to file
                  void releaseLevel(); // released level from memory
                  void reset();
                  
                  // level toolkit functions
                  inline int returnNumberFromFile(ifstream &file); // returns number from file and moves file pointer
                  inline bool checkPosition(ifstream &file); // checks if position is valid and moves file pointer
                  inline PTeleport* returnTeleport(int id); // returns teleports addres, that contains given id
                  PPlayer* getPlayerHandle();
                  PCore* getGameCoreHandle();
                  
                  // getters
                  bool getEndgameFlag();
				  bool getWonFlag();
				  void setWonFlag(bool val);
                  unsigned getWidth();
                  unsigned getHeight();
                  
                  // bomb related
                  bool addDroppedBomb(int i, int j);
                  void checkAndApplyBombBlast(int i, int j);
                  void processBombs(double current_time);

                  // functions to override
                  void draw();  // draws whole level
                  bool initialize(); // initiates level
                  void print(); // dumps level data into console
                  short isPlayerMovePossible();  // blind method
              };
      }
}

#endif
