//Copyright 2010-2014 Benjamin ALBOUY-KISSI
/*
    This file is part of LibGraph.

    LibGraph is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LibGraph is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LibGraph. If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#ifdef LIBGRAPH2_USE_GDIPLUS
#  include "LibGraph2impGDIPLUS.h"
#endif
#ifdef LIBGRAPH2_USE_DIRECTX
#  include "libgraph2impDX.h"
#endif
#ifdef LIBGRAPH2_USE_OPENGL
#  include "libgraph2impGL.h"
#endif
