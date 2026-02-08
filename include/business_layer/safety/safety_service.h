#pragma once

class ISafetyService {
public:
    virtual void run() = 0;
    virtual ~ISafetyService() = default;
};


class SafetyService : public ISafetyService {
public:
    
};
