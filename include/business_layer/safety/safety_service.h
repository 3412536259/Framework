#pragma once
#include <string>
class ISafetyService {
public:
    
    virtual ~ISafetyService() = default;

    virtual bool authenticate() = 0;

    virtual bool authorize() = 0;



};  


class SafetyService : public ISafetyService {


public:
    bool authenticate() override;
    
    
    bool authorize() override;


private:
    //AuthService 
    //PermissionService
};
