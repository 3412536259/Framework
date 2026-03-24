#include "data_layer/physical_camera/packet_decoder.h"

PacketDecoder::PacketDecoder() {

}

PacketDecoder::~PacketDecoder() {

}

bool PacketDecoder::open(const AVCodecParameters* params) {
    codec_ = avcodec_find_decoder(params -> codec_id);
    if(!codec_) return false;

    codecCtx_ = avcodec_alloc_context3(codec_);
    if(!codecCtx_) return false;

    if(avcodec_parameters_to_context(codecCtx_,params) < 0)
        return false;
    
    if(avcodec_open2(codecCtx_,codec_,nullptr) < 0)
        return false;

    videoWidth_ = codecCtx_ -> width;
    videoHeight_ = codecCtx_ -> height;

    return true;
}

bool PacketDecoder::decode(AVPacket* packet,std::vector<AVFrame*>& frames) {
    int ret = avcodec_send_packet(codecCtx_,packet);

    if(ret < 0) 
        return false;
    
    while(ret >= 0) {
        AVFrame* frame = av_frame_alloc();
        
        ret = avcodec_receive_frame(codecCtx_,frame);

        if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            av_frame_free(&frame);
            break;
        }

        if( ret < 0) {
            av_frame_free(&frame);
            return false;
        }
        frames.push_back(frame);
    }
    return true;
}

void PacketDecoder::flush() {
    avcodec_send_packet(codecCtx_,nullptr);

    while(true) {
        AVFrame* frame = av_frame_alloc();

        int ret = avcodec_receive_frame(codecCtx_,frame);

        if(ret == AVERROR_EOF || ret == AVERROR(EAGAIN)) {
            av_frame_free(&frame);
            break;
        }
        av_frame_free(&frame);
    }
    avcodec_flush_buffers(codecCtx_);
}

void PacketDecoder::close() {
    if(codecCtx_) {
        avcodec_free_context(&codecCtx_);
        codecCtx_ = nullptr;
    }
}