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

#include "TrackCache.hpp"

cache_iterator TrackCache::cbegin() const {
    return index.cbegin();
}

cache_iterator TrackCache::cend() const {
    return index.cend();
}

Track* const TrackCache::get(uint64_t id) const {
    return nullptr;
}

size_t TrackCache::size() const {
    return index.size();
}

bool TrackCache::update(std::unique_ptr<Report> report){
    // create new Track, if missing
    auto result = index.try_emplace(report->id, report->name, report->id);
    
    // equivalent to: `index[report->id].update(...)` ...but faster.  ;)
    result.first->second.update(std::move(report));

    return true;
}


TrackCache::~TrackCache(){
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
