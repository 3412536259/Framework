#include "data_layer/gpio_device/infrared_sensor.h"

#include <thread>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <iostream>
InfraredSensor::InfraredSensor(int type,
                             const std::string& deviceId,
                             const std::string& name,
                             int pin,
                             const std::string& direction)
    : GPIOInputDevice(type,deviceId,name,pin,direction)
{

}

std::unique_ptr<DeviceStatus> InfraredSensor::getStatus() const {
    return std::unique_ptr<DeviceStatus> ();
}

InfraredSensorStatus InfraredSensor::queryStatus() {
  if(!isGPIOExport()) {
    if(!exportGPIO()) {
      // std::cout << "红外gpio导出失败: " << std::endl;
      return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::UNKNOW);
    }
    if(!setGPIOInput()) {
      // std::cout << "红外gpio设置输出失败" << std::endl;
      return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::UNKNOW);
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
    if(val1 == 0) return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::TRIGGER);
    return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::NORMAL);
  } else {
    if(val2 == 0) return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::TRIGGER);
    else if(val2 == 1) return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::NORMAL);
    else return InfraredSensorStatus(this->getDeviceId(),4,this->getName(),InfraredStatus::UNKNOW);
  }
}

bool InfraredSensor::isGPIOExport() {
  struct stat st;
  return stat((buildGPIOPath() + "/gpio" + buildGPIONum()).c_str(),&st) == 0;
}
void InfraredSensor::exitGPIO() {

}

bool InfraredSensor::exportGPIO() {
  std::ifstream gpioDir(buildGPIOPath() + "gpio" + buildGPIONum());
  if(!gpioDir.good()) {
    std::ofstream exportFile(buildGPIOPath() + "export");
    if(!exportFile.is_open()) {
      //日志
      return false;
    }
    exportFile << buildGPIONum();
    exportFile.close();
    usleep(200000);//延长初始化时间，匹配主板时序（200ms）
  }
  return true;
}
bool InfraredSensor::setGPIOInput() {
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

std::string InfraredSensor::buildGPIONum() {
  return std::to_string(this->getPin());
}
std::string InfraredSensor::buildGPIOPath() {
  return "/sys/class/gpio/";
}