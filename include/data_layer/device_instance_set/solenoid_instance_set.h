#ifndef SOLENOID_INSTANCE_SET_H
#define SOLENOID_INSTANCE_SET_H

#include "solenoid_value.h"
#include <unordered_map>
#include <memory>

class SolenoidInsatnceSet {
    public:
        SolenoidInsatnceSet() = default;
        ~SolenoidInsatnceSet();

        const std::vector<SolenoidValue>& getSolenoidValues() const;
        const std::vector<SolenoidRealTimeData>& getSolenoidRealTimeData() const;

        int openSolenoidValue(const SolenoidValueInfo& info);
 
    private:
        std::unordered_map<int, std::unique_ptr<SolenoidValue> > _solenoidValues;
};

#endif;