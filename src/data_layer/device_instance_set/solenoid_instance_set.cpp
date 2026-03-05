#include "solenoid_instance_set.h"
#include "solenoid_value.h"
SolenoidInstanceSet::SolenoidInsatnceSet() {

}

SolenoidInsatnceSet::~SolenoidInsatnceSet() {

}

const std::vector<SolenoidValue>& SolenoidInsatnceSet::getSolenoidValues() const {
    return _solenoidValues;
}