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

#ifndef CURSES_RENDERER_HPP
#define CURSES_RENDERER_HPP

#include <memory>
#include <string>
// #include <vector>

#include "TrackCache.hpp"

using std::string;

class CursesRenderer
{
    public:
        CursesRenderer() = delete;

        CursesRenderer(TrackCache& cache);

        ~CursesRenderer() = default;

        void configure();

        bool is_paused() const;
        void pause();
        void resume();

        void set_key_command(const char command);

        void update();


    private:
        void render_command();
        void render_options();
        void render_status_bar();
        void render_column_headers();
        void render_column_contents();

        // void render_status_bar();

    private: 
        static const int footer_line_offset = -4;
        static const int option_upper_line_offset = -3;
        static const int option_lower_line_offset = -2;
        static const int status_line_offset = -1;

        TrackCache& cache;
        char command;
        bool paused;
};


#endif
