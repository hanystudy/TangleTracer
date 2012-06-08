// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

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
	void renderStart(int);
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