#include "business_layer/lobby/lobby_service.h"

LobbyResult LobbyService::retrieveDeviceStatus(const DeviceStatusQuery& query)
{
    // // 1. 安全验证
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // // 2. 查询设备状态
    // auto result = m_deviceService.getDeviceStatus(query.deviceId);

    // // 3. 返回统一结果
    // return LobbyResult::FromDeviceResult(result);
}



LobbyResult LobbyService::retrieveSensorStatus(const SensorQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_deviceService.getSensorStatus(query.sensorId);

    // return LobbyResult::FromDeviceResult(result);
}


LobbyResult LobbyService::retrieveEnvironmentData(const EnvironmentQuery& query)
{
    // auto auth = m_safetyService.verify(query.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_deviceService.getEnvironmentData(query.deviceId);

    // return LobbyResult::FromDeviceResult(result);
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

LobbyResult LobbyService::operateDoorLock(const DoorLockOperation& operation)
{
    // auto auth = m_safetyService.verify(operation.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto status = m_deviceService.getDeviceStatus(operation.deviceId);
    // if (!status.canOperate())
    //     return LobbyResult::InvalidState();

    // auto cmdResult = m_commandService.execute(operation);

    // if (cmdResult.success())
    //     m_deviceService.updateDeviceStatus(operation.deviceId, cmdResult.newState());

    // return LobbyResult::FromCommandResult(cmdResult);
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

LobbyResult LobbyService::controlTrolleyRotation(const TrolleyOperation& operation)
{
    // auto auth = m_safetyService.verify(operation.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto status = m_deviceService.getDeviceStatus(operation.deviceId);
    // if (!status.canRotate())
    //     return LobbyResult::InvalidState();

    // auto cmdResult = m_commandService.execute(operation);

    // if (cmdResult.success())
    //     m_deviceService.updateDeviceStatus(operation.deviceId, cmdResult.newState());

    // return LobbyResult::FromCommandResult(cmdResult);
}

LobbyResult LobbyService::controlRotateCamera(const CameraOperation& operation)
{
    // auto auth = m_safetyService.verify(operation.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto cmdResult = m_commandService.execute(operation);

    // return LobbyResult::FromCommandResult(cmdResult);
}



LobbyResult LobbyService::deployAIModel(const AIModelDeploy& deploy)
{
    // auto auth = m_safetyService.verify(deploy.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_detectionService.deployModel(deploy);

    // return LobbyResult::FromDetectionResult(result);
}

LobbyResult LobbyService::enableAIModel(const AIModelEnable& enable)
{
    // auto auth = m_safetyService.verify(enable.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_detectionService.enableModel(enable);

    // return LobbyResult::FromDetectionResult(result);
}


LobbyResult LobbyService::disableAIModel(const AIModelDisable& disable)
{
    // auto auth = m_safetyService.verify(disable.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_detectionService.disableModel(disable);

    // return LobbyResult::FromDetectionResult(result);
}

LobbyResult LobbyService::updateAIModel(const AIModelUpdate& update)
{
    // auto auth = m_safetyService.verify(update.token);
    // if (!auth.success())
    //     return LobbyResult::NoPermission();

    // auto result = m_detectionService.updateModel(update);

    // return LobbyResult::FromDetectionResult(result);
}