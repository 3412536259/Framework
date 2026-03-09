#ifndef ACQUISITION_TASK_H
#define ACQUISITION_TASK_H

#include <chrono>
class AcquisitionTask {
    public:
        AcquisitionTask(int type, int sampleIntervalSec);
        virtual ~AcquisitionTask();

        virtual bool isAcquisitionData();

        int getType() const ;
        int getSampleIntervalSec() const ;
        int getNextAcquisitionTime() const ;

    protected:
        int _type;
        int _sampleIntervalSec;
        std::chrono::steady_clock::time_point _nextAcquisitionTime; //下次采集时间
};

#endif;