#pragma once

#include "stdafx.h"
#include "RenderPixel.h"
#include "World.h"

class RenderCanvas;

class RenderThread
{
public:
   RenderThread(RenderCanvas* c, World* w) : world(w), canvas(c), m_image(NULL) {};
   virtual void Run();
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
