#pragma once
#include <string>

class DownloadVideoFile {
public:
    DownloadVideoFile() = default;

    DownloadVideoFile(const std::string& cameraId,const std::string& nvrId,const std::string& fileName,const std::string& startTime,const std::string& fileSize = "");


    // ===== Getter =====
    const std::string& cameraId()  const;
    const std::string& nvrId()     const;
    const std::string& fileName()  const;
    const std::string& startTime() const;
    const std::string& fileSize()  const;

    void setStartTime(const std::string& startTime) {
        startTime_ = startTime;
        // 替换空格为下划线
        size_t spacePos = startTime_.find(' ');
        if (spacePos != std::string::npos) {
            startTime_[spacePos] = '_';
        }
    }

private:
   
    std::string cameraId_;
    std::string nvrId_;
    std::string fileName_;   
    std::string fileSize_; 
    std::string startTime_;  // yyyy-MM-dd HH:mm:ss 或时间戳字符串
};


class DownloadReadyFile {
public:
    // 无参构造函数
    DownloadReadyFile()  : downloadResult(0)  {}// 默认下载状态为"进行中"
    // 带参构造函数（方便一次性初始化所有成员）
    DownloadReadyFile(const std::string& cameraId, 
                      const std::string& nvrId, 
                      const std::string& fileName, 
                      const std::string& fileSize, 
                      int downloadResult, 
                      const std::string& localPath, 
                      const std::string& processError)
        : cameraId(cameraId),
          nvrId(nvrId),
          fileName(fileName),
          fileSize(fileSize),
          downloadResult(downloadResult),
          localPath(localPath),
          processError(processError)
    {}
  
    std::string getCameraId() const ;
    
    void setCameraId(const std::string& cameraId) ;
    

    std::string getNvrId() const ;

    void setNvrId(const std::string& nvrId) ;


    std::string getFileName() const ;
    

    void setFileName(const std::string& fileName) ;

    std::string getFileSize() const ;

    void setFileSize(const std::string& fileSize) ;

 
    int getDownloadResult() const ;

    void setDownloadResult(int downloadResult) {
        // 可选：增加参数合法性校验，确保值只能是 1/0/-1
        if (downloadResult == 1 || downloadResult == 0 || downloadResult == -1) {
            this->downloadResult = downloadResult;
        }
    }

    std::string getLocalPath() const ;

    void setLocalPath(const std::string& localPath) ;


    std::string getProcessError() const ;

    void setProcessError(const std::string& processError) ;
private:
    std::string cameraId;      // 摄像头ID
    std::string nvrId;         // NVR设备ID
    std::string fileName;      // 文件名
    std::string fileSize;      // 文件大小（字节）
    int downloadResult;        // 下载结果（1:完成，0:进行中 ,-1:失败）
    std::string localPath;     // 本地下载地址
    std::string processError;  // 下载过程中的错误信息
};

class VideoFiles{

};