#ifndef SOLENOID_INSTANCE_SET_H
#define SOLENOID_INSTANCE_SET_H

#include "solenoid_value.h"
#include "solenoid_status.h"
#include"solenoid_real_time_data.h"
#include <unordered_map>
#include <memory>

class SolenoidInstanceSet {
    public:
        SolenoidInstanceSet() = default;
        ~SolenoidInstanceSet();

        const std::vector<SolenoidStatus>& getSolenoidStatusList() const;
        const std::vector<SolenoidRealTimeData>& getSolenoidRealTimeDataList() const;

        int openSolenoidValue(const SolenoidValueInfo& info);
        int closeSolenoidValue(const SolenoidValueInfo& info);
 
    private:
        std::unordered_map<std::string, std::unique_ptr<SolenoidValue> > solenoidValues_;
};

#endif;