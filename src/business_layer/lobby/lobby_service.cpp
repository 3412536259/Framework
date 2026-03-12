#include "business_layer/lobby/lobby_service.h"
//public
 LobbyService::LobbyService(ISafetyService& safetyService, ICommandService& commandService, ITimer & timer )/* IDeviceService& deviceService, IDetectionService& detectionService */
    :  m_safetykService(safetyService), m_commandService(commandService),m_Timer(timer) /* ,m_deviceService(deviceService),  m_detectionService(detectionService) */
{
    
}


LobbyResult<SensorQuery> LobbyService::retrieveDeviceStatus(const DeviceStatusQuery& query){
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);   
    // 获取设备状态的逻辑 去设备状态缓冲里面去拿
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
    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}



LobbyResult<SensorQuery> LobbyService::operateSolenoidValve(const SolenoidValveOperation& operation)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<SensorQuery>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 打开电磁阀的逻辑 

    //1.正确
    return LobbyResult<SensorQuery>::Ok(SensorQuery());
    //2.错误
    // return LobbyResult<SensorQuery>::Error(ErrorCode::Code::SERVER_INTERNAL_ERROR);
    //3.异常错误
}
//private
void LobbyService::TimingProcessing(){
    


}


void LobbyService::TimingPullVideoFrame(){

}





