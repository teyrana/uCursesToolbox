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
#include <signal.h>

#include "CursesRenderer.hpp"

/* If an xterm is resized the contents on your text windows might be messed up.
To handle this gracefully you should redraw all the stuff based on the new
height and width of the screen. When resizing happens, your program is sent
a SIGWINCH signal. You should catch this signal and do redrawing accordingly.
*/
void resizeHandler(int sig)
{
    int h, w;

    // this simply doesn't update h&w under OSX when using terminal
    getmaxyx(stdscr, h, w);
    fprintf(stderr, "Resizing: (h= %d, w= %d )\n", h, w);
    fprintf(stderr, "Resizing: (LINES= %d, COLS= %d )\n", LINES, COLS);
    refresh();
}

CursesRenderer::CursesRenderer()
{
  // SIGWINCH ~= SIGnal-WINdow-CHange
  signal(SIGWINCH, resizeHandler);
}

void CursesRenderer::configureCurses(){
}

void CursesRenderer::renderInput( const bool hotKeyMode, const string& command){
    if(hotKeyMode){
        mvprintw(LINES-1, 0, ">> ");
        mvprintw(LINES-1, 3, command.c_str());
        printw("\n");
    }else{
        mvprintw(LINES-1, 0, command.c_str());
        if( 1 == command.size()){
            printw(" (%d)", static_cast<int>(command[0]));
        }
        printw("\n");
    }
    return;
}


void CursesRenderer::renderStatusBar(){
    move(LINES-2,0);

    attron(A_REVERSE);
    {
        printw("============");  // chunks of 12
        printw("============");
        printw("==== %4d/%4d Tracks ==== ", (int)1, (int)1);
        printw("============");
        printw("============");

        rightFillStatusBar();
    }
    attroff(A_REVERSE);
    return;
}

void CursesRenderer::rightFillStatusBar(){
    int x, y, columns_remaining;
    getyx(stdscr, y, x);
    columns_remaining = COLS - x;

    while(columns_remaining > 12){
        printw("============");
        getyx(stdscr, y, x);
        columns_remaining = COLS - x;
    }

    // logically it should be 0, but that would crash ncurses :(
    while(columns_remaining > 1){
        printw("=");
        getyx(stdscr, y, x);
        columns_remaining = COLS - x;
    }
}

void CursesRenderer::renderTrackLabels(){
    mvprintw(0,0,"Source       Time           X / Y            Latitude / Longitude  \n");
    mvprintw(1,0,"=====================================================================");

    int x, y, columns_remaining;
    getyx(stdscr, y, x);
    columns_remaining = COLS - x;

    while(columns_remaining > 12){
        printw("============");
        getyx(stdscr, y, x);
        columns_remaining = COLS - x;
    }

    // logically it should be 0, but that would crash ncurses :(
    while(columns_remaining > 1){
        printw("=");
        getyx(stdscr, y, x);
        columns_remaining = COLS - x;
    }
}

void CursesRenderer::renderTrackContents(){

    for(int trackIndex=0; trackIndex < 1/*trackList.size()*/; trackIndex++){
        mvprintw(trackIndex+2,0,"iGPS       1.1         2242.2 / 784823       55.09493 / 10.7993 \n");
    }

    return;
}

void CursesRenderer::render( const bool hotKeyMode, const string command){

    renderTrackLabels();
    renderTrackContents();

    renderStatusBar();
    renderInput(hotKeyMode, command);

    refresh();			/* Print it on to the real screen */
}
