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

CursesRenderer::CursesRenderer():
    last_input("?")
{
    // initialise Ncurses
    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing NCurses: initscr() failed!!\n");
        exit(EXIT_FAILURE);
    }

    // SIGWINCH ~= SIGnal-WINdow-CHange
    signal(SIGWINCH, resizeHandler);

    printw("Ncurses initialized\n");
    refresh();
}

void CursesRenderer::loadTrack(const Track& newTrack){

}

void CursesRenderer::renderInput(){
    move(LINES-1,0);

    printw(last_input.c_str());
    printw("\n");

    return;
}


void CursesRenderer::renderStatusBar(){
    move(LINES-2,0);

    attron(A_REVERSE);
    {
        printw("---------------------------------");
        printw("---------------------------------");
        printw("---------------------------------");
        printw("  {:>4} Tracks\n", (int)1);
        printw("---------------------------------");
    }
    attroff(A_REVERSE);
    return;
}

void CursesRenderer::renderTracks(){
    move(0,0);

    // print header:
    printw("Source     Time           X / Y            Latitude / Longitude  \n");

    printw("iGPS       1.1       2242.2 / 784823       55.09493 / 10.7993 \n");


    // for(trackIndex=0; trackIndex < trackList.size(); trackIndex++){

    return;
}

void CursesRenderer::render(){

    renderTracks();

    renderStatusBar();

    renderInput();

    refresh();			/* Print it on to the real screen */

    char last_char_input = static_cast<char>(getch()); // don't redraw, yet.
    if('q' == last_char_input){
        exit(0);
    }
    last_input = string(1, last_char_input);
}

CursesRenderer::~CursesRenderer(){
    printw("Program finished... shutting down NCurses");
    endwin();			/* End curses mode		  */
    fprintf(stderr, "Program finished... shutting down NCurses...");
}
