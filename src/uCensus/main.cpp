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

#include <string>
#include <vector>

#include "MBUtils.h"

#include "TrackMonitor.hpp"
#include "TrackMonitorInfo.hpp"

using std::string;

int main(int argc, char *argv[])
{
    string mission_file;
    string run_command("uCensus");
    string incoming_var;
    string outgoing_var;

    for(int i=1; i<argc; i++) {
        string argi = argv[i];
        if((argi=="-e") || (argi=="--example") || (argi=="-example")){
            showExampleConfigAndExit();
        }else if((argi == "-h") || (argi == "--help") || (argi=="-help")){
            showHelpAndExit();
        }else if((argi == "-i") || (argi == "--interface")){
            showInterfaceAndExit();
        }else if((argi == "-v") || (argi == "--version")){
            showVersionAndExit();

        // add more arguments here.

        }else if(strEnds(argi, ".moos") || strEnds(argi, ".moos++")){
            mission_file = argi;
        }else if(i==2){
            run_command = argi;
        }
    }

    if(mission_file == "")
        showHelpAndExit();

    TrackMonitor monitor;

    monitor.Run(run_command.c_str(), mission_file.c_str());

    return(0);
}
