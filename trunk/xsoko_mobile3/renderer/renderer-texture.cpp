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
 * File: renderer-texture.cpp
 *
 * Summary:
 * Includes texture class implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa 2008
 * Jernej Skrabec June 19 2008
 * Aljosa Osep September 18 2008
*/

//#include "texture.h"

#include "stdafx.h"

namespace PacGame
{
      namespace RenderMaschine
      {
          PTexture::PTexture(string _filename)
          {
              type = GL_RGBA;  // sets texture type
              filename = _filename; // sets filename
          }

          PTexture::PTexture(string _filename, string type, bool filter)
          {
              // standard procedure
              this->type = GL_RGBA;
              filename = _filename;

              // gen
              if(type == "tga")
                  makeTgaTexture(filter);
              else
                  Messages::errorMessage("Unknown image format type, bad texture class initialization! Blame developers for this!");
          }

          PTexture::~PTexture()
          {
              this->release();
              Messages::infoMessage("Texture released from memory.");
          } 
          
          void PTexture::setPath(string filename)
          {
              this->filename = filename;
          }

          bool PTexture::loadTGA()
          {
              GLubyte       TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};              // uncompressed TGA Header
              GLubyte       TGAcompare[12];                                         // for compare...
              GLubyte       header[6];                                              // first 6 bits
              unsigned      bytesPerPixel;                                          // number of bytes per pixel in tga image
              unsigned      imageSize;                                              // store image size
              unsigned      temp;                                                   
    //        unsigned      type  = GL_RGBA;        

              FILE *file = fopen(filename.c_str(), "rb");                                   // open file

              if(file==NULL ||                                                      
                    fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) || // are 12 bytes readable?
                    memcmp(TGAheader,TGAcompare,sizeof(TGAheader)) != 0 ||                          // header match?
                    fread(header, 1,sizeof(header), file) != sizeof(header))                                // :)
              {
                      if (file == NULL)
                      {
				//			  Messages::errorMessage("Texture file  is empty!");
				//			  Messages::errorMessage(this->filename);
                              return false;                                         // :(
                      }
                      else 
                      {
			//				  Messages::errorUnknown();
                              fclose(file);                                         
                              return false;                                         
                      }
              }

              this->width  = header[1] * 256 + header[0];                         // get width (highbyte*256+lowbyte)
              this->height = header[3] * 256 + header[2];                         // get height   (highbyte*256+lowbyte)

              if(this->width      <=0 ||                                          // width and height must be > 0
                     this->height <=0 ||                                          
                     (header[4]!=24 && header[4]!=32))                              // 24 or 32 bit
              {

			//		  Messages::errorMessage("Texture isn't 32 or 24 bit OR texture width or height isn't greater than zero :D");
                      fclose(file);                                         
                      return false;
              } 

              this->bpp   = header[4];                                            // grab The TGA's Bits Per Pixel (24 or 32)
              bytesPerPixel = this->bpp/8;                                        // divide By 8 To Get The Bytes Per Pixel
              imageSize             = this->width*this->height*bytesPerPixel;   // Calculate The Memory Required 

              this->imageData=(GLubyte *)malloc(imageSize);                       // reserve memory to store TGA data

              if(this->imageData==NULL ||                                 // storage memory exist... ?
                     fread(this->imageData, 1, imageSize, file)!=imageSize)       // Does The Image Size Match The Memory Reserved?
              {
                      if(this->imageData!=NULL)                                   // release
                      {
               //               Messages::errorMessage("TGA image data is empty. Releasing memory...");
                              free(this->imageData);      
                      }

			//		  Messages::errorUnknown();
                      fclose(file);                                                 
                      return false;                                                 
              }

              for(unsigned i=0; i<imageSize; i+=bytesPerPixel)      // Swaps The 1st And 3rd Bytes, R and B
              {
                      temp=this->imageData[i];                                    
                      this->imageData[i] = this->imageData[i + 2];              
                      this->imageData[i + 2] = temp;                              
              }

              fclose (file);                                                                
          //    Messages::infoTexture(filename.c_str());
              return true;
          }

          void PTexture::generateTextureMipmap()
          {
              // TEXTURE BUILDING SECTION
        /*      glGenTextures(1, &this->texID);					// Generate texture IDs
              // MipMap filtering
              glBindTexture(GL_TEXTURE_2D, this->texID);
              glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
              glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); 

              if (this->bpp==24) // 24 bpp means, we have alpha channel		
              {
                  Messages::initMessage("TGA texture/Alpha channel", false);
                  type=GL_RGB;							// type je GL_RGB
              }
              else
                  Messages::initMessage("TGA texture/Alpha channel", true);

              gluBuild2DMipmaps(GL_TEXTURE_2D, type, this->width, this->height, type, GL_UNSIGNED_BYTE, this->imageData); 
              Messages::infoMessage("Texture was successfully generated, mipmap filtering.");*/
          }

          void PTexture::generateTextureLinear()
          {
              // TEXTURE BUILDING SECTION
              glGenTextures(1, &this->texID);					// Generate texture IDs
              glBindTexture(GL_TEXTURE_2D, this->texID);				// binf texture
              glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear 
              glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

              if (this->bpp==24)	// 24 bpp means, we have alpha channel	
              {
           //       Messages::initMessage("TGA texture/Alpha channel", false);
                  type=GL_RGB;							// type je GL_RGB
              }
         //     else
            //      Messages::initMessage("TGA texture/Alpha channel", true);

              glTexImage2D(GL_TEXTURE_2D, 0, type, this->width, this->height, 0, type, GL_UNSIGNED_BYTE, this->imageData); 
         //     Messages::infoMessage("Texture was successfully generated, linear filtering.");
          }

          bool PTexture::makeTgaTexture(bool mipmap)
          {
              if(!loadTGA())  // first, me must load tga
              {
              //    Messages::infoMessage("Texture creation failed.");
                  return false;
              }

              if(mipmap)   // if we are successful, we generate texture; we have two possibilities...
                  generateTextureMipmap();    // mipmap filtering
              else
                  generateTextureLinear();    // or linear filtering

        //      Messages::infoMessage("Texture created, ready for use.");
        //      cout<<endl<<endl; 
              return true;

          }

          // getters
          unsigned PTexture::getId()
          {
              return this->texID;   // returns id of textyre
          }
          
          string PTexture::getFilename() const
          {
              return this->filename;
          }
          
          void PTexture::release()
		  {
			  if(this->imageData!=NULL)
			  {
				  Messages::infoMessage("Releasing texture...");
				  Messages::infoMessage(this->filename);
				  free(this->imageData);  // releases tga data from memory
				  this->imageData = NULL;
			  }
          }
      }
}
