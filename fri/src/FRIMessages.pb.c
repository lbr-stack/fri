/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.2.8 at Tue Feb 14 12:42:03 2017. */

#include <fri/FRIMessages.pb.h>



const pb_field_t JointValues_fields[2] = {
    PB_FIELD2(  1, DOUBLE  , REPEATED, CALLBACK, FIRST, JointValues, value, value, 0),
    PB_LAST_FIELD
};

const pb_field_t TimeStamp_fields[3] = {
    PB_FIELD2(  1, UINT32  , REQUIRED, STATIC  , FIRST, TimeStamp, sec, sec, 0),
    PB_FIELD2(  2, UINT32  , REQUIRED, STATIC  , OTHER, TimeStamp, nanosec, sec, 0),
    PB_LAST_FIELD
};

const pb_field_t CartesianVector_fields[2] = {
    PB_FIELD2(  1, DOUBLE  , REPEATED, STATIC  , FIRST, CartesianVector, element, element, 0),
    PB_LAST_FIELD
};

const pb_field_t Checksum_fields[2] = {
    PB_FIELD2(  1, INT32   , OPTIONAL, STATIC  , FIRST, Checksum, crc32, crc32, 0),
    PB_LAST_FIELD
};

const pb_field_t Transformation_fields[4] = {
    PB_FIELD2(  1, STRING  , REQUIRED, STATIC  , FIRST, Transformation, name, name, 0),
    PB_FIELD2(  2, DOUBLE  , REPEATED, STATIC  , OTHER, Transformation, matrix, name, 0),
    PB_FIELD2(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, Transformation, timestamp, matrix, &TimeStamp_fields),
    PB_LAST_FIELD
};

const pb_field_t FriIOValue_fields[6] = {
    PB_FIELD2(  1, STRING  , REQUIRED, STATIC  , FIRST, FriIOValue, name, name, 0),
    PB_FIELD2(  2, ENUM    , REQUIRED, STATIC  , OTHER, FriIOValue, type, name, 0),
    PB_FIELD2(  3, ENUM    , REQUIRED, STATIC  , OTHER, FriIOValue, direction, type, 0),
    PB_FIELD2(  4, UINT64  , OPTIONAL, STATIC  , OTHER, FriIOValue, digitalValue, direction, 0),
    PB_FIELD2(  5, DOUBLE  , OPTIONAL, STATIC  , OTHER, FriIOValue, analogValue, digitalValue, 0),
    PB_LAST_FIELD
};

const pb_field_t MessageHeader_fields[4] = {
    PB_FIELD2(  1, UINT32  , REQUIRED, STATIC  , FIRST, MessageHeader, messageIdentifier, messageIdentifier, 0),
    PB_FIELD2(  2, UINT32  , REQUIRED, STATIC  , OTHER, MessageHeader, sequenceCounter, messageIdentifier, 0),
    PB_FIELD2(  3, UINT32  , REQUIRED, STATIC  , OTHER, MessageHeader, reflectedSequenceCounter, sequenceCounter, 0),
    PB_LAST_FIELD
};

const pb_field_t ConnectionInfo_fields[5] = {
    PB_FIELD2(  1, ENUM    , REQUIRED, STATIC  , FIRST, ConnectionInfo, sessionState, sessionState, 0),
    PB_FIELD2(  2, ENUM    , REQUIRED, STATIC  , OTHER, ConnectionInfo, quality, sessionState, 0),
    PB_FIELD2(  3, UINT32  , OPTIONAL, STATIC  , OTHER, ConnectionInfo, sendPeriod, quality, 0),
    PB_FIELD2(  4, UINT32  , OPTIONAL, STATIC  , OTHER, ConnectionInfo, receiveMultiplier, sendPeriod, 0),
    PB_LAST_FIELD
};

const pb_field_t RobotInfo_fields[6] = {
    PB_FIELD2(  1, INT32   , OPTIONAL, STATIC  , FIRST, RobotInfo, numberOfJoints, numberOfJoints, 0),
    PB_FIELD2(  2, ENUM    , OPTIONAL, STATIC  , OTHER, RobotInfo, safetyState, numberOfJoints, 0),
    PB_FIELD2(  5, ENUM    , REPEATED, CALLBACK, OTHER, RobotInfo, driveState, safetyState, 0),
    PB_FIELD2(  6, ENUM    , OPTIONAL, STATIC  , OTHER, RobotInfo, operationMode, driveState, 0),
    PB_FIELD2(  7, ENUM    , OPTIONAL, STATIC  , OTHER, RobotInfo, controlMode, operationMode, 0),
    PB_LAST_FIELD
};

const pb_field_t MessageMonitorData_fields[8] = {
    PB_FIELD2(  1, MESSAGE , OPTIONAL, STATIC  , FIRST, MessageMonitorData, measuredJointPosition, measuredJointPosition, &JointValues_fields),
    PB_FIELD2(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageMonitorData, measuredTorque, measuredJointPosition, &JointValues_fields),
    PB_FIELD2(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageMonitorData, commandedJointPosition, measuredTorque, &JointValues_fields),
    PB_FIELD2(  4, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageMonitorData, commandedTorque, commandedJointPosition, &JointValues_fields),
    PB_FIELD2(  5, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageMonitorData, externalTorque, commandedTorque, &JointValues_fields),
    PB_FIELD2(  8, MESSAGE , REPEATED, STATIC  , OTHER, MessageMonitorData, readIORequest, externalTorque, &FriIOValue_fields),
    PB_FIELD2( 15, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageMonitorData, timestamp, readIORequest, &TimeStamp_fields),
    PB_LAST_FIELD
};

const pb_field_t MessageIpoData_fields[5] = {
    PB_FIELD2(  1, MESSAGE , OPTIONAL, STATIC  , FIRST, MessageIpoData, jointPosition, jointPosition, &JointValues_fields),
    PB_FIELD2( 10, ENUM    , OPTIONAL, STATIC  , OTHER, MessageIpoData, clientCommandMode, jointPosition, 0),
    PB_FIELD2( 11, ENUM    , OPTIONAL, STATIC  , OTHER, MessageIpoData, overlayType, clientCommandMode, 0),
    PB_FIELD2( 12, DOUBLE  , OPTIONAL, STATIC  , OTHER, MessageIpoData, trackingPerformance, overlayType, 0),
    PB_LAST_FIELD
};

const pb_field_t MessageCommandData_fields[6] = {
    PB_FIELD2(  1, MESSAGE , OPTIONAL, STATIC  , FIRST, MessageCommandData, jointPosition, jointPosition, &JointValues_fields),
    PB_FIELD2(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageCommandData, cartesianWrenchFeedForward, jointPosition, &CartesianVector_fields),
    PB_FIELD2(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageCommandData, jointTorque, cartesianWrenchFeedForward, &JointValues_fields),
    PB_FIELD2(  4, MESSAGE , REPEATED, STATIC  , OTHER, MessageCommandData, commandedTransformations, jointTorque, &Transformation_fields),
    PB_FIELD2(  5, MESSAGE , REPEATED, STATIC  , OTHER, MessageCommandData, writeIORequest, commandedTransformations, &FriIOValue_fields),
    PB_LAST_FIELD
};

const pb_field_t MessageEndOf_fields[3] = {
    PB_FIELD2(  1, INT32   , OPTIONAL, STATIC  , FIRST, MessageEndOf, messageLength, messageLength, 0),
    PB_FIELD2(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, MessageEndOf, messageChecksum, messageLength, &Checksum_fields),
    PB_LAST_FIELD
};

const pb_field_t FRIMonitoringMessage_fields[8] = {
    PB_FIELD2(  1, MESSAGE , REQUIRED, STATIC  , FIRST, FRIMonitoringMessage, header, header, &MessageHeader_fields),
    PB_FIELD2(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, FRIMonitoringMessage, robotInfo, header, &RobotInfo_fields),
    PB_FIELD2(  3, MESSAGE , OPTIONAL, STATIC  , OTHER, FRIMonitoringMessage, monitorData, robotInfo, &MessageMonitorData_fields),
    PB_FIELD2(  4, MESSAGE , OPTIONAL, STATIC  , OTHER, FRIMonitoringMessage, connectionInfo, monitorData, &ConnectionInfo_fields),
    PB_FIELD2(  5, MESSAGE , OPTIONAL, STATIC  , OTHER, FRIMonitoringMessage, ipoData, connectionInfo, &MessageIpoData_fields),
    PB_FIELD2(  6, MESSAGE , REPEATED, STATIC  , OTHER, FRIMonitoringMessage, requestedTransformations, ipoData, &Transformation_fields),
    PB_FIELD2( 15, MESSAGE , OPTIONAL, STATIC  , OTHER, FRIMonitoringMessage, endOfMessageData, requestedTransformations, &MessageEndOf_fields),
    PB_LAST_FIELD
};

const pb_field_t FRICommandMessage_fields[4] = {
    PB_FIELD2(  1, MESSAGE , REQUIRED, STATIC  , FIRST, FRICommandMessage, header, header, &MessageHeader_fields),
    PB_FIELD2(  2, MESSAGE , OPTIONAL, STATIC  , OTHER, FRICommandMessage, commandData, header, &MessageCommandData_fields),
    PB_FIELD2( 15, MESSAGE , OPTIONAL, STATIC  , OTHER, FRICommandMessage, endOfMessageData, commandData, &MessageEndOf_fields),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
STATIC_ASSERT((pb_membersize(Transformation, timestamp) < 65536 && pb_membersize(MessageMonitorData, measuredJointPosition) < 65536 && pb_membersize(MessageMonitorData, measuredTorque) < 65536 && pb_membersize(MessageMonitorData, commandedJointPosition) < 65536 && pb_membersize(MessageMonitorData, commandedTorque) < 65536 && pb_membersize(MessageMonitorData, externalTorque) < 65536 && pb_membersize(MessageMonitorData, readIORequest[0]) < 65536 && pb_membersize(MessageMonitorData, timestamp) < 65536 && pb_membersize(MessageIpoData, jointPosition) < 65536 && pb_membersize(MessageCommandData, jointPosition) < 65536 && pb_membersize(MessageCommandData, cartesianWrenchFeedForward) < 65536 && pb_membersize(MessageCommandData, jointTorque) < 65536 && pb_membersize(MessageCommandData, commandedTransformations[0]) < 65536 && pb_membersize(MessageCommandData, writeIORequest[0]) < 65536 && pb_membersize(MessageEndOf, messageChecksum) < 65536 && pb_membersize(FRIMonitoringMessage, header) < 65536 && pb_membersize(FRIMonitoringMessage, connectionInfo) < 65536 && pb_membersize(FRIMonitoringMessage, robotInfo) < 65536 && pb_membersize(FRIMonitoringMessage, monitorData) < 65536 && pb_membersize(FRIMonitoringMessage, ipoData) < 65536 && pb_membersize(FRIMonitoringMessage, requestedTransformations[0]) < 65536 && pb_membersize(FRIMonitoringMessage, endOfMessageData) < 65536 && pb_membersize(FRICommandMessage, header) < 65536 && pb_membersize(FRICommandMessage, commandData) < 65536 && pb_membersize(FRICommandMessage, endOfMessageData) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_JointValues_TimeStamp_CartesianVector_Checksum_Transformation_FriIOValue_MessageHeader_ConnectionInfo_RobotInfo_MessageMonitorData_MessageIpoData_MessageCommandData_MessageEndOf_FRIMonitoringMessage_FRICommandMessage)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
STATIC_ASSERT((pb_membersize(Transformation, timestamp) < 256 && pb_membersize(MessageMonitorData, measuredJointPosition) < 256 && pb_membersize(MessageMonitorData, measuredTorque) < 256 && pb_membersize(MessageMonitorData, commandedJointPosition) < 256 && pb_membersize(MessageMonitorData, commandedTorque) < 256 && pb_membersize(MessageMonitorData, externalTorque) < 256 && pb_membersize(MessageMonitorData, readIORequest[0]) < 256 && pb_membersize(MessageMonitorData, timestamp) < 256 && pb_membersize(MessageIpoData, jointPosition) < 256 && pb_membersize(MessageCommandData, jointPosition) < 256 && pb_membersize(MessageCommandData, cartesianWrenchFeedForward) < 256 && pb_membersize(MessageCommandData, jointTorque) < 256 && pb_membersize(MessageCommandData, commandedTransformations[0]) < 256 && pb_membersize(MessageCommandData, writeIORequest[0]) < 256 && pb_membersize(MessageEndOf, messageChecksum) < 256 && pb_membersize(FRIMonitoringMessage, header) < 256 && pb_membersize(FRIMonitoringMessage, connectionInfo) < 256 && pb_membersize(FRIMonitoringMessage, robotInfo) < 256 && pb_membersize(FRIMonitoringMessage, monitorData) < 256 && pb_membersize(FRIMonitoringMessage, ipoData) < 256 && pb_membersize(FRIMonitoringMessage, requestedTransformations[0]) < 256 && pb_membersize(FRIMonitoringMessage, endOfMessageData) < 256 && pb_membersize(FRICommandMessage, header) < 256 && pb_membersize(FRICommandMessage, commandData) < 256 && pb_membersize(FRICommandMessage, endOfMessageData) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_JointValues_TimeStamp_CartesianVector_Checksum_Transformation_FriIOValue_MessageHeader_ConnectionInfo_RobotInfo_MessageMonitorData_MessageIpoData_MessageCommandData_MessageEndOf_FRIMonitoringMessage_FRICommandMessage)
#endif


/* On some platforms (such as AVR), double is really float.
 * These are not directly supported by nanopb, but see example_avr_double.
 * To get rid of this error, remove any double fields from your .proto.
 */
STATIC_ASSERT(sizeof(double) == 8, DOUBLE_MUST_BE_8_BYTES)

