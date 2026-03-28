#ifndef SENSOR_TYPES_H
#define SENSOR_TYPES_H

enum class TempHumidStatus {
    NORMAL = 0,
    ABNORMAL = -1,
    OFFLINE = 1
};

enum class InfraredStatus {
    NORMAL = 1,
    TRIGGER = 0,
    UNKNOW = -1
};

enum class SmokeStatus {
    NORMAL = 1,
    ALARM = 0,
    UNKNOW = -1
};

enum class WaterLevelStatus {
    NORMAL = 0,
    ABNORMAL = -1,
    UNKNOW = -2,
};

#endif