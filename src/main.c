#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "sample_common.h"
#include "rtsp_demo.h"
#include "rkmedia_api.h"
#include "rkmedia_venc.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

// #define REMOTE_SERVER "192.168.1.242"
#define REMOTE_SERVER "43.139.145.196"
#define REMOTE_PORT 9999
#define REMOTE_TCP_PORT 9998

#define UDP_PACK_SIZE 1024

rtsp_demo_handle g_rtsplive = NULL;
static rtsp_session_handle g_rtsp_session;
static bool quit = false;
static struct timeval last_sec_tv;
static struct timeval tv_now;
int sockfd;
struct sockaddr_in server_addr;

static void sigterm_handler(int sig)
{
    fprintf(stderr, "signal %d\n", sig);
    quit = true;
}

// 发送数据给tcp服务器
void send_data_to_tcp(char *server_ip, int port, const char *data, int data_len)
{

    // 发送数据
    send(sockfd, data, data_len, 0);
}

// 发送数据给udp服务器
void send_data_to_udp(char *server_ip, int port, const char *data, int data_len)
{

    // 创建UDP套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(port);

    // 发送数据
    sendto(sockfd, data, data_len, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    close(sockfd);
}

// 改用TCP方式发送
void video_packet_cb(MEDIA_BUFFER mb)
{
    static RK_S32 packet_cnt = 0;
    if (quit)
        return;

    gettimeofday(&tv_now, NULL);

    uint8_t *buf_data = RK_MPI_MB_GetPtr(mb);
    uint32_t buf_size = RK_MPI_MB_GetSize(mb);

    // 使用udp发送数据到remote server
    // char sendline[buf_size];
    char *sendline = NULL;
    int n;
    int i = 0;
    // int pack_size = UDP_PACK_SIZE;
    int pack_num = buf_size / UDP_PACK_SIZE;
    int last_pack_size = buf_size % UDP_PACK_SIZE;
    int total_bytes = pack_num * UDP_PACK_SIZE + last_pack_size;

    // 分包发送所有数据
    for (i = 0; i < pack_num; i++)
    {
        sendline = buf_data + i * UDP_PACK_SIZE;
        send_data_to_tcp(REMOTE_SERVER, REMOTE_PORT, sendline, UDP_PACK_SIZE);
        usleep(1000);
    }

    if (last_pack_size > 0)
    {
        sendline = buf_data + pack_num * UDP_PACK_SIZE;
        send_data_to_tcp(REMOTE_SERVER, REMOTE_PORT, sendline, last_pack_size);
    }

    // 统计帧率
    static uint32_t bytes_sent = 0;
    bytes_sent = bytes_sent + buf_size;

    if (tv_now.tv_sec - last_sec_tv.tv_sec >= 1)
    {
        printf("bytes total: %d\n", bytes_sent);
        bytes_sent = 0;
        last_sec_tv = tv_now;
    }

    RK_MPI_MB_ReleaseBuffer(mb);
}

void video_packet_cb_udp(MEDIA_BUFFER mb)
{

    static RK_S32 packet_cnt = 0;
    if (quit)
        return;

    // gettimeofday(&tv_now);

    gettimeofday(&tv_now, NULL);

    uint8_t *buf_data = RK_MPI_MB_GetPtr(mb);
    uint32_t buf_size = RK_MPI_MB_GetSize(mb);

    // 使用udp发送数据到remote server
    // char sendline[buf_size];
    char *sendline = NULL;
    int n;
    int i = 0;
    // int pack_size = UDP_PACK_SIZE;
    int pack_num = buf_size / UDP_PACK_SIZE;
    int last_pack_size = buf_size % UDP_PACK_SIZE;
    int total_bytes = pack_num * UDP_PACK_SIZE + last_pack_size;

    // 分包发送所有数据
    for (i = 0; i < pack_num; i++)
    {
        // memcpy(sendline, buf_data + i * UDP_PACK_SIZE, UDP_PACK_SIZE);
        sendline = buf_data + i * UDP_PACK_SIZE;
        send_data_to_udp(REMOTE_SERVER, REMOTE_PORT, sendline, UDP_PACK_SIZE);
        usleep(1000);
    }

    if (last_pack_size > 0)
    {
        sendline = buf_data + pack_num * UDP_PACK_SIZE;
        // memcpy(sendline, buf_data + pack_num * UDP_PACK_SIZE, last_pack_size);
        send_data_to_udp(REMOTE_SERVER, REMOTE_PORT, sendline, last_pack_size);
    }

    // 统计帧率
    static uint32_t bytes_sent = 0;
    bytes_sent = bytes_sent + buf_size;

    if (tv_now.tv_sec - last_sec_tv.tv_sec >= 1)
    {
        printf("bytes total: %d\n", bytes_sent);
        bytes_sent = 0;
        last_sec_tv = tv_now;
    }

    RK_MPI_MB_ReleaseBuffer(mb);
}

void video_packet_cb_rtsp(MEDIA_BUFFER mb)
{
    int buf_size = 0;
    static RK_S32 packet_cnt = 0;
    if (quit)
        return;
    gettimeofday(&tv_now, NULL);

    if (g_rtsplive && g_rtsp_session)
    {
        buf_size = RK_MPI_MB_GetSize(mb);

        rtsp_tx_video(g_rtsp_session, RK_MPI_MB_GetPtr(mb), RK_MPI_MB_GetSize(mb),
                      RK_MPI_MB_GetTimestamp(mb));
        rtsp_do_event(g_rtsplive);

        static uint32_t bytes_sent = 0;
        bytes_sent = bytes_sent + buf_size;
        uint32_t time_gap = tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000 - last_sec_tv.tv_sec * 1000 + last_sec_tv.tv_usec / 1000;

        if (time_gap >= 1000)
        {
            printf("bytes total: %d KB %d kb time_gap :%d\n", bytes_sent / 1024, bytes_sent / 128, time_gap);
            bytes_sent = 0;
            last_sec_tv = tv_now;
        }
    }

    RK_MPI_MB_ReleaseBuffer(mb);
    packet_cnt++;
}

int main(int argc, char *argv[])
{
    RK_U32 u32Width = 1920;
    RK_U32 u32Height = 1080;
    RK_CHAR *pDeviceName = "rkispp_scale0";
    RK_CHAR *pIqfilesPath = "/oem/etc/iqfiles";
    CODEC_TYPE_E enCodecType = RK_CODEC_TYPE_H264;
    RK_CHAR *pCodecName = "H264";
    RK_S32 s32CamId = 0;
    RK_BOOL bMultictx = RK_FALSE;
    int c;
    int ret = 0;
    printf("#Device: %s\n", pDeviceName);
    printf("#CodecName:%s\n", pCodecName);
    printf("#Resolution: %dx%d\n", u32Width, u32Height);
    printf("#CameraIdx: %d\n\n", s32CamId);
    printf("#bMultictx: %d\n\n", bMultictx);
    printf("#Aiq xml dirpath: %s\n\n", pIqfilesPath);

    rk_aiq_working_mode_t hdr_mode = RK_AIQ_WORKING_MODE_NORMAL;
    int fps = 30;
    SAMPLE_COMM_ISP_Init(s32CamId, hdr_mode, bMultictx, pIqfilesPath);
    SAMPLE_COMM_ISP_Run(s32CamId);
    SAMPLE_COMM_ISP_SetFrameRate(s32CamId, fps);

    // 创建TCP套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(REMOTE_SERVER);
    server_addr.sin_port = htons(REMOTE_TCP_PORT);

    // 连接服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // init rtsp
    g_rtsplive = create_rtsp_demo(554);
    g_rtsp_session = rtsp_new_session(g_rtsplive, "/live/main_stream");
    rtsp_set_video(g_rtsp_session, RTSP_CODEC_ID_VIDEO_H264, NULL, 0);
    rtsp_sync_video_ts(g_rtsp_session, rtsp_get_reltime(), rtsp_get_ntptime());

    RK_MPI_SYS_Init();
    VI_CHN_ATTR_S vi_chn_attr;
    vi_chn_attr.pcVideoNode = pDeviceName;
    vi_chn_attr.u32BufCnt = 3;
    vi_chn_attr.u32Width = u32Width;
    vi_chn_attr.u32Height = u32Height;
    vi_chn_attr.enPixFmt = IMAGE_TYPE_NV12;
    vi_chn_attr.enBufType = VI_CHN_BUF_TYPE_MMAP;
    vi_chn_attr.enWorkMode = VI_WORK_MODE_NORMAL;
    ret = RK_MPI_VI_SetChnAttr(s32CamId, 0, &vi_chn_attr);
    ret |= RK_MPI_VI_EnableChn(s32CamId, 0);
    if (ret)
    {
        printf("ERROR: create VI[0] error! ret=%d\n", ret);
        return 0;
    }

    VENC_CHN_ATTR_S venc_chn_attr;
    memset(&venc_chn_attr, 0, sizeof(venc_chn_attr));
    venc_chn_attr.stVencAttr.enType = RK_CODEC_TYPE_H264;
    venc_chn_attr.stRcAttr.enRcMode = VENC_RC_MODE_H264CBR;
    venc_chn_attr.stRcAttr.stH264Cbr.u32Gop = 30;
    venc_chn_attr.stRcAttr.stH264Cbr.u32BitRate = u32Width * u32Height;
    // frame rate: in 30/1, out 30/1.
    venc_chn_attr.stRcAttr.stH264Cbr.fr32DstFrameRateDen = 1;
    venc_chn_attr.stRcAttr.stH264Cbr.fr32DstFrameRateNum = 30;
    venc_chn_attr.stRcAttr.stH264Cbr.u32SrcFrameRateDen = 1;
    venc_chn_attr.stRcAttr.stH264Cbr.u32SrcFrameRateNum = 30;

    venc_chn_attr.stVencAttr.imageType = IMAGE_TYPE_NV12;
    venc_chn_attr.stVencAttr.enRotation = VENC_ROTATION_270;
    venc_chn_attr.stVencAttr.u32PicWidth = u32Width;
    venc_chn_attr.stVencAttr.u32PicHeight = u32Height;
    venc_chn_attr.stVencAttr.u32VirWidth = u32Width;
    venc_chn_attr.stVencAttr.u32VirHeight = u32Height;
    venc_chn_attr.stVencAttr.u32Profile = 77;
    ret = RK_MPI_VENC_CreateChn(0, &venc_chn_attr);
    if (ret)
    {
        printf("ERROR: create VENC[0] error! ret=%d\n", ret);
        return 0;
    }

    MPP_CHN_S stEncChn;
    stEncChn.enModId = RK_ID_VENC;
    stEncChn.s32DevId = 0;
    stEncChn.s32ChnId = 0;
    ret = RK_MPI_SYS_RegisterOutCb(&stEncChn, video_packet_cb);
    if (ret)
    {
        printf("ERROR: register output callback for VENC[0] error! ret=%d\n", ret);
        return 0;
    }

    MPP_CHN_S stSrcChn;
    stSrcChn.enModId = RK_ID_VI;
    stSrcChn.s32DevId = 0;
    stSrcChn.s32ChnId = 0;
    MPP_CHN_S stDestChn;
    stDestChn.enModId = RK_ID_VENC;
    stDestChn.s32DevId = 0;
    stDestChn.s32ChnId = 0;
    ret = RK_MPI_SYS_Bind(&stSrcChn, &stDestChn);
    if (ret)
    {
        printf("ERROR: Bind VI[0] and VENC[0] error! ret=%d\n", ret);
        return 0;
    }

    printf("%s initial finish\n", __func__);
    signal(SIGINT, sigterm_handler);
    while (!quit)
    {
        usleep(500000);
    }

    printf("%s exit!\n", __func__);
    if (g_rtsplive)
        rtsp_del_demo(g_rtsplive);

    // unbind first
    ret = RK_MPI_SYS_UnBind(&stSrcChn, &stDestChn);
    if (ret)
    {
        printf("ERROR: UnBind VI[0] and VENC[0] error! ret=%d\n", ret);
        return 0;
    }
    // destroy venc before vi
    ret = RK_MPI_VENC_DestroyChn(0);
    if (ret)
    {
        printf("ERROR: Destroy VENC[0] error! ret=%d\n", ret);
        return 0;
    }
    // destroy vi
    ret = RK_MPI_VI_DisableChn(s32CamId, 0);
    if (ret)
    {
        printf("ERROR: Destroy VI[0] error! ret=%d\n", ret);
        return 0;
    }

    if (pIqfilesPath)
    {
        SAMPLE_COMM_ISP_Stop(s32CamId);
    }
    close(sockfd);
    return 0;
}
