#include "business_layer/lobby/lobby_service.h"

LobbyResult LobbyService::retrieveDeviceStatus(const DeviceStatusQuery& query){

}


LobbyResult LobbyService::retrieveLiveCameraFrame(const FrameQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto frame = m_deviceService.getLiveFrame(query.cameraId);

    // return LobbyResult::FromDeviceResult(frame);
}

LobbyResult LobbyService::retrieveHistoricalCameraFootage(const HistoricalVideoQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_deviceService.getHistoricalVideo(query.cameraId, query.timeRange);

    // return LobbyResult::FromDeviceResult(result);
}

LobbyResult LobbyService::retrieveAlarmRecords(const AlarmQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto alarms = m_detectionService.getAlarmRecords(query);

    // return LobbyResult::FromDetectionResult(alarms);
}


LobbyResult LobbyService::downloadHistoricalCameraFootage(const DownloadHistoricalVideo& download)
{
    // auto auth = m_safetyService.verify(download.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_commandService.execute(download);

    // return LobbyResult::FromCommandResult(result);
}



LobbyResult LobbyService::operateSolenoidValve(const SolenoidValveOperation& operation)
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





