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
