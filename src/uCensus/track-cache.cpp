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

#include <proj.h>

#include "track-cache.hpp"

PJ* P_for_GIS;
PJ_COORD a, b;

TrackCache::TrackCache()
    : contextp(nullptr)
    , proj(nullptr)
{
    contextp = proj_context_create();
    set_origin(42.357591,-71.082075);  // middle of Charles River Basin
}

cache_iterator TrackCache::cbegin() const {
    return index.cbegin();
}

cache_iterator TrackCache::cend() const {
    return index.cend();
}

Track* const TrackCache::get(uint64_t id) const {
    return nullptr;
}

void TrackCache::set_origin(double latitude, double longitude) {
    if(std::isnan(latitude) || std::isnan(longitude)){
        return;
    }
    this->origin_latitude = latitude;
    this->origin_longitude = longitude;

    // https://mangomap.com/robertyoung/maps/69585/what-utm-zone-am-i-in-#
    const int zone = (static_cast<int>((origin_longitude + 180.)/6.) + 1) % 60;
    // fprintf(stderr, "origin (deg): %g, %g\n", origin_latitude, origin_longitude);
    // fprintf(stderr, "zone:         %d\n", zone);

    const std::string definition("+proj=utm +zone=" + std::to_string(zone) + " +ellps=GRS80");
    if(nullptr == proj){
        proj_destroy(proj);
    }
    proj = proj_create(contextp, definition.c_str());
    
    //     # preparing projection data
    //     self.pj_latlong = pyproj.Proj("+proj=latlong +ellps=WGS84")
    //     self.pj_utm = pyproj.Proj("+proj=utm +ellps=WGS84 +zone=%d" % self._zone)

    // x, y = pyproj.transform(self.pj_latlong,  self.pj_utm, origin.longitude, origin.latitude)
    // const double origin_x = NAN;
    // const double origin_y = NAN;
    // fprintf(stderr, "origin: %g, %g\n", origin_x, origin_y);
    
    // fprintf(stderr, ">>> Debug Projection\n");
    this->origin_latitude = proj_torad(origin_latitude);
    this->origin_longitude = proj_torad(origin_longitude);
    // fprintf(stderr, "    .1. Projecting LL: lat: %g,    lon: %g \n", origin_latitude, origin_longitude);
    // fprintf(stderr, "    .2. As Radians:    lat: %g,    lon: %g\n", proj_torad(origin_latitude), proj_torad(origin_longitude));
    PJ_COORD c_in = proj_coord( proj_torad(origin_longitude), proj_torad(origin_latitude), 0, 0);

    PJ_COORD raw_coord = proj_trans( proj, PJ_FWD, c_in);
    // fprintf( stderr, "    .3. Easting:   %12.2f,    Northing: %12.2f\n", raw_coord.enu.e, raw_coord.enu.n );

    // PJ_COORD back_coord = proj_trans (proj, PJ_INV, raw_coord);
    // fprintf( stderr, "    .4. Back Check:   lat: %g,    lon: %g\n", back_coord.lp.phi, back_coord.lp.lam);

    origin_easting = raw_coord.enu.e;
    origin_northing = raw_coord.enu.n;
    // fprintf(stderr, "    .5. Projecting to UTM: %g, %g \n", origin_easting, origin_northing);
}

size_t TrackCache::size() const {
    return index.size();
}

bool TrackCache::update(const std::string_view text){
    auto report = Report::make(text, proj, origin_easting, origin_northing);

    // create new Track, if missing
    auto result = index.try_emplace(report->id, report->name, report->id);
    
    // equivalent to: `index[report->id].update(...)` ...but faster.  ;)
    result.first->second.update(std::move(report));

    return true;
}

TrackCache::~TrackCache(){

    // libproj cleanup
    proj_destroy(proj);
    proj_context_destroy(contextp);

    // Probably not necessary.
    // // for track in index:
    // for (auto it = index.begin(); it != index.end(); ++it) {
    //     uint64_t key = it->first;
    //     Track* track = &it->second;
    //     //     (1) remove track from index
    //     index.erase(key);
    //     //     (2) delete each track
    //     delete track;
    // }
    return;
}
