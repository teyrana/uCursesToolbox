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

#ifndef TRACK_CACHE_HPP
#define TRACK_CACHE_HPP

#include <map>
#include <memory>

#include "report.hpp"
#include "track.hpp"

typedef std::map<uint64_t, Track>::const_iterator cache_iterator;

class TrackCache
{
    public:
        TrackCache();

        ~TrackCache();

        cache_iterator cbegin() const;

        cache_iterator cend() const;

        Track * const get(uint64_t id) const;

        void set_origin(double latitude, double longitude);

        size_t size() const;

        bool update(const std::string_view text);

    private:
        double origin_latitude;
        double origin_longitude;
        double origin_easting;
        double origin_northing;

        PJ_CONTEXT *contextp;
        PJ* proj;
        std::map<uint64_t, Track> index;

};

#endif
