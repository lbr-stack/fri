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
#ifndef _KUKA_SIMULATED_TRANSFORMATION_PROVIDER_H
#define _KUKA_SIMULATED_TRANSFORMATION_PROVIDER_H

#include <fri/friTransformationClient.h>

/**
 * \brief Test client that sends back simulated transformations corresponding to a
 * slight translation with change of orientation in Cartesian space (duration is 5s,
 * then it will loop). One can simulate a real sensor by setting a sampling rate
 * for the sensor (i.e. when are transformations and corresponding timestamps updated)
 * as well as providing the sampling rate by FRI (i.e. at what frequency is the 
 * client polled by the robot controller).
 */
class SimulatedTransformationProviderClient : public KUKA::FRI::TransformationClient
{
   
public:
      
   /**
    * \brief Constructor.
    * 
    * @param friMs sending period from FRI (e.g. when 4 each fourth transformation sample is sent back)
    * @param sensorMs simulated sensor sampling rate (when is the transformation updated)
    * @param slowDownFactor slow down factor for motion (must not be larger than FRI send period)
    * @param waitBeforeStart wait for so many milliseconds before starting motion
    */
   SimulatedTransformationProviderClient(int friMS, int sensorMS, int slowDownFactor, int waitBeforeStartMS);
   
   /** 
    * \brief Destructor.
    */
   ~SimulatedTransformationProviderClient();
   
   virtual void provide();
      
private:
   
   static const double simuTrafo[5000][12];  //!< array with simulated transformation data
   
   const int _friMS;                      //!< FRI send period in ms
   const int _sensorMS;                   //!< Sensor sampling rate in ms
   int _slowDownFactor;                   //!< Slow down factor for motion
   const int _waitBeforeStartMS;          //!< wait for so many milliseconds before starting motion
   
   double _currentSensorData[3][4];       //!< current sensor data to send
   unsigned int _currentTimestampSec;     //!< timestamp for current sensor data (sec)
   unsigned int _currentTimestampNanoSec; //!< timestamp for current sensor data (nanosec)
   
   int _millisecondsExpired;              //!< milliseconds expired since first callback
   
   void updateCurrentSensorData(int idx, int ageOfDataMS);
};

#endif // _KUKA_SIMULATED_TRANSFORMATION_PROVIDER_H
