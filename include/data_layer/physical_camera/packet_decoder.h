#ifndef PACKET_DECODE_H
#define PACKET_DECODE_H

#include <libavcodec/avcodec.h>
#include <vector>
class PacketDecoder {
    public:
        PacketDecoder();
        ~PacketDecoder();

        bool open(const AVCodecParameters* params);// 初始化解码器
        bool decode(AVPacket* packet,std::vector<AVFrame*>& frames);// 进行解码
        void flush();// 刷新解码器
        void close();
    
    private:
        AVCodecContext* codecCtx_ = nullptr; //解码器上下文
        const AVCodec* codec_ = nullptr; //解码器
        int videoWidth_;
        int videoHeight_;
};

#endif