// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "tangeimagesize.h"

TangeImageSize::TangeImageSize(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

TangeImageSize::~TangeImageSize()
{

}

void TangeImageSize::SetSize(int w,int h)
{
	this->spinHeightBox->setValue(h);
	this->spinWidthBox->setValue(w);
}

QSize TangeImageSize::GetSize()
{
	return QSize(this->spinWidthBox->value(),this->spinHeightBox->value());
}

