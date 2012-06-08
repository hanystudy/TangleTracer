// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "RenderCanvas.h"

RenderCanvas::RenderCanvas()
   : m_image(NULL)
   , w(NULL)
   , thread(NULL)
   , width(200)
   , height(200)
{
}

RenderCanvas::~RenderCanvas(void)
{
   if(m_image != NULL)
      delete m_image;
   
  // if(thread != NULL)
  //    thread->Delete();
   
   if(w != NULL)
      delete w;
   
 ///  if(timer != NULL)
  //    delete timer;
}

void RenderCanvas::SetImage(QImage& image)
{
   if(m_image != NULL)
      delete m_image;
   
   m_image = new QImage(image);
}

QImage RenderCanvas::GetImage(void)
{
   if(m_image != NULL)
      return *m_image;
   
   return QImage();
}
/*
void RenderCanvas::OnRenderCompleted()
{
   thread = NULL;
   
   if(w != NULL)
   {
      delete w;
      w = NULL;
   }
   
   if(timer != NULL)
   {
      long interval = timer->Time();
  
      delete timer;
      timer = NULL;
   }
}

void RenderCanvas::OnNewPixel( wxCommandEvent& event )
{
   //set up double buffered device context
   wxClientDC cdc(this);
   DoPrepareDC(cdc);
   wxBufferedDC bufferedDC(&cdc, *m_image);
   
   //iterate over all pixels in the event
   vector<RenderPixel*> *pixelsUpdate =
                        (vector<RenderPixel*> *)event.GetClientData();
   
   for(vector<RenderPixel*>::iterator itr = pixelsUpdate->begin();
                        itr != pixelsUpdate->end(); itr++)
   {
      RenderPixel* pixel = *itr;
      
      wxPen pen(wxColour(pixel->red, pixel->green, pixel->blue));
      bufferedDC.SetPen(pen);
      bufferedDC.DrawPoint(pixel->x, pixel->y);
     
      pixelsRendered++;
      delete pixel;
   }
   
   pixelsUpdate->clear();
   delete pixelsUpdate;
}*/

void RenderCanvas::renderPause(void)
{
   //if(thread != NULL)
    //  thread->Pause();
   
   //updateTimer.Stop();
   
   //if(timer != NULL)
     // timer->Pause();
}

void RenderCanvas::renderResume(void)
{
   //if(thread != NULL)
     // thread->Resume();
   
  // updateTimer.Start();
   
  // if(timer != NULL)
 //     timer->Resume();
}

/*
void RenderCanvas::OnTimerUpdate( wxTimerEvent& event )
{
   if(timer == NULL)
      return;
   
   //percent
   float completed = (float)pixelsRendered / (float)pixelsToRender;
      
   wxString progressString = wxString::Format(wxT("Rendering...%d%%"),
                                             (int)(completed*100));
   wxGetApp().SetStatusText( progressString , 0);
   
   //time elapsed
   long interval = timer->Time();
   
   wxTimeSpan timeElapsed(0, 0, 0, interval);
   
   //time remaining
   float remaining = 1.0f - completed;
   long msecRemain = (long)
                       (((double)interval / (completed*100)) * 100 * remaining);
   
   wxTimeSpan timeRemaining(0, 0, 0, msecRemain);
   
   wxString timeRemainString = timeRemaining.Format(wxT(" / ETA: %H:%M:%S"));
   wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));
   
   //only display ETA if something has been completed
   if(msecRemain >= 0)
      wxGetApp().SetStatusText( timeString + timeRemainString, 1);
   else
      wxGetApp().SetStatusText( timeString, 1);
}*/

void RenderCanvas::renderStart(int no)
{
	w = new World();

	//wxGetApp().SetStatusText( wxT( "Building world..." ) );

	w->build(no);

	//wxGetApp().SetStatusText( wxT( "Rendering..." ) );
	w->vp.hres = width;
	w->vp.vres = height;
	//w->vp.set_pixel_size(1.0);
	//w->vp.num_samples = 16;			//only works in chapter 5.6
	//w->vp.set_samples(16);			//works after chapter 5, while you can use function set_sampler but this is easier

	pixelsRendered = 0;
	pixelsToRender = w->vp.hres * w->vp.vres;

	m_image = new QImage(w->vp.hres, w->vp.vres,QImage::Format::Format_RGB888);
	//set the background
	//wxBitmap bitmap(w->vp.hres, w->vp.vres, -1);
	//wxMemoryDC dc;
	//dc.SelectObject(bitmap);
	//dc.SetBackground(*wxGREY_BRUSH);
	//dc.Clear();

	//wxBitmap tile(bg_xpm);
	/*
	for(int x = 0; x < w->vp.hres; x += 16)
	{
	for(int y = 0; y < w->vp.vres; y += 16)
	dc.DrawBitmap(tile, x, y, FALSE);
	}*/

	// dc.SelectObject(wxNullBitmap);

	//wxImage temp = bitmap.ConvertToImage();
	//SetImage(temp);

	//updateTimer.Start(250);

	//start timer
	// timer = new wxStopWatch();

	thread = new RenderThread(this,w);
	
	thread->setImage(m_image);
	w->paintArea = thread;

	thread->Run(no);
}

void RenderCanvas::SetSize(int w ,int h)
{
	this->width = w;
	this->height = h;
}