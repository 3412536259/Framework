#ifndef BOX_INSTANCE_H
#define BOX_INSTANCE_H

class BoxInstance {
    public:
        BoxInstance() = default;
        ~BoxInstance();

        BoxConfigResult configBoxDeviceParams(const BoxDeviceParams& params);

    private:
        //盒子相关配置
};

#endif
