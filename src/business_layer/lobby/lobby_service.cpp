#include "business_layer/lobby/lobby_service.h"
#include "business_layer/lobby/lobby_object.h"

//public
 LobbyService::LobbyService(ISafetyService& safetyService, ICommandService& commandService/*,IDeviceService deviceService*/,ITimer & timer )/* IDeviceService& deviceService, IDetectionService& detectionService */
    :  m_safetykService(safetyService), m_commandService(commandService)/*,m_deviceService(deviceService)*/,m_Timer(timer) /* ,m_deviceService(deviceService),  m_detectionService(detectionService) */
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



LobbyResult<DeviceOperationResult> LobbyService::operateSolenoidValve(const SolenoidValveOperation& operation)
{
    auto auth = m_safetykService.authenticate();
    if (!auth)return LobbyResult<DeviceOperationResult>::Error(ErrorCode::Code::AUTH_PERMISSION_DENIED);
    // 打开电磁阀的逻辑 
    //1.去device服务里面去验证这个设备的状态是否可用



    // try {
        // 3️⃣ 构建命令（✅ 正确方式）
        Command cmd = Command::createOperateSolenoid(operation);

        // 4️⃣ 下发命令
        m_commandService.executeCommand(cmd);

        if(operation.getCmd() == "open"){
            //这里 去调用设备服务去打开电磁阀
            // DeviceOperationResult result = 
            // return LobbyResult<SensorQuery>::Ok();
        } else if(operation.getCmd() == "close"){
            // DeviceOperationResult result = 
            // return LobbyResult<SensorQuery>::Ok();
        }

        // 5️⃣ 返回结果
        // SolenoidValveOperationResult result;
        // result.cmdId = cmd.getCmdId();

        // return LobbyResult<SensorQuery>::Ok();
    // }
    // catch (const std::exception& e) {
        return LobbyResult<DeviceOperationResult>::Error(
            ErrorCode::Code::SERVER_INTERNAL_ERROR
        );
    // }
    //   LobbyResult<DeviceOperationResult>
    // operateSolenoidValve(const SolenoidValveOperation& op) override
    // {
    //     // (1) 鉴权
    //     auto auth = m_safety.authenticate();
    //     if (!auth) {
    //         return LobbyResult<DeviceOperationResult>::Error(
    //             ErrorCode::AUTH_PERMISSION_DENIED);
    //     }

    //     // (2) 查询设备状态
    //     auto deviceStatus = m_deviceClient.getDeviceStatus(op.getDeviceId());
    //     if (!deviceStatus) {
    //         return LobbyResult<DeviceOperationResult>::Error(
    //             ErrorCode::DEVICE_NOT_FOUND);
    //     }

    //     if (!deviceStatus.value().isAvailable()) {
    //         return LobbyResult<DeviceOperationResult>::Error(
    //             ErrorCode::DEVICE_BUSY);
    //     }

    //     // (3) 执行命令
    //     auto result = m_commandClient.operateSolenoidValve(op);
    //     if (!result) {
    //         return result; // 直接返回错误
    //     }

    //     // (4) 更新设备状态
    //     DeviceStatus newStatus = deviceStatus.value();
    //     newStatus.updateFromOperation(result.value());

    //     m_deviceClient.updateDeviceStatus(op.getDeviceId(), newStatus);

    //     // (5) 返回结果
    //     return result;
    // }

    
}
//private
void LobbyService::TimingProcessing(){
    


}


void LobbyService::TimingPullVideoFrame(){

}





