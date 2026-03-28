#include "data_layer/gpio_device/water_level_sensor.h"

#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
WaterLevelSensor::WaterLevelSensor(int type,
                             const std::string& deviceId,
                             const std::string& name,
                             int pin,
                             const std::string& direction)
                :GPIOInputDevice(type,deviceId,name,pin,direction) 
{

}  

std::unique_ptr<DeviceStatus> WaterLevelSensor::getStatus() const {
    return std::make_unique<WaterLevelSensorStatus>();
}

WaterLevelSensorStatus WaterLevelSensor::queryStatus() {
  if(!isGPIOExport()) {
    if(!exportGPIO()) {
      return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::UNKNOW);
    }
    if(!setGPIOInput()) {
      return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::UNKNOW);
    }
  }
  if(!setWaterLevelSensorValue()) return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::UNKNOW);
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
    if(val1 == 0) return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::ABNORMAL);
    return WaterLevelSensorStatus(this->getDeviceId(),5,this->getName(),WaterLevelStatus::NORMAL);
  } else {
    if(val2 == 0) return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::ABNORMAL);
    else if(val2 == 1) return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::NORMAL);
    else return WaterLevelSensorStatus(this->getDeviceId(),6,this->getName(),WaterLevelStatus::UNKNOW);
  }
}

bool WaterLevelSensor::isGPIOExport() {
  struct stat st;
  return stat((buildGPIOPath() + "/gpio" + buildGPIONum()).c_str(),&st) == 0;
}
void WaterLevelSensor::exitGPIO() {

}

bool WaterLevelSensor::exportGPIO() {
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
bool WaterLevelSensor::setGPIOInput() {
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

bool WaterLevelSensor::setWaterLevelSensorValue() {
  std::ifstream dirCheck(buildGPIOPath() + "gpio" + buildGPIONum() + "/direction");
  std::string currentDir;
  dirCheck >> currentDir;
  dirCheck.close();

  std::ofstream valueFile(buildGPIOPath() + "gpio" + buildGPIONum() + "/value");
  if(!valueFile.is_open()) return false;
  valueFile << 1;
  valueFile.close();
  usleep(50000);
  return true;
}

std::string WaterLevelSensor::buildGPIONum() {
  return std::to_string(this->getPin());
}
std::string WaterLevelSensor::buildGPIOPath() {
  return "/sys/class/gpio/";
}
