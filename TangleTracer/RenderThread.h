// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "stdafx.h"
#include "RenderPixel.h"
#include "World.h"

class RenderCanvas;

class RenderThread
{
public:
   RenderThread(RenderCanvas* c, World* w) : world(w), canvas(c), m_image(NULL) {};
   virtual void Run(int);
   virtual void setPixel(int x, int y, int red, int green, int blue);

   void setImage(QImage *);
private:
   void NotifyCanvas();
   
   World* world;
   RenderCanvas* canvas;
   
   vector<RenderPixel*> pixels;
   long lastUpdateTime;

   QImage* m_image;


};
