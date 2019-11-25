/**

The following license terms and conditions apply, unless a redistribution
agreement or other license is obtained by KUKA Roboter GmbH, Augsburg, Germany.

SCOPE

The software �KUKA Sunrise.Connectivity FRI Client SDK� is targeted to work in
conjunction with the �KUKA Sunrise.Connectivity FastRobotInterface� toolkit.
In the following, the term �software� refers to all material directly
belonging to the provided SDK �Software development kit�, particularly source
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
#include <LBRWrenchSineOverlayClient.h>


using namespace KUKA::FRI;
//******************************************************************************
LBRWrenchSineOverlayClient::LBRWrenchSineOverlayClient(double freqHzX, double freqHzY, 
      double amplRadX, double amplRadY) 
   : _freqHzX(freqHzX)
   , _freqHzY(freqHzY)
   , _amplRadX(amplRadX)
   , _amplRadY(amplRadY)
   , _stepWidthX(0.0)
   , _stepWidthY(0.0)
   , _phiX(0.0)
   , _phiY(0.0)
{
   printf("LBRWrenchSineOverlayClient initialized:\n"
         "\tfrequency (Hz):  X = %f, Y = %f\n"
         "\tamplitude (N):   X = %f, Y = %f\n"
         , freqHzX, freqHzY, amplRadX, amplRadY);
   
   for(int i = 0; i<CART_VECTOR_DIM; i++){_wrench[i] = 0.0;}
}

//******************************************************************************
LBRWrenchSineOverlayClient::~LBRWrenchSineOverlayClient()
{
}
      
//******************************************************************************
void LBRWrenchSineOverlayClient::onStateChange(ESessionState oldState, ESessionState newState)
{
   LBRClient::onStateChange(oldState, newState);
   switch (newState)
   {
      // (re)initialize sine parameters when entering Monitoring
      case MONITORING_READY:
      {
         for(int i = 0; i<CART_VECTOR_DIM; i++){_wrench[i] = 0.0;}
         _phiX = 0.0;
         _phiY = 0.0;
         _stepWidthX = 2 * M_PI * _freqHzX * robotState().getSampleTime();
         _stepWidthY = 2 * M_PI * _freqHzY * robotState().getSampleTime();
         break;
      }
      default:
      {
         break;
      }
   }
}

//******************************************************************************
void LBRWrenchSineOverlayClient::waitForCommand()
{
   // In waitForCommand(), the joint values have to be mirrored. Which is done, by calling
   // the base method.
   LBRClient::waitForCommand();
   
   // If we want to command wrenches, we have to command them all the time. Even in
   // waitForCommand(). This has to be done due to consistency checks. In this state 
   // it is only necessary, that some wrench values are sent.
   // The LBR does not take the specific value into account.
   if (robotState().getClientCommandMode() == WRENCH)
   {
      robotCommand().setWrench(_wrench);
   }
}

//******************************************************************************
void LBRWrenchSineOverlayClient::command()
{
   // In command(), the joint values have to be sent. Which is done, by calling
   // the base method.
   LBRClient::command();
   
   if (robotState().getClientCommandMode() == WRENCH)
   {
      // calculate new forces in x and y direction
      _wrench[0] = _amplRadX * sin(_phiX);
      _wrench[1] = _amplRadY * sin(_phiY);
      
      _phiX += _stepWidthX;
      _phiY += _stepWidthY;
      if (_phiX >= 2 * M_PI) _phiX -= 2 * M_PI;   
      if (_phiY >= 2 * M_PI) _phiY -= 2 * M_PI; 
      
      robotCommand().setWrench(_wrench);
   }
}

// clean up additional defines
#ifdef _USE_MATH_DEFINES
#undef _USE_MATH_DEFINES
#endif

