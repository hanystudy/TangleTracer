// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

class RenderPixel
{
public:
   RenderPixel(int x, int y, int red, int green, int blue);

public:
   int x, y;
   int red, green, blue;
};
