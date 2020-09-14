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

#ifndef REPORT_HPP
#define REPORT_HPP

#include <memory>

class Report {
public:
    static std::unique_ptr<Report> make(const std::string_view text);
    
    Report() = delete;
    Report(std::string _name, uint64_t _id, double _ts,
                double _x, double _y, double _heading,
                double _course, double _speed);
    ~Report() = default;


// metadata
        const std::string name;
        const uint64_t id;
        const double timestamp;

// position / orientation
        const double x;  // meters to the right of the origin 
        const double y;  // meters upwards from the origin
        /// /brief degrees CW from true north
        const double heading;

// velocity
        /// /brief degrees CW from true north
        const double course;
        const double speed;

private:
    static const std::hash<std::string> hasher;

};


#endif
