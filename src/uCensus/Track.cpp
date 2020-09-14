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

#include <cstdlib>
#include <iostream>

#include "Report.hpp"
#include "Track.hpp"

using namespace std;

Track::Track(const std::string& _name, uint64_t _id)
    : name(_name)
    , id(_id)
{}

Track::Track(const Track& other)
    : name(other.name)
    , id(other.id)
{}

void Track::update(std::unique_ptr<Report> _report){
    last_report = std::move(_report);
    // _report is left in an undefined state
}