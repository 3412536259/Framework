#include <termios.h>
#include <fcntl.h> 
#include <unistd.h>
#include "data_layer/plc/plc_instance.h"

PlcInstance::PlcInstance(const PlcDevice& plcDevice,
                         const SerialConfig& serialConfig,
                         std::vector<SolenoidValue>& solenoidValues)
                         : plcDevice_(plcDevice),
                           serialConfig_(serialConfig)
{
  solenoidMap_.reserve(solenoidValues.size());
         
  for (auto& solenoid : solenoidValues) {
    solenoidMap_.emplace(solenoid.getDeviceId(), std::move(solenoid));
  }

}

bool PlcInstance::openSolenoidValue(const PlcDeviceInfo& info) {
  auto it = solenoidMap_.find(info.getDeviceId());

  if(it == solenoidMap_.end()) {
    return false;
  }
  SolenoidValue& solenoid = it -> second;
  return solenoid.open(serialPortStatus_);  
}

bool PlcInstance::closeSolenoidValue(const PlcDeviceInfo& info) {
  auto it = solenoidMap_.find(info.getDeviceId());

  if(it == solenoidMap_.end()) {
    return false;    
  }
  SolenoidValue& solenoid = it -> second;
  return solenoid.close(serialPortStatus_);

}

std::vector<SolenoidStatus> PlcInstance::getSolenoidStatusList(){
  std::vector<SolenoidStatus> statusList;
  statusList.reserve(solenoidMap_.size());
  for(auto& [key,solenoid] : solenoidMap_) {
    statusList.push_back(solenoid.queryStatus(serialPortStatus_));
  }
  return statusList;
}

SolenoidStatus PlcInstance::getSolenoidValueStatus(const PlcDeviceInfo& info) {
  auto it = solenoidMap_.find(info.getDeviceId());

  if(it == solenoidMap_.end()) {
    return SolenoidStatus();
  }
  SolenoidValue& solenoid = it -> second;
  return solenoid.queryStatus(serialPortStatus_);
}

int PlcInstance::getSolenoidSensorNum(){
  return solenoidMap_.size();
}

bool PlcInstance::connect() {
  if(serialPortStatus_ >= 0) {
    //串口已经打开
    return true;
  }
  //初始化串口
  serialPortStatus_ = open( plcDevice_.getBindSerialPort().c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if(serialPortStatus_ < 0){
    //打开失败
    return false;
  }
  if(!configureSerial()){
    close(serialPortStatus_);
    serialPortStatus_ = -1;
    return false;
  }
  //串口初始化成功(串口：this.getBindSerialPort());
  return true;
}

void PlcInstance::disconnect() {
  if(serialPortStatus_ >= 0) {
    close(serialPortStatus_);
    serialPortStatus_ = -1;
    //串口已关闭
  }
}

bool PlcInstance::configureSerial() {
  struct termios tty;
  if(tcgetattr(serialPortStatus_,&tty) != 0) {
    //串口配置失败
    return false;
  }

  speed_t speed = serialConfig_.getBaudRate();
  cfsetospeed(&tty, speed);  // 设置输出波特率为9600
  cfsetispeed(&tty, speed);
  // 校验位：无校验（PARENB 是奇偶校验使能位，~表示清除该位）
  serialConfig_.setPlcParity(tty);
  // 停止位：1位停止位（CSTOPB 是2位停止位使能位，清除则为1位）
  serialConfig_.setPlcStopBits(tty);
  // 数据位：8位数据位（先清除CSIZE掩码，再置位CS8）
  serialConfig_.setPlcDataBits(tty);
  // 关闭硬件流控（CRTSCTS 是硬件流控使能位，清除则禁用）
  tty.c_cflag &= ~CRTSCTS;
  // 启用串口接收（CREAD）+ 忽略调制解调器状态线（CLOCAL）
  tty.c_cflag |= CREAD | CLOCAL;

  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
  tty.c_oflag = 0;
  tty.c_lflag = 0;

  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 10;

  if (tcsetattr(serialPortStatus_, TCSANOW, &tty) != 0) {
      //"串口参数设置失败(tcsetattr)"
      return false;
  }
  return true;
}

