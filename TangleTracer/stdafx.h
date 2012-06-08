// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <Windows.h>

#include <qstring.h>
#include <QPainter>
#include <QImage>
#include <QPaintEvent>
#include <qpaintengine.h>
#include <qmenu.h>
#include <qaction.h>
#include <qfiledialog.h>
#include <qdatetime.h>

#include <vector>

using namespace std;

#pragma comment(lib,"psapi.lib")

#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

#define MAX_NUM_DEMOS 440//395//374//354//295//273//257//242//202//183//167//153

extern QString demo[];
