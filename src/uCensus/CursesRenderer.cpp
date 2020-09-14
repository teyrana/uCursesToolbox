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

#include <chrono>

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

CursesRenderer::CursesRenderer(TrackCache& _cache)
    : cache(_cache)
    , command(' ')
    , paused(false)
{
    // SIGWINCH ~= SIGnal-WINdow-CHange
    signal(SIGWINCH, resizeHandler);
}

void CursesRenderer::configure(){
}


bool CursesRenderer::is_paused() const {
    return paused;
}

void CursesRenderer::pause() {
    paused = true;
}

void CursesRenderer::resume() {
    paused = false;
}



void CursesRenderer::render_command(){
    // if(hotKeyMode){
    //     mvprintw(LINES-1, 0, ">> ");
    //     mvprintw(LINES-1, 3, command );
    //     printw("\n");
    // }else{
    const int status_render_line = LINES + status_line_offset;
    mvprintw(status_render_line, 0, "command:%c: <result>", command );
    // }
    return;
}

void CursesRenderer::render_options(){
    {  // upper option line:
        mvprintw(LINES + option_upper_line_offset, 0, "==== ");

    }{ // lower option line:
        mvprintw(LINES + option_lower_line_offset, 0, "==== ");
    }
}

void CursesRenderer::render_status_bar(){
    move(LINES + footer_line_offset,0);

    attron(A_REVERSE);
    {
        // chunks of 12
        printw("============ ============ ");
        printw("============ ============ ");
        printw("==== %4d/%4d Tracks ==== ", (int)1, (int)1);
    }
    attroff(A_REVERSE);
    return;
}

// void CursesRenderer::rightFillStatusBar(){
//     int x = getcurx(stdscr);
//     // int y = getcury(stdscr);

//     while(12 < (COLS - x)){
//         printw("============");
//         x += 12;
//     }

//     // logically it should be 0, but that would crash ncurses :(
//     while( 1 < (COLS - x)){
//         printw("=");
//         ++x;
//     }
// }

void CursesRenderer::render_column_headers(){
    mvprintw(0,0,"Source       Time           X / Y            Latitude / Longitude    ");
    move(1,0);
    hline(ACS_HLINE, 999);
}

void CursesRenderer::render_column_contents(){
    std::time_t current_time = std::time(nullptr);

    if(0 == cache.size()){
        // dummy / placeholder
        mvprintw( 2, 0, " < No Tracks Received > ");
    } else {
        size_t track_index = 0;
        for (auto iter = cache.cbegin(); iter != cache.cend(); ++iter) {
            const uint64_t id = iter->first;
            const Track& track = iter->second;
            
            const size_t render_line = 2 + track_index;

            const Report * const report = track.last_report.get();
            const double age = current_time - report->timestamp;
            mvprintw( render_line, 0, "%lu      %g     %g / %g  ", id, age, report->x, report->y);
            ++track_index;
        }
    }

    return;
}


void CursesRenderer::set_key_command(const char _command){
    command = _command;
}

void CursesRenderer::update(){
    if(paused)
        return;

    clear();

    render_column_headers();

    // render the columns themselves
    render_column_contents();

    // footer
    render_status_bar();
    render_options();
    render_command();

    refresh();    // Print it on to the real screen
}
