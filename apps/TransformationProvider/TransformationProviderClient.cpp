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



1.15
*/
#include <cstring>
#include <cstdio>
// Visual studio needs extra define to use math constants
#define _USE_MATH_DEFINES
#include <cmath>

#include <TransformationProviderClient.h>

using namespace KUKA::FRI;
//******************************************************************************
TransformationProviderClient::TransformationProviderClient()
{
   printf("TransformationProviderClient initialized:\n");

   // create a transformation matrix which keeps the orientation of the frame but 
   // results in a translational movement
   for (int row = 0; row < 3; row++)
   {
      for (int column = 0; column < 4; column++)
      {
         if (row == column)
         {
            _transformationMatrix[row][column] = 1;
         }
         else if (column == 3)
         {
            _transformationMatrix[row][column] = 10;
         }
         else
         {
            _transformationMatrix[row][column] = 0;
         }
      }
   }
   // _transformationMatrix is now:
   // {  1, 0, 0, 10},
   // {  0, 1, 0, 10},
   // {  0, 0, 1, 10}

}

//******************************************************************************
TransformationProviderClient::~TransformationProviderClient()
{
}

//******************************************************************************
void TransformationProviderClient::provide()
{
   // Change the translational vector of the transformation matrix (all values in mm)
   double x = _transformationMatrix[0][3];
   if (x < 100)
   {
      x++;
   }
   else
   {
      x = 0;
   }
   _transformationMatrix[0][3] = x;

   double y = _transformationMatrix[1][3];
   if (y < 200)
   {
      y += 5;
   }
   else
   {
      y = 0;
   }
   _transformationMatrix[1][3] = y;

   double z = _transformationMatrix[2][3];
   if (z < 300)
   {
      z += 10;
   }
   else
   {
      z = 0;
   }
   _transformationMatrix[2][3] = z;

   //printf("X:%f, Y:%f, Z:%f\n", _transformationMatrix[0][3], _transformationMatrix[1][3], _transformationMatrix[2][3]);

   // Set new transformation matrix for frame with identifier"PBase"
   setTransformation("PBase", _transformationMatrix, getTimestampSec(),
         getTimestampNanoSec());
}

// clean up additional defines
#ifdef _USE_MATH_DEFINES
#undef _USE_MATH_DEFINES
#endif
