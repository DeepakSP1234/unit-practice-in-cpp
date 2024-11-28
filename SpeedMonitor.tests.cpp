#include <gtest/gtest.h>
#include "SpeedMonitor.h"
uisng namespace testing;

// Stub Implementation
class LoggerTestDoubleStub:public ILogger{
public:
  void write(const string& msg){
  }
};

class LoggerTestDoubleMock:public ILogger{
public:
  int writeCallCount = 0;
  string write_Msg_ArgValue = "";
  void write(const string& msg){
    write_Msg_ArgValue = msg;
  }
};

class SpeedSendorTestDoubleStub:public ISpeedSensor {
public:
  int getCurrentSpeed(){
      return 50;
  }
};

class CommunicatorTestDoubleStub:public ICloudCommunicatior{
public:
  int pushMessage(const string& message){  return 200;}
};
 

TEST(SpeeMonitorTestSuite,AssertValidSpeedMonitorInstantiation){
    //Arrange
    LoggerTestDoubleStub       loggerStub;
    CommunicatorTestDoubleStub communicatorStub;
    SpeedSendorTestDoubleStub  speedSensorStub;
    //ACT
    SpeedMonitor objUnderTest {40,&loggerStub,&speedSensorStub,&communicatorStub } ;
    //Assert
    ASSERT_EQ(40, objUnderTest.getSpeedThreshold());
    
}


TEST(SpeeMonitorTestSuite,VerifyValidSpeedThresholdState){
  //interaction- Behavior-Commnication  Testing
    LoggerTestDoubleMock loggerMock;
    CommunicatorTestDoubleStub communicatorStub;
    SpeedSendorTestDoubleStub speedSensorStub;
    string expectedMessage=""_speedThreshold value must be in the ramge {1-100} 400";
    SpeedMonitor objUnderTest {400,&loggerMock,&speedSensorStub,&communicatorStub } ;
    objUnderTest.monitor();
    EXPECT_EQ(loggermock.writeCallCount,1);
    EXPECT_STREQ(loggermock.write_Msg_ArgValue,expectedMessage);
 
}



