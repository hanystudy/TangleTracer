// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#ifndef TANGEIMAGESIZE_H
#define TANGEIMAGESIZE_H

#include <QDialog>
#include "stdafx.h"
#include "ui_imagesize.h"

class TangeImageSize : public QDialog, Ui_TTImageSize
{
	Q_OBJECT

public:
	TangeImageSize(QWidget *parent);
	~TangeImageSize();

	void SetSize(int,int);
	QSize GetSize();
private:
	
};

#endif // TANGEIMAGESIZE_H
