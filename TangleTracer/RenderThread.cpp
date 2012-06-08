// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

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

void RenderThread::Run(int no)
{
	if(world->objects.size() == 0)
	{
		return;
	}
	if(no < 3)
	{
		world->render_scene();
		//works for chapter 1-3
	}
	else if( no == 3)
	{
		world->camera_ptr->render_scene(*world);
		//only works for chapter 4.1
	}
	else if( no == 4)
	{
		world->camera_ptr->render_scene(*world);
		//only works for chapter 4.2
	}
	else
	{
		world->camera_ptr->render_scene(*world);
	}
	//world->render_scene_antialise_regular_sampler();	
	//only works for chapter 5.6
	//world->render_scene_perspective();
	//only works for chapter 8.1
		//world->camera_ptr->render_scene(*world);
		//works after chapter 14

	if( m_image != NULL)
	{
		for( vector<RenderPixel*>::const_iterator it = pixels.begin(); it != pixels.end(); ++it)
		{
			m_image->setPixel((*it)->x,(*it)->y, QColor((*it)->red,(*it)->green,(*it)->blue).rgb());
		}
	}
}

void RenderThread::setImage(QImage *m)
{
	this->m_image = m;
}
