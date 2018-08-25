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
#include <vector>

#include "Track.hpp"

class CursesRenderer
{
    public:
        CursesRenderer();

        virtual ~CursesRenderer();

        void loadTrack(const Track & newTrack);

        void render();

    private:
        void renderInput();
        void renderStatusBar();
        void renderTrackLabels();
        void renderTrackContents();

        void rightFillStatusBar();
        void handleKeyStrokes(const char key);
        void handleHotKeys(const char key);
        void handleLongCommands(const string& commandString);

        void shutdownCurses();

    protected:
        bool long_input_mode;
        int input_index;
        string command;

};


#endif
