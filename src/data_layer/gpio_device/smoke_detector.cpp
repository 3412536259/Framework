#include "data_layer/gpio_device/smoke_detector.h"

#include <cstring>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
SmokeDetector::SmokeDetector(int type,
                             const std::string& deviceId,
                             const std::string& name,
                             int pin,
                             const std::string& direction)
                : GPIOInputDevice(type,deviceId,name,pin,direction)
{

}        

std::unique_ptr<DeviceStatus> SmokeDetector::getStatus() const {
    return std::make_unique<SmokeDetectorStatus>();
}

SmokeDetectorStatus SmokeDetector::queryStatus() {
  if(!isGPIOExport()) {
    if(!exportGPIO()) {
      return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::UNKNOW);
    }
    if(!setGPIOInput()) {
      return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::UNKNOW);
    }
  }
  int val1,val2;
  std::ifstream valueFile(buildGPIOPath() + "gpio" + buildGPIONum() + "/value");
  if(!valueFile.is_open()) {
    //日志
  }
  valueFile >> val1;
  valueFile.close();
  usleep(10000);
  std::ifstream valueFile2(buildGPIOPath() + "gpio" + buildGPIONum() + "/value");
  valueFile2 >> val2;
  valueFile2.close();
  if(val1 == val2 ) {
    if(val1 == 0) return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::ALARM);
    return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::NORMAL);
  } else {
    if(val2 == 0) return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::ALARM);
    else if(val2 == 1) return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::NORMAL);
    else return SmokeDetectorStatus(this->getDeviceId(),5,this->getName(),SmokeStatus::UNKNOW);
  }
}

bool SmokeDetector::isGPIOExport() {
  struct stat st;
  return stat((buildGPIOPath() + "/gpio" + buildGPIONum()).c_str(),&st) == 0;
}
void SmokeDetector::exitGPIO() {

}
bool SmokeDetector::exportGPIO() {
  std::string gpioPath = buildGPIOPath();
  std::ifstream gpioDir(gpioPath + "gpio" + buildGPIONum());
  if(!gpioDir.good()) {
    std::ofstream exportFile(gpioPath + "export");
    if(!exportFile.is_open()) {
      //日志
      return false;
    }
    exportFile << buildGPIONum();
    exportFile.close();
    usleep(200000);//延长初始化时间，匹配主板时序（200ms）
  }
  gpioDir.close();
  return true;
}
bool SmokeDetector::setGPIOInput() {
  std::ofstream dirFile(buildGPIOPath() + "gpio" + buildGPIONum() + "/direction");
  if(!dirFile.is_open()){
    //日志
    return false;
  }
  dirFile << this->getDirection();
  dirFile.close();
  usleep(100000);
  return true;
}

std::string SmokeDetector::buildGPIONum() {
  return std::to_string(this->getPin());
}
std::string SmokeDetector::buildGPIOPath() {
  return "/sys/class/gpio/";
}
