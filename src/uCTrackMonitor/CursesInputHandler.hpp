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

#ifndef CURSES_INPUT_HANDLER_HPP
#define CURSES_INPUT_HANDLER_HPP

#include <string>
// #include <memory>

#include "CursesRenderer.hpp"

using std::string;

class CursesInputHandler
{
    public:
        CursesInputHandler();

        void configureCurses();

        virtual ~CursesInputHandler() {};

        void handleInput();
        int handleKeyStroke(const char key);

        bool inHotKeyMode() const;
        const string& getCommand() const;

    private:
        int handleHotKeys(const char key);
        int handleLongCommands(const string& commandString);

        void shutdownCurses();

    private:
        bool long_input_mode;
        int input_index;
        string command;

        CursesRenderer renderer;

};


#endif
