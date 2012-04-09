
#include <Windows.h>

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
