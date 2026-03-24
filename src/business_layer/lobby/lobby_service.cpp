#include "business_layer/lobby/lobby_service.h"
#include "business_layer/lobby/lobby_object.h"
#include "common/log/log_manager.h"
//public
 LobbyService::LobbyService(ISafetyService& safetyService, ICommandService& commandService,IDeviceService& deviceService,ITimer & timer,DeviceStatusCache& deviceStatusCache )
    :  m_safetykService(safetyService), m_commandService(commandService),m_deviceService(deviceService),m_Timer(timer),deviceStatusCache_(deviceStatusCache)
{
    
}


LobbyResult<BoxDeviceStatus> LobbyService::retrieveDeviceStatus(const DeviceStatusQuery& query){
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<BoxDeviceStatus>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);   
    if(query.getReqSource() == "http"){
        //去拿设备状态
    } else{
        
    }
    return LobbyResult<BoxDeviceStatus>::Ok(BoxDeviceStatus());
    
    
}


LobbyResult<SensorQuery> LobbyService::retrieveLiveCameraFrame(const FrameQuery& query)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 获取视频帧的逻辑 去帧缓冲里面去拿
    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}

LobbyResult<SensorQuery> LobbyService::retrieveHistoricalCameraFootage(const HistoricalVideoQuery& query)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 获取历史视频时间段的逻辑 
    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}

LobbyResult<SensorQuery> LobbyService::retrieveAlarmRecords(const AlarmQuery& query)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 查看报警记录
    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}


LobbyResult<SensorQuery> LobbyService::downloadHistoricalCameraFootage(const DownloadHistoricalVideo& download)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 上传视频的逻辑 
    //1.去device服务里面去验证这个视频的状态是否可用
    //2.命令服务创建命令
    //3.命令调用命令服务，加入到命令服务的接口
    //4.打开电磁阀
    //5.根据返回值进行更改命令的状态

    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}



LobbyResult<SolenoidValveOperationResult> LobbyService::operateSolenoidValve(const SolenoidValveOperation& operation)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SolenoidValveOperationResult>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);

    //这里需要检查设备状态的

    try {

        PlcDeviceInfo plcDevice = PlcDeviceInfo::createPlcDevice(operation);

        DeviceOperationResult result;

        if(operation.getCmd() == "open"){
            result = m_deviceService.openSolenoidValue(plcDevice);
        }
        else if(operation.getCmd() == "close"){
            result = m_deviceService.closeSolenoidValue(plcDevice); 
        } 
        else {
            return LobbyResult<SolenoidValveOperationResult>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
        }

        Command cmd = Command::createOperateSolenoidResult(result,operation);

        m_commandService.executeCommand(cmd);
        
        sendSolenoidResult(cmd,operation,result);
        
        
        SolenoidValveOperationResult opResult = SolenoidValveOperationResult::createResult(result,operation);

        return LobbyResult<SolenoidValveOperationResult>::Ok(opResult);
    } catch (const std::exception& e) {
            LOG_WARNING("操作电磁阀出错 " + std::string("Exception: ") + e.what());
            return LobbyResult<SolenoidValveOperationResult>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);

        }
}

LobbyResult<void> LobbyService::startDeviceStatusUpload(const DeviceStatusQuery& query){
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<void>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    if(!TimingUpload()){
        return LobbyResult<void>::Error(ErrorCode::Code::SERVER_TOO_MANY_Repeat);
    }
    return LobbyResult<void>::Ok();
}

//private
void LobbyService::TimingProcessing(){
    


}

bool LobbyService::TimingUpload(){

    if(m_Timer.isRunningUpload()) return false;
    m_Timer.scheduleRepeated(5000,[this]() {
        // 👇 业务逻辑在这里（不是 Timer 内部）
        auto status = m_deviceService.viewAllDeviceStatus();
        // upload(status); //上传逻辑
        sendBoxStatusResult(status);
        
    });
}



void LobbyService::TimingPullVideoFrame(){

}
void LobbyService::sendBoxStatusResult(const BoxDeviceStatus& boxStatus) {
    json msg;

    // 从传入的 boxStatus 中获取所有设备状态
    // msg["solenoid"] = boxStatus.getSolenoidStatusList();
    // msg["sensor"] = boxStatus.getSensorStatusList();
    // msg["camera"] = boxStatus.getCameraStatusList();
    // msg["infrared"] = boxStatus.getInfraredSensorStatusList();
    // msg["smokeDetector"] = boxStatus.getSmokeDetectorStatusList();
    // msg["waterLevel"] = boxStatus.getWaterLevelSensorStatusList();
    // msg["doorLock"] = boxStatus.getDoorLockStatusList();

    // MQTT 发送
    std::string topic = "device/uploadStatus/result";
    m_commandService.sendCommandResultToMqtt(topic, msg.dump());
}


void LobbyService::sendSolenoidResult(const Command& cmd, const SolenoidValveOperation& op,const DeviceOperationResult& result){
    if(op.getReqSource() == "http") return;
    json msg;
    msg["cmdId"] = cmd.getCmdId();
    msg["deviceId"] = cmd.getDeviceId();
    msg["plcId"] = op.getPlcId();
    msg["success"] = result.operationBool()? "0" : "-1";

    std::string topic = "device/solenoid/result";

    m_commandService.sendCommandResultToMqtt(topic, msg.dump());
}
