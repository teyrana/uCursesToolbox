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

#ifndef DISPLAY_COLUMN_HPP
#define DISPLAY_COLUMN_HPP

#include <string>

using std::string;

class DisplayColumn 
{

public:
    DisplayColumn() = delete;
    DisplayColumn(const std::string _key, 
                    const std::string _title,
                    const std::string _format,
                    size_t _width);
    // ~DisplayColumn() = default;

    const std::string key;
    const std::string title;
    const std::string format;
    size_t width;
    
};


#endif
