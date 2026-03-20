#include "data_layer/plc_device/plc_water_level_sensor.h"

#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <thread>
PlcWaterLevelSensor::PlcWaterLevelSensor(const int& type,
                         const std::string& deviceId,
                         const std::string& name,
                         const std::string& bindSerialPort,
                         const std::string& slaveAddr,
                         const std::string& plcPort,
                         const std::string& regAddr)
                : PlcDevice(type,deviceId,name,bindSerialPort,slaveAddr),
                  plcPort_(plcPort),
                  regAddr_(regAddr) {

}  

std::unique_ptr<DeviceStatus> PlcWaterLevelSensor::getStatus() const {
    return std::make_unique<PlcWaterLevelSensorStatus>();
}

PlcWaterLevelSensorStatus PlcWaterLevelSensor::queryStatus(int serialPortStatus) {
    auto command = buildQueryCommand();
    if(!sendData(command,serialPortStatus)) {
        //发送指令失败
        return PlcWaterLevelSensorStatus(this->getDeviceId(),1,this->getName(),WaterLevelSensorStatus::UNKNOW);
    }

    unsigned char recvBuf[256];
    int len = receviceData(recvBuf,sizeof(recvBuf),100,serialPortStatus);

    if(len >= 4 && recvBuf[1] == 0x01) {
        int state = recvBuf[3];
        if(state == 0) return PlcWaterLevelSensorStatus(this->getDeviceId(),1,this->getName(),WaterLevelSensorStatus::NORMAL);
        else if (state ==1 ) return PlcWaterLevelSensorStatus(this->getDeviceId(),1,this->getName(),WaterLevelSensorStatus::ABNORMAL);
        else return PlcWaterLevelSensorStatus(this->getDeviceId(),1,this->getName(),WaterLevelSensorStatus::UNKNOW);
    } return PlcWaterLevelSensorStatus(this->getDeviceId(),1,this->getName(),WaterLevelSensorStatus::UNKNOW);
}

std::array<uint8_t,8> PlcWaterLevelSensor::buildQueryCommand() {
  std::array<uint8_t,8> frame;
  frame[0] = std::stoi(this->getSlaveAddr(),nullptr,16);
  //功能码
  frame[1] = 0x01;
  uint8_t high,low;
  splitRegAddress(high,low);
  frame[2] = high;
  frame[3] = low;
  frame[4] = 0x00;
  frame[5] = 0x01;
  uint16_t crc = buildCalcCRC(frame.data(),6);
  frame[6] = crc & 0xFF;
  frame[7] = ( crc >> 8) & 0xFF;
  return frame;
}

void PlcWaterLevelSensor::splitRegAddress(uint8_t& high,uint8_t& low) {
  int value = std::stoi(regAddr_,nullptr,16);
  uint16_t regAddr = static_cast<uint16_t>(value);
  high = ( regAddr >> 8) & 0xFF;
  low = regAddr & 0xFF;
}

uint16_t PlcWaterLevelSensor::buildCalcCRC(const uint8_t* data,size_t length) {
  uint16_t crc = 0xFFFF;

  for(size_t i = 0; i < length; ++i){
    crc ^= data[i];

    for(int j = 0; j < 8; ++j) {
      if(crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else crc >>= 1;
    }
  }
  return crc;
}

bool PlcWaterLevelSensor::sendData(std::array<uint8_t,8> command,int serialPortStatus) {
    ssize_t sent = write(serialPortStatus,command.data(),command.size());
    if(sent != command.size()) {
        //发送指令失败
        return false;
    }
    tcdrain(serialPortStatus);
    return true;
}
int PlcWaterLevelSensor::receviceData(unsigned char* recvBuf,int bufSize,int waitTime,int serialPortStatus) {

    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    memset(recvBuf,0,bufSize);

    int len = read(serialPortStatus,recvBuf,bufSize);
    return len;
}