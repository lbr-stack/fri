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
#include <cstring>
#include <cstdio>
// Visual studio needs extra define to use math constants
#define _USE_MATH_DEFINES
#include <math.h>
#include <LBRTorqueSineOverlayClient.h>


using namespace KUKA::FRI;

//******************************************************************************
LBRTorqueSineOverlayClient::LBRTorqueSineOverlayClient(unsigned int jointMask, 
      double freqHz, double torqueAmplitude) 
   :_jointMask(jointMask)
   , _freqHz(freqHz)
   , _torqueAmpl(torqueAmplitude)
   , _phi(0.0)
   , _stepWidth(0.0)
{
   printf("LBRTorqueSineOverlayClient initialized:\n"
         "\tjoint mask: 0x%x\n"
         "\tfrequency (Hz): %f\n"
         "\tamplitude (Nm): %f\n",
         jointMask, freqHz, torqueAmplitude);
   
   for(int i = 0; i< LBRState::NUMBER_OF_JOINTS; i++){ _torques[i] = 0.0;}
}

//******************************************************************************
LBRTorqueSineOverlayClient::~LBRTorqueSineOverlayClient()
{
}
      
//******************************************************************************
void LBRTorqueSineOverlayClient::onStateChange(ESessionState oldState, ESessionState newState)
{
   LBRClient::onStateChange(oldState, newState);
   // (re)initialize sine parameters when entering Monitoring
   switch (newState)
   {
      case MONITORING_READY:
      {
         for(int i = 0; i< LBRState::NUMBER_OF_JOINTS; i++){ _torques[i] = 0.0;}
         _phi = 0.0;
         _stepWidth = 2 * M_PI * _freqHz * robotState().getSampleTime();
         break;
      }
      default:
      {
         break;
      }
   }
}
//******************************************************************************

void LBRTorqueSineOverlayClient::waitForCommand()
{
   // In waitForCommand(), the joint values have to be mirrored. Which is done, by calling
   // the base method.
   LBRClient::waitForCommand();
   
   // If we want to command torques, we have to command them all the time; even in
   // waitForCommand(). This has to be done due to consistency checks. In this state it is 
   // only necessary, that some torque values are sent. The LBR does not take the 
   // specific value into account.
   if (robotState().getClientCommandMode() == TORQUE)
   {
      robotCommand().setTorque(_torques);
   }
}
//******************************************************************************
void LBRTorqueSineOverlayClient::command()
{
    // In command(), the joint values have to be sent. Which is done by calling
    // the base method.
    LBRClient::command();
    
    // Check for correct ClientCommandMode.
    if (robotState().getClientCommandMode() == TORQUE)
    { 
       // calculate  offset
        double offset = _torqueAmpl * sin(_phi);
       
       _phi += _stepWidth;
       if (_phi >= 2 * M_PI) _phi -= 2 * M_PI;      

       for (int i=0; i<LBRState::NUMBER_OF_JOINTS; i++)
       {
          if (_jointMask & (1<<i))
          {
              _torques[i] = offset;
          }
       }
       // Set superposed joint torques.
       robotCommand().setTorque(_torques);
    }
}

// clean up additional defines
#ifdef _USE_MATH_DEFINES
#undef _USE_MATH_DEFINES
#endif
