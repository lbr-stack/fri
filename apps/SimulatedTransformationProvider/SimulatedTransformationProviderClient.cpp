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
Copyright (C)  2014-2017 
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
\version {1.14}
*/
#include <cstring>
#include <cstdio>

#include <SimulatedTransformationProviderClient.h>

#define TRAFO_SIZE 5000

const double SimulatedTransformationProviderClient::simuTrafo[TRAFO_SIZE][12] = 
{
#include <SimulatedData.inc>
};

using namespace KUKA::FRI;
//******************************************************************************
SimulatedTransformationProviderClient::SimulatedTransformationProviderClient(int friMS, int sensorMS, int slowDownFactor, int waitBeforeStartMS) 
: _friMS(friMS),
  _sensorMS(sensorMS),
  _slowDownFactor(slowDownFactor),
  _waitBeforeStartMS(waitBeforeStartMS),
  _millisecondsExpired(0)
{
   if (_slowDownFactor > _friMS)
   {
      _slowDownFactor = _friMS;
      printf("Slow down factor must not be larger than FRI send period!\n");
   }
	printf("SimulatedTransformationProviderClient initialized:\n"
		"\tFRI send period (ms): %d\n"
		"\tSensor sampling rate (ms): %d\n"
		"\tSlow down factor: %d\n"
      "\tWait time before starting (ms): %d\n",
      _friMS, _sensorMS, _slowDownFactor, _waitBeforeStartMS);
}

//******************************************************************************
SimulatedTransformationProviderClient::~SimulatedTransformationProviderClient()
{
   
}

void SimulatedTransformationProviderClient::updateCurrentSensorData(int idx, int ageOfDataMS)
{
   memcpy(_currentSensorData, &simuTrafo[idx][0], 12 * sizeof(double));
   _currentTimestampSec = getTimestampSec();
   _currentTimestampNanoSec = getTimestampNanoSec();
    
   // estimate timestamp when sensor was sampled from current timestamp and ageOfData
   if (ageOfDataMS > 0)
   {
      unsigned int ageOfDataNanoSec = ageOfDataMS * 1000000;
      
      while (ageOfDataNanoSec > _currentTimestampNanoSec)
      {
         ageOfDataNanoSec -= _currentTimestampNanoSec;
         _currentTimestampSec -= 1;
         _currentTimestampNanoSec = 1000000000; // 1 sec
      }
      _currentTimestampNanoSec -= ageOfDataNanoSec;
   }
}

void SimulatedTransformationProviderClient::provide()
{
   // update time since first callback
   _millisecondsExpired += _friMS;
   // compute age of sensor data in milliseconds
   int ageOfDataMs = _millisecondsExpired % _sensorMS;
   // compute index for the current sensor data
   int trafoIdx = ((_millisecondsExpired - ageOfDataMs) - _waitBeforeStartMS) / _slowDownFactor;
   // when out of bounds, we repeat the first or the last transformation
   if (trafoIdx < 0)
   {
      trafoIdx = 0;
   }
   else if (trafoIdx >= TRAFO_SIZE)
   {
      trafoIdx = TRAFO_SIZE - 1;
   }
   
   updateCurrentSensorData(trafoIdx, ageOfDataMs);
   
   // provide transformation
	setTransformation(getRequestedTransformationIDs()[0], 
	      _currentSensorData, _currentTimestampSec, _currentTimestampNanoSec);
}

