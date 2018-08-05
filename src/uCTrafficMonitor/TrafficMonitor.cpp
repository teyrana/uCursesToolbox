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


#include <iterator>
#include "MBUtils.h"

#include "TrafficMonitor.hpp"

using namespace std;

//---------------------------------------------------------
// Constructor

TrafficMonitor::TrafficMonitor()
{


}

//---------------------------------------------------------
// Procedure: OnNewMail

bool TrafficMonitor::OnNewMail(MOOSMSG_LIST &NewMail)
{
    MOOSMSG_LIST::iterator p;
    for(p = NewMail.begin(); p!=NewMail.end(); p++) {
        CMOOSMsg &msg = *p;

        string key = msg.GetKey();

        // no-op

    }
    return(true);
}


//---------------------------------------------------------
// Procedure: OnConnectToServer

bool TrafficMonitor::OnConnectToServer()
{
    // this is the only registration
    Register("NODE_REPORT", 0);

    return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()

bool TrafficMonitor::Iterate()
{
    // m_iterations++;
    //
    // unsigned int i, amt = (m_tally_recd - m_tally_sent);
    // for(i=0; i<amt; i++) {
    //     m_tally_sent++;
    //     Notify(m_outgoing_var, m_tally_sent);
    // }
    //
    // // If this is the first iteration just note the start time, otherwise
    // // note the currently calculated frequency and post it to the DB.
    // if(m_start_time_iterations == 0)
    // m_start_time_iterations = MOOSTime();
    // else {
    //     double delta_time = (MOOSTime() - m_start_time_iterations) + 0.01;
    //     double frequency  = (double)(m_iterations) / delta_time;
    //     Notify(m_outgoing_var+"_ITER_HZ", frequency);
    // }
    //
    //
    // // If this is the first time a received msg has been noted, just
    // // note the start time, otherwise calculate and post the frequency.
    // if(amt > 0) {
    //     if(m_start_time_postings == 0)
    //     m_start_time_postings = MOOSTime();
    //     else {
    //         double delta_time = (MOOSTime() - m_start_time_postings) + 0.01;
    //         double frequency = (double)(m_tally_sent) / delta_time;
    //         Notify(m_outgoing_var+"_POST_HZ", frequency);
    //     }
    // }
    return(true);
}



//---------------------------------------------------------
// Procedure: OnStartUp()
//      Note: happens before connection is open

bool TrafficMonitor::OnStartUp()
{
    STRING_LIST sParams;
    m_MissionReader.GetConfiguration(GetAppName(), sParams);
    //
    // STRING_LIST::iterator p;
    // for(p = sParams.begin();p!=sParams.end();p++) {
    //     string line  = *p;
    //     string param = tolower(biteStringX(line, '='));
    //     string value = line;
    //
    //     if(param == "incoming_var")
    //     m_incoming_var = value;
    //
    //     else if(param == "outgoing_var")
    //     m_outgoing_var = value;
    // }

    return(true);
}
