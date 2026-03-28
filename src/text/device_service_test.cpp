#include "business_layer/device/device_service.h"
#include "common/config/config_parser.h"
#include "business_layer/stream/stream_service.h"
#include <iostream>
const std::string CONFIGPATH = "../include/common/config/config.json";
int main(int argc, char* argv[]) {

    TempHumidSensorAcquisitionTask tempSensorTask = TempHumidSensorAcquisitionTask(1, 10);
    SerialDirectDeviceAcquisitionTask serialDeviceTask = SerialDirectDeviceAcquisitionTask(tempSensorTask); 

    SolenoidAcquisitionTask solenoidTask = SolenoidAcquisitionTask(0,10);           // 默认构造或自定义参数
    InfraredSensorAcquisitionTask infraredTask = InfraredSensorAcquisitionTask(4,10);
    WaterLevelSensorAcquisitionTask waterLevelTask = WaterLevelSensorAcquisitionTask(5,10);
    SmokeDetectorAcquisitionTask smokeTask = SmokeDetectorAcquisitionTask(6,10);


    PlcDeviceAcquisitionTask plcTask = PlcDeviceAcquisitionTask(solenoidTask);

    DoorLockAcquisitionTask doorLockTask = DoorLockAcquisitionTask(3,10);
    GPIODeviceAcquisitionTask gpioTask  = GPIODeviceAcquisitionTask(doorLockTask,infraredTask,waterLevelTask,smokeTask);

    //设备任务类
    DeviceAcquisitionTask deviceAcquisitionTask = DeviceAcquisitionTask(serialDeviceTask, plcTask,gpioTask);

    if(!ConfigParser::getInstance().loadFromFile(CONFIGPATH)) {
        std::cout << "配置文件加载失败" << std::endl;
    }

    // PlcInstanceSet plcInstances;
    // SerialDirectDeviceInstanceSet serialDeviceInstances;
    // GPIODeviceInstanceSet gpioDeviceInstances;
    // DeviceManageService devicemanageService(std::move(plcInstances),std::move(gpioDeviceInstances),std::move(serialDeviceInstances));

    // DeviceStatusCache deviceStatusCache;
    // RealTimeFrameCache realTimeFrameCache;

    // DeviceService deviceService(devicemanageService,deviceStatusCache,deviceAcquisitionTask,realTimeFrameCache);


    // InfraredSensorStatus infraredSensorStatus = deviceService.getInfraredSensorStatus(GPIODeviceSimpleInfo("infrared_01","红外传感器"));
    // SmokeDetectorStatus smokeStatus = deviceService.getSmokeDetectorStatus(GPIODeviceSimpleInfo("smoke_01","烟感传感器"));
    // WaterLevelSensorStatus waterLevelSensorStatus =  deviceService.getWaterLevelSensorStatus(GPIODeviceSimpleInfo("water_01","水浸传感器"));

    // std::cout <<"获取到的红外传感器状态:" << infraredSensorStatus.getStatus() << std::endl;
    // std::cout <<"获取到的烟感传感器状态" << smokeStatus.getStatus() << std::endl;
    // std::cout <<"获取到的水浸传感器状态" << waterLevelSensorStatus.getStatus() << std::endl;


    // int result = deviceService.lockDoorLock(GPIODeviceSimpleInfo("door_lock_1","门锁1"));
    // if(result == 0) {
    //     std::cout <<"打开成功" << std::endl;
    // } else if(result == -1) {
    //     std::cout <<"打开失败" << std::endl;
    // } else {
    //     std::cout << "门锁已经打开" << std::endl;
    // }

    StreamService streamService;
 
}