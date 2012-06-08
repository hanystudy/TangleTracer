// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "tangletracer.h"

TangleTracer::TangleTracer(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	,image(NULL)
	,painter(NULL)
	,width(512)
	,height(512)
	,deltatime(0)
	,deltamem(0)
	,no(0)
{
	setupUi(this);
	DWORD pid = ::GetCurrentProcessId();
	handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);	


	image =new QImage(width,height,QImage::Format::Format_RGB32);
	image->fill(0);

		
	canvas = new RenderCanvas();
	canvas->SetSize(width,height);
		
	painter = new QPainter(this);
	
	menu = new QMenu(this);
	menu->setStyleSheet("color: rgb(1, 1, 1);");
	menu->setAutoFillBackground(true);
	
	start = new QAction("start",this);
	save = new QAction("save",this);
	size = new QAction("size",this);

	
	submenu = new QMenu("demos",this);

	submenuactions = new QActionGroup(this);

	submenuactions->setExclusive(true);

	for(int i = 0; i < MAX_NUM_DEMOS; ++i )
	{
		QAction *ac = new QAction(demo[i],this);
		ac->setCheckable(true);
		submenuactions->addAction(ac);
		submenu->addAction(ac);
		connect(ac,SIGNAL(triggered()),this,SLOT(submenuchecked()));
	}

	menu->addMenu(submenu);
	menu->addAction(start);
	menu->addAction(save);
	menu->addAction(size);
	
	save->setEnabled(false);

	start->setCheckable(false);
	start->setCheckable(false);

	connect(this->start,SIGNAL(triggered()),this,SLOT(startrender()));
	connect(this->save,SIGNAL(triggered()),this,SLOT(saveas()));
	connect(this->size,SIGNAL(triggered()),this,SLOT(setsize()));
}

TangleTracer::~TangleTracer()
{
	if(image != NULL)
		delete image;
}

void TangleTracer::render()
{	
	if(image != NULL)
		delete image;
	//time
	qint64 time = QDateTime::currentMSecsSinceEpoch();
	//mem
	::GetProcessMemoryInfo(handle,&psmemCounters,sizeof(psmemCounters));
	deltamem = psmemCounters.WorkingSetSize / 1000;
	canvas->renderStart(no);
	deltatime = QDateTime::currentMSecsSinceEpoch() - time;
	::GetProcessMemoryInfo(handle,&psmemCounters,sizeof(psmemCounters));
	deltamem = psmemCounters.WorkingSetSize / 1000 - deltamem;

	image = new QImage(canvas->GetImage());
	//image.save("c:\\1.jpg");
	repaint();
}

void TangleTracer::paintEvent(QPaintEvent *pe)
{
	if(painter != NULL)
	{
		painter->begin(this);
		painter->drawImage(0,0,*image);
		painter->end();
		print();
	}
}

void TangleTracer::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		menu->popup(this->mapToGlobal(event->pos()));
	}
}

void TangleTracer::startrender()
{
	render();
	save->setEnabled(true);
}

void TangleTracer::saveas()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save as"), 0 , tr("Bitmap Images (*.bmp)"));
	image->save(filename);
}

void TangleTracer::setsize()
{
	TangeImageSize dlg(this);
	dlg.SetSize(width, height);

	if(dlg.exec() == QDialog::Accepted)
	{
		QSize size = dlg.GetSize();
		width = size.width();
		height = size.height();
		canvas->SetSize(width,height);

		if(image != NULL)
			delete image;
		image =new QImage(width,height,QImage::Format::Format_RGB32);
		image->fill(0);
		repaint();
	}
}

void TangleTracer::print()
{
	QPainter p(this);
	p.begin(this);
	p.setFont(QFont("Arial", 10));
	p.drawText(width+10,20,"Render time: "+QString::number(deltatime)+" ms");
	p.drawText(width+10,40,"Render workset size: "+QString::number(deltamem)+" KB");
	p.end();
}

void TangleTracer::submenuchecked()
{
	QAction *p = submenuactions->checkedAction();
	for(int i = 0 ; i < MAX_NUM_DEMOS; ++i )
	{
		if( p->text() == demo[i] )
		{
			no = i;
			return;
		}
	}
}