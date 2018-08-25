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

#include <ncurses.h>

#include "CursesInputHandler.hpp"
#include "CursesRenderer.hpp"

CursesInputHandler::CursesInputHandler():
    long_input_mode(false),
    input_index(0),
    command(COLS, ' ')
{
    configureCurses();
}

void CursesInputHandler::configureCurses(){
    // initialise Ncurses
    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing NCurses: initscr() failed!!\n");
        exit(EXIT_FAILURE);
    }

    renderer.configureCurses();

    // One-character-a-time:
    // Disables the buffering of typed characters by the TTY driver;
    // get a-character-at-a-time input,
    raw();

    // No echo:
    // Suppresses the automatic echoing of typed characters:
    noecho();

    fprintf(stderr, ">> Successfully initialized Curses. >>\n");
}

bool CursesInputHandler::inHotKeyMode() const {
    return long_input_mode;
}

const string& CursesInputHandler::getCommand() const {
    return command;
}

void CursesInputHandler::handleInput(){
    renderer.render(long_input_mode, command);
    handleKeyStroke(getch());
}

int CursesInputHandler::handleKeyStroke(const char key_input){
    if(long_input_mode){
        if('\n' == key_input){
            long_input_mode = false;
            return handleLongCommands(command);
        }else{
            // merely grow the command-in-progress
            command[input_index] = key_input;
            input_index++;
        }
    }else{
        return handleHotKeys(key_input);
    }
    return 0;
}

int CursesInputHandler::handleHotKeys(const char key){
    // 17 == ctrl-q on OSX/Darwin/Terminal
    if('q' == key || 17 == key){
        // normal exit
        shutdownCurses();
        exit(0);
    }else if('\n' == key){
        long_input_mode = true;
        command.clear();
    }else{
        input_index = 0;
        command[0] = key;
    }
    return 0;
}

int CursesInputHandler::handleLongCommands(const string& commandString){
    return 0;
}

void CursesInputHandler::shutdownCurses(){
    endwin();			/* End curses mode		  */
    fprintf(stderr, "Program finished... shutting down NCurses...");
}
