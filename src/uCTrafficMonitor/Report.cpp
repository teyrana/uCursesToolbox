//*****************************************************************************
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//*****************************************************************************

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Report.hpp"

Report::Report():
    course(NAN),
    heading(NAN),
    latitude(NAN),
    longitude(NAN),
    speed(NAN)
{
    // no-op
}

Report::Report( double cog, double hdg, double lat, double lon, double spd):
    course(cog),
    heading(hdg),
    latitude(lat),
    longitude(lon),
    speed(spd)
{
    // no-op
}
