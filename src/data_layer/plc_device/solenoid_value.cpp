#include <unistd.h>
#include "solenoid_value.h"

SolenoidValue::SolenoidValue(const int type,
                             const std::string& deviceId,
                             const std::string& name,
                             const std::string& bindSerialPort,
                             const std::string& slaveAddr,
                             const std::string& plcId,
                             const std::string& plcPort,
                             const std::string& regAddr) 
    : PlcDevice(type,deviceId,name,bindSerialPort,slaveAddr), 
      plcId_(plcId),plcPort_(plcPort),regAddr_(regAddr) {

}

std::unique_ptr<DeviceStatus> SolenoidValue::getStatus() const {

}

std::string SolenoidValue::getPlcId() const {
  return plcId_;
}

// SolenoidRealTimeData SolenoidValue::getRealTimeData() {

// }   

bool SolenoidValue::open(int serialPortStatus) {
  // 电磁阀（Y1）开启指令（地址0x0501，校验码重新计算）
    
    // unsigned char sendBuf[] = {0x01, 0x05, 0x05, 0x01, 0xFF, 0x00, 0xDD, 0x36};
    auto frame = buildOpenCommand();
    ssize_t sent = write(serialPortStatus, frame.data(), frame.size());

    if (sent != frame.size()) {
        //"电磁阀开启指令发送失败";
        return false;
    }

    unsigned char recvBuf[256];
    ssize_t len = read(serialPortStatus, recvBuf, sizeof(recvBuf));
    
    if(len <= 0) return false;

    //"电磁阀状态：已开启" << endl;
    return true;
}

bool SolenoidValue::close(int serialPortStatus) {
    // 电磁阀（Y1）关闭指令（地址0x0501，校验码重新计算）
  // unsigned char sendBuf[] = {0x01, 0x05, 0x05, 0x01, 0x00, 0x00, 0x9C, 0xC6};
  auto frame = buildCloseCommand();
  ssize_t sent = write(serialPortStatus, frame.data(), frame.size());

  if (sent != frame.size()) {
      perror("电磁阀关闭指令发送失败");
      return false;
  }

  unsigned char recvBuf[256];
  ssize_t len = read(serialPortStatus, recvBuf, sizeof(recvBuf));

  if(len <= 0) return false;
  //cout << "电磁阀状态：已关闭" << endl;
  return true;
}

SolenoidStatus SolenoidValue::queryStatus(int serialPortStatus) {
  // unsigned char sendBuf[] = {0x01, 0x01, 0x05, 0x01, 0x00, 0x01, 0xAC, 0xC6};
  auto frame = buildQueryStatusCommand();
  ssize_t sent = write(serialPortStatus, frame.data(), frame.size());

  if (sent != frame.size()) {
    //perror("电磁阀状态查询指令发送失败");
    return SolenoidStatus();
  }

  // cout << "电磁阀状态查询指令已发送：";

  unsigned char recvBuf[256];
  ssize_t len = read(serialPortStatus, recvBuf, sizeof(recvBuf));
  if(len <= 0) return SolenoidStatus(getDeviceId(),0,getName(),"UNKNOW","UNKNOW");
     
  // 解析响应：第3字节为数据长度，第4字节bit0表示状态（1=开启，0=关闭）
  if (len >= 4) {
    if (recvBuf[3] & 0x01) {
      return SolenoidStatus(getDeviceId(),0,getName(),"ONLINE","OPEN");
    } else {
        return SolenoidStatus(getDeviceId(),0,getName(),"ONLINE","CLOSED");
      }
  } else  return SolenoidStatus(getDeviceId(),0,getName(),"UNKNOW","UNKNOW"); 
}

std::array<uint8_t,8> SolenoidValue::buildOpenCommand() {
  std::array<uint8_t,8> frame;
  //plc从机地址
  frame[0] = std::stoi(getSlaveAddr(),nullptr,16);
  //功能码
  frame[1] = 0x05;

  //线圈地址
  uint8_t high,low;
  buildCoilAddress(high,low);
  frame[2] = high;
  frame[3] = low;

  //写入值
  frame[4] = 0xFF;
  frame[5] = 0x00;

  //CRC
  uint16_t crc = buildCalcCRC(frame.data(),6);

  frame[6] = crc & 0xFF;
  frame[7] = (crc >> 8) & 0xFF;

  return frame;
}

std::array<uint8_t,8> SolenoidValue::buildCloseCommand() {
  std::array<uint8_t,8> frame;

  frame[0] = std::stoi(getSlaveAddr(),nullptr,16);
  //功能码
  frame[1] = 0x05;

  //线圈地址
  uint8_t high,low;
  buildCoilAddress(high,low);
  frame[2] = high;
  frame[3] = low;

  //写入值
  frame[4] = 0x00;
  frame[5] = 0x00;

  //CRC
  uint16_t crc = buildCalcCRC(frame.data(),6);
  frame[6] = crc & 0xFF;
  frame[7] = (crc >> 8) & 0xFF;

  return frame;
}

std::array<uint8_t,8> SolenoidValue::buildQueryStatusCommand() {
  std::array<uint8_t,8> frame;

  frame[0] = std::stoi(this -> getSlaveAddr(),nullptr,16);
  frame[1] = 0x01;

  uint8_t high,low;
  buildCoilAddress(high,low);
  frame[2] = high;
  frame[3] = low;
  frame[4] = 0x00;
  frame[5] = 0x01;
  uint16_t crc = buildCalcCRC(frame.data(),6);
  frame[6] = crc & 0xFF;
  frame[7] = (crc >> 8) & 0xFF;
  return frame;
}


void SolenoidValue::buildCoilAddress(uint8_t& high,uint8_t& low) {
  // int port = std::stoi(regAddr_, nullptr, 16);
  // uint16_t address = 0x0500 + port;
  // high = (address >> 8) & 0xFF;
  // low = address & 0xFF;
  int value = std::stoi( regAddr_ ,nullptr,16);
  uint16_t regAddr = static_cast<uint16_t>(value);
  high = ( regAddr >> 8) & 0xFF;
  low = regAddr & 0xFF;
}

uint16_t SolenoidValue::buildCalcCRC(const uint8_t* data, size_t length) {
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