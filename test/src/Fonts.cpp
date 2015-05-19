/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2015 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "Fonts.hpp"
#include "Look/FontDescription.hpp"
#include "Screen/Font.hpp"
#include "Screen/Layout.hpp"
#include "Asset.hpp"

#include <string.h>

Font normal_font, small_font, bold_font, monospace_font;

void
InitialiseFonts()
{
  unsigned font_height = Layout::SmallScale(IsAndroid() ? 30u : 24u);

  normal_font.Load(FontDescription(font_height / 2));
  small_font.Load(FontDescription(font_height / 2 - Layout::Scale(2)));
  bold_font.Load(FontDescription(font_height / 2, true));
  monospace_font.Load(FontDescription(10, false, false, true));
}

void
DeinitialiseFonts()
{
  monospace_font.Destroy();
  bold_font.Destroy();
  small_font.Destroy();
  normal_font.Destroy();
}
