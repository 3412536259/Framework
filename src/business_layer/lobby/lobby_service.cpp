#include "business_layer/lobby/lobby_service.h"
//public
 LobbyService::LobbyService(ITimer & timer /* IDeviceService& deviceService, ISafetyService& safetyService, ICommandService& commandService, IDetectionService& detectionService */)
    : m_Timer(timer)/* , m_deviceService(deviceService), m_safetykService(safetyService), m_commandService(commandService), m_detectionService(detectionService) */
{
    
}


LobbyResult<SensorQuery> LobbyService::retrieveDeviceStatus(const DeviceStatusQuery& query){
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);   
    // 获取设备状态的逻辑 
    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误

}


LobbyResult<SensorQuery> LobbyService::retrieveLiveCameraFrame(const FrameQuery& query)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 获取视频帧的逻辑 
    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}

LobbyResult<SensorQuery> LobbyService::retrieveHistoricalCameraFootage(const HistoricalVideoQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_deviceService.getHistoricalVideo(query.cameraId, query.timeRange);

    // return LobbyResult::FromDeviceResult(result);
}

LobbyResult<SensorQuery> LobbyService::retrieveAlarmRecords(const AlarmQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto alarms = m_detectionService.getAlarmRecords(query);

    // return LobbyResult::FromDetectionResult(alarms);
}


LobbyResult<SensorQuery> LobbyService::downloadHistoricalCameraFootage(const DownloadHistoricalVideo& download)
{
    // auto auth = m_safetyService.verify(download.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_commandService.execute(download);

    // return LobbyResult::FromCommandResult(result);
}



LobbyResult<SensorQuery> LobbyService::operateSolenoidValve(const SolenoidValveOperation& operation)
{
    // // 1. 安全验证
    // auto auth = m_safetyService.verify(operation.token);
    // if (!auth.success())
    //     return LobbyResult.NoPermission();

    // // 2. 查询设备状态
    // auto status = m_deviceService.getDeviceStatus(operation.deviceId);
    // if (!status.canOperate())
    //     return LobbyResult.InvalidState();

    // // 3. 下发命令
    // auto cmdResult = m_commandService.execute(operation);

    // // 4. 更新设备状态
    // if (cmdResult.success())
    //     m_deviceService.updateDeviceStatus(operation.deviceId, cmdResult.newState());

    // // 5. 返回统一结果
    // return LobbyResult.FromCommandResult(cmdResult);
}
//private
void LobbyService::TimingProcessing(){
    


}


void LobbyService::TimingPullVideoFrame(){

}





