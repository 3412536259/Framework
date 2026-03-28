#pragma once
#include <string>
#include <vector>

//录像的文件信息
struct VideoFileInfo {
    std::string starttime;  // 开始时间 yyyy-MM-dd HH:mm:ss
    std::string endtime;    // 结束时间 yyyy-MM-dd HH:mm:ss
    std::string filename;   // 文件名
    unsigned int filesize;  // 文件大小（字节）
    bool valid = false;
};

struct VideoFileInfos {
    bool isSuccess;         // 查询是否成功
    std::string errorMsg;   // 错误信息（失败时填充）
    std::vector<VideoFileInfo> fileList; // 录像文件列表
};


struct DownloadFile{
    std::string fileName;    // 文件名
    int downloadResult;     // 下载结果（1:完成，0进行中 ,-1:失败） //std::atomic<int> downloadResult{0};
    std::string localPath; //下载地址
    std::string processError;

    // ===== 工具函数 =====
    bool isFinished() const {
        if(downloadResult == 0) return true;
        else return false;
    }

    bool isSuccess() const {
        return downloadResult == 1;
    }
};