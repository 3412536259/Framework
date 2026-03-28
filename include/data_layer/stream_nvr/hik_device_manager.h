#pragma once



class NVRConfig;

class NVRLoginManager{
public:
    ~NVRLoginManager();    

    virtual bool login(const NVRConfig& info) = 0;

    virtual int acquireUser() = 0;

    virtual bool logout() = 0;

    virtual void releaseUser(const NVRConfig& info) = 0 ;

}


class HikvisionLoginManager :public NVRLoginManager{
public:
    HikvisionLoginManager() = default;

    ~HikvisionLoginManager() = default;

    bool login(const NVRConfig& info) override;

    int acquireUser()override ;

    bool logout()override;

    void releaseUser(const NVRConfig& info) override;

private:
    int usedId;
};


