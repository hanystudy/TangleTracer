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

