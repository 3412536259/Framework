#include "data_layer/gpio_device/door_lock.h"

#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
DoorLock::DoorLock(int type,
                   const std::string& deviceId,
                   const std::string& name,
                   int pin,
                   const std::string& direction)
            : GPIOOutputDevice(type,deviceId,name,pin,direction){
    if(isGPIOExport()) {
        return ;
    }
    if(!exportGPIO()) {
        std::cout << "导出门锁的gpio失败!" << std::endl;
        return ;
    }
    if(!setGPIODirection()) {
        std::cout << "设置门锁的方向失败!" << std::endl;
        return ;
    }
}

bool DoorLock::lockDoorLock() {
    std::ofstream valueFile(buildGPIOBasePath() + "gpio" + buildGPIOPin() + "/value");
    if (!valueFile.is_open()) {
        //无法打开value文件（权限不足）
        std::cout << "打开value文件失败!" <<std::endl;
        return false;
    }
    valueFile << 0;
    valueFile.close();
    return true;
}
//（0=低电平/设备关，1=高电平/设备开）
bool DoorLock::unlockDoorLock() {
    std::ofstream valueFile(buildGPIOBasePath() + "gpio" + buildGPIOPin() + "/value");
    if (!valueFile.is_open()) {
        std::cout << "门锁value文件打开失败" << std::endl;
        //无法打开value文件（权限不足）
        return false;
    }
    valueFile << 1;
    valueFile.close();
    return true;
}

std::unique_ptr<DeviceStatus> DoorLock::getStatus() const {
    return std::make_unique<DeviceStatus> ();
}

DoorLockStatus DoorLock::queryDoorLockStatus() {
    std::ifstream valueFile(getGPIOSysPath());
    if (!valueFile.is_open()) {
        //无法读取value文件"
        return DoorLockStatus(this->getDeviceId(),4,this->getName(),LockStatus::UNKNOW);
    }
    std::string valueStr;
    valueFile >> valueStr;
    valueFile.close();
    if (valueStr == "1") return  DoorLockStatus(this->getDeviceId(),4,this->getName(),LockStatus::UNLOCK);
    return DoorLockStatus(this->getDeviceId(),4,this->getName(),LockStatus::LOCK);
}

bool DoorLock::isGPIOExport() {
    struct stat st;
    return stat(getGPIOSysPath().c_str(),&st) == 0;
}
bool DoorLock::exportGPIO() {
    std::ifstream gpioDir(getGPIOSysPath());
    if(!gpioDir.good()) {
        std::ofstream exportFile(buildGPIOBasePath() + "export");
        if(!exportFile.is_open()) {
            std::cout << "门锁: 打开导出文件失败" << std::endl;
            return false;
        }
        exportFile << buildGPIOPin();
        exportFile.close();
        usleep(200000);
    }
    gpioDir.close();
    return true;
}
bool DoorLock::setGPIODirection() {

    std::string dirPath = getGPIOSysPath() + "/direction";
    std::ofstream dirFile(dirPath);
    if (!dirFile.is_open()) {
        //无法打开direction文件
        return false;
    }
    dirFile << this->getDirection();
    dirFile.close();
    return true;
}

std::string DoorLock::getGPIOSysPath() {
    return "/sys/class/gpio/gpio" + std::to_string(this->getPin());
}

std::string DoorLock::buildGPIOBasePath() {
    return "/sys/class/gpio/";
}
std::string DoorLock::buildGPIOPin() {
    return std::to_string(this->getPin());
}