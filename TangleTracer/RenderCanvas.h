#pragma once

#include "stdafx.h"
#include "World.h"
#include "RenderThread.h"

class RenderCanvas
{
public:
	RenderCanvas();
	virtual ~RenderCanvas(void);

	void SetImage(QImage& image);
	QImage GetImage(void);

	//virtual void OnDraw(wxDC& dc);
	void renderStart(void);
	void renderPause(void);
	void renderResume(void);
	//void OnRenderCompleted( wxCommandEvent& event );
	//void OnTimerUpdate( wxTimerEvent& event );
	// void OnNewPixel( wxCommandEvent& event );
	void SetSize(int,int);

protected:
	//wxBitmap *m_image;
	QImage *m_image;
	World* w;

private:
	RenderThread* thread;
	//wxStopWatch* timer;
	long pixelsRendered;
	long pixelsToRender;

	int width;
	int height;
	//wxTimer updateTimer;
};