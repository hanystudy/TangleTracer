#include "RenderThread.h"

void RenderThread::setPixel(int x, int y, int red, int green, int blue)
{
   
   pixels.push_back(new RenderPixel(x, y, red, green, blue));
   
   //if(timer->Time() - lastUpdateTime > 40)
   //NotifyCanvas();
    
   //TestDestroy();
}

void RenderThread::NotifyCanvas()
{
   //lastUpdateTime = timer->Time();
   
   //copy rendered pixels into a new vector and reset
   vector<RenderPixel*> *pixelsUpdate = new vector<RenderPixel*>(pixels);
   pixels.clear();
   
   //wxCommandEvent event(wxEVT_RENDER, ID_RENDER_NEWPIXEL);
   //event.SetClientData(pixelsUpdate);
   //canvas->GetEventHandler()->AddPendingEvent(event);
}

void RenderThread::Run()
{
	//world->render_scene();	//works in chapter 1-3
	//world->render_scene_antialise_regular();	//only works in chapter 4.1
	//world->render_scene_antialise_random();	//only works in chapter 4.2
	//world->render_scene_antialise_regular_sampler();	//only works in chapter 5.6
	world->render_scene_perspective();					//only works in chapter 8.1
	if( m_image != NULL)
		for( vector<RenderPixel*>::const_iterator it = pixels.begin(); it != pixels.end(); it++)
		{
			m_image->setPixel((*it)->x,(*it)->y, QColor((*it)->red,(*it)->green,(*it)->blue).rgb());
		}
}

void RenderThread::setImage(QImage *m)
{
	this->m_image = m;
}