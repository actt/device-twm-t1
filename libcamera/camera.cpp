#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <dirent.h>
#include <strings.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <cutils/log.h>

//#include <linux/input.h>
//#include <hardware/sensors.h>
#include <linux/ioctl.h>
#include <linux/android_pmem.h>
//#include <camera/CameraParameters.h>
#include <camera/CameraHardwareInterface.h>
#include "QualcommCameraHardware.h"

//#include <camera/ICameraService.h>
//#include <cutils/properties.h>

//namespace android {
using namespace android;

int mCameraControlFd;

int native_set_parm(
    cam_ctrl_type type, uint16_t length, void *value)
{
    struct msm_ctrl_cmd ctrlCmd;

    ctrlCmd.timeout_ms = 5000;
    ctrlCmd.type       = (uint16_t)type;
    ctrlCmd.length     = length;
    // FIXME: this will be put in by the kernel
    ctrlCmd.resp_fd    = mCameraControlFd;
    ctrlCmd.value = value;

    LOGV("%s: fd %d, type %d, length %d", __FUNCTION__,
         mCameraControlFd, type, length);
    if (ioctl(mCameraControlFd, MSM_CAM_IOCTL_CTRL_COMMAND, &ctrlCmd) < 0 ||
                ctrlCmd.status != CAM_CTRL_SUCCESS) {
        LOGE("%s: error (%s): fd %d, type %d, length %d, status %d",
             __FUNCTION__, strerror(errno),
             mCameraControlFd, type, length, ctrlCmd.status);
        return false;
    }
    return true;
}


cam_ctrl_dimension_t mdim;
int main (int argc,char *argv[]){
	int fd;
	int ret;
	unsigned char buffer[32];
	unsigned char cmd[32];
	sp<CameraHardwareInterface> cam;

	struct msm_camsensor_info mSensorInfo;
#if 1
//    LOGD("openCameraHardware: call createInstance");
   cam =  QualcommCameraHardware::createInstance();

	while(1){
	printf("sleeping...Zzz.z...\n");
		sleep(10);
	}
#endif

#if 0 
	fd = open("/dev/msm_camera/control0",O_RDWR);	
	if( fd < 0){
		printf("open error\n");
	}
	mCameraControlFd = fd;
	mdim.picture_width = 1024;
	mdim.picture_height = 768;

	ret = native_set_parm(CAMERA_SET_PARM_DIMENSION,
                    sizeof(cam_ctrl_dimension_t), &mdim);
    LOGD("%s :ret=%d",__func__,ret);
	if(ret < 0){
		printf("error\n");
		return -1;
	}

	printf("mdim.width=%d height=%d\n",mdim.picture_width,mdim.picture_height);

#if 0
    memset(&mSensorInfo, 0, sizeof(mSensorInfo));
    if (ioctl(fd,
              MSM_CAM_IOCTL_GET_SENSOR_INFO,
              &mSensorInfo) < 0)
        printf("%s: cannot retrieve sensor info!", __FUNCTION__);
    else
        printf("%s: camsensor name %s, flash %d", __FUNCTION__,
             mSensorInfo.name, mSensorInfo.flash_enabled);	
#endif
#endif
#if 0
	input_read_main(argc ,argv);		
	sscanf(argv[1],"%x",&cmd[0]);
	printf("0x%x = %d\n",cmd[0],cmd[0]);
	fd = open("/dev/kxte9",O_RDWR);
	if(fd  < 0){
		printf("faild to open /dev/kxte9\n");
	}
	buffer[0] = 0x0c;
	ret =  write(fd, cmd, 1);
	if(ret < 0) {
		printf("faild to write\n");
		return -1;
	}
	ret =  read(fd, buffer, 1);
	if(ret < 0) {
		printf("faild to write\n");
		return -1;
	}
	printf("read 0x%X\n",buffer[0]);
#endif
	
}
//}
