#ifndef ACQUISITION_TASK_H
#define ACQUISITION_TASK_H

class AcquisitionTask {
    public:
        AcquisitionTask(int type, int sampleIntervalSec);
        virtual ~AcquisitionTask();

        virtual bool isAcquisitionData();

        int getType() const ;
        int getSampleIntervalSec() const ;

    protected:
        int _type;
        int _sampleIntervalSec;
};

#endif;