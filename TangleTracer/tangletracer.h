// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#ifndef TANGLETRACER_H
#define TANGLETRACER_H

#include "stdafx.h"

#include <QtGui/QMainWindow>
#include "ui_tangletracer.h"

#include "RenderCanvas.h"
#include "tangeimagesize.h"

#include <Psapi.h>

class TangleTracer : public QMainWindow, public Ui_TangleTracerClass
{
	Q_OBJECT

public:
	TangleTracer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TangleTracer();

private:
	//Ui::TangleTracerClass ui;

	QImage *image;

	void render();

	void print();

	RenderCanvas *canvas; //where the rendering takes place
	QPainter *painter;

	int width;
	int height;

	QAction *start;
	QAction *save;
	QAction *size;
	QMenu *menu;

	QMenu *submenu;

	qint64 deltatime;

	PROCESS_MEMORY_COUNTERS psmemCounters;
	HANDLE handle;

	int deltamem;
	int no;

	QActionGroup *submenuactions;
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void startrender();
	void saveas();
	void setsize();

	void submenuchecked();
};

#endif // TANGLETRACER_H
