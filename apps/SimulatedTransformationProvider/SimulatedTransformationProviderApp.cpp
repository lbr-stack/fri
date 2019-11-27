/**

The following license terms and conditions apply, unless a redistribution
agreement or other license is obtained by KUKA Roboter GmbH, Augsburg, Germany.

SCOPE

The software "KUKA Sunrise.Connectivity FRI Client SDK" is targeted to work in
conjunction with the "KUKA Sunrise.Connectivity FastRobotInterface" toolkit.
In the following, the term "software" refers to all material directly
belonging to the provided SDK "Software development kit", particularly source
code, libraries, binaries, manuals and technical documentation.

COPYRIGHT

All Rights Reserved
Copyright (C)  2014-2019 
KUKA Roboter GmbH
Augsburg, Germany

LICENSE 

Redistribution and use of the software in source and binary forms, with or
without modification, are permitted provided that the following conditions are
met:
a) The software is used in conjunction with KUKA products only. 
b) Redistributions of source code must retain the above copyright notice, this
list of conditions and the disclaimer.
c) Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the disclaimer in the documentation and/or other
materials provided with the distribution. Altered source code of the
redistribution must be made available upon request with the distribution.
d) Modification and contributions to the original software provided by KUKA
must be clearly marked and the authorship must be stated.
e) Neither the name of KUKA nor the trademarks owned by KUKA may be used to
endorse or promote products derived from this software without specific prior
written permission.

DISCLAIMER OF WARRANTY

The Software is provided "AS IS" and "WITH ALL FAULTS," without warranty of
any kind, including without limitation the warranties of merchantability,
fitness for a particular purpose and non-infringement. 
KUKA makes no warranty that the Software is free of defects or is suitable for
any particular purpose. In no event shall KUKA be responsible for loss or
damages arising from the installation or use of the Software, including but
not limited to any indirect, punitive, special, incidental or consequential
damages of any character including, without limitation, damages for loss of
goodwill, work stoppage, computer failure or malfunction, or any and all other
commercial damages or losses. 
The entire risk to the quality and performance of the Software is not borne by
KUKA. Should the Software prove defective, KUKA is not liable for the entire
cost of any service and repair.



\file
\version {1.15}
*/
#include <cstdlib>
#include <cstdio>
#include <cstring> // strstr
#include <fri/friLBRClient.h>
#include <SimulatedTransformationProviderClient.h>
#include <fri/friUdpConnection.h>
#include <fri/friClientApplication.h>

using namespace KUKA::FRI;

#define DEFAULT_PORTID 30200
#define DEFAULT_FRI_MS 1
#define DEFAULT_SENSOR_MS 1
#define DEFAULT_SLOW_DOWN 1
#define DEFAULT_WAIT_BEFORE_START_MS 1000


int main (int argc, char** argv)
{
   // parse command line arguments
   if (argc > 1)
   {
	   if ( strstr (argv[1],"help") != NULL)
	   {
	      printf(
	            "\nKUKA simulated transformation provider test application\n\n"
	            "\tCommand line arguments:\n"
	            "\t1) FRI send period (ms)(optional)\n"
	            "\t2) Sensor sampling rate (ms)(optional)\n"
               "\t3) Slow down factor(optional)\n"
	            "\t4) Wait time before starting motion (ms) (optional)\n"
	            "\t5) remote hostname (optional)\n"
               "\t6) port ID (optional)\n"
	      );
	      return 1;
	   }
   }
   int fri_MS = (argc >= 2) ? atoi(argv[1]) : DEFAULT_FRI_MS;
   int sensor_MS = (argc >= 3) ? atoi(argv[2]) : DEFAULT_SENSOR_MS;
   int slowDownFactor = (argc >= 4) ? atoi(argv[3]) : DEFAULT_SLOW_DOWN;
   int initialWaitMs = (argc >= 5) ? atoi(argv[4]) : DEFAULT_WAIT_BEFORE_START_MS;
   char* hostname = (argc >= 6) ? argv[5] : NULL;
   int port = (argc >= 7) ? atoi(argv[6]) : DEFAULT_PORTID;

   /***************************************************************************/
   /*                                                                         */
   /*   Place user Client Code here                                           */
   /*                                                                         */
   /**************************************************************************/
   
   // create new simulated transformation provider client
   SimulatedTransformationProviderClient trafoClient(fri_MS, sensor_MS, slowDownFactor, initialWaitMs);

   /***************************************************************************/
   /*                                                                         */
   /*   Standard application structure                                        */
   /*   Configuration                                                         */
   /*                                                                         */
   /***************************************************************************/

   // create new udp connection
   UdpConnection connection;


   // pass connection and client to a new FRI client application
   LBRClient lbrClient;
   ClientApplication app(connection, lbrClient, trafoClient);

   // connect client application to KUKA Sunrise controller
   app.connect(port, hostname);

   /***************************************************************************/
   /*                                                                         */
   /*   Standard application structure                                        */
   /*   Execution mainloop                                                    */
   /*                                                                         */
   /***************************************************************************/

   // repeatedly call the step routine to receive and process FRI packets
   bool success = true;
   while (success)
   {
      success = app.step();
      
      // check if we are in IDLE because the FRI session was closed
      if (lbrClient.robotState().getSessionState() == IDLE)
      {
         // In this demo application we simply quit.
         // Waiting for a new FRI session would be another possibility.
         break;
      }
   }

   /***************************************************************************/
   /*                                                                         */
   /*   Standard application structure                                        */
   /*   Dispose                                                               */
   /*                                                                         */
   /***************************************************************************/

   printf("Leaving...");
   
   // disconnect from controller
   app.disconnect();
   
   return 1;
}
