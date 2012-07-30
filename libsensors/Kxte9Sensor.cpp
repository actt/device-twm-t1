/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>

//#include <linux/akm8973.h>

#include <cutils/log.h>

#include "Kxte9Sensor.h"
#include "Yas529Sensor.h"
#include "OrientSensor.h"

/*****************************************************************************/

KXTE9Sensor::KXTE9Sensor()
: SensorBase(NULL, "kxte9_accel"),
      mEnabled(0),
      mPendingMask(0),
      mInputReader(1)
{
    memset(&mPendingEvent, 0, sizeof(mPendingEvent));

    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_A;
    mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
    mPendingEvent.acceleration.status = SENSOR_STATUS_ACCURACY_HIGH;

	mDelay = 200000000; // 200 ms by default

    // read the actual value of all sensors if they're enabled already
    struct input_absinfo absinfo;
    short flags = 0;

    open_device();
	mEnabled = 1;
	if (!ioctl(data_fd, EVIOCGABS(EVENT_TYPE_ACCEL_X), &absinfo)) {
		mPendingEvent.acceleration.x = absinfo.value * CONVERT_A_X;
	}
	if (!ioctl(data_fd, EVIOCGABS(EVENT_TYPE_ACCEL_Y), &absinfo)) {
		mPendingEvent.acceleration.y = absinfo.value * CONVERT_A_Y;
	}
	if (!ioctl(data_fd, EVIOCGABS(EVENT_TYPE_ACCEL_Z), &absinfo)) {
		mPendingEvent.acceleration.z = absinfo.value * CONVERT_A_Z;
	}
    mEnabled = 1;

    if (!mEnabled) {
        close_device();
    }
}

KXTE9Sensor::~KXTE9Sensor() {
}

int KXTE9Sensor::enable(int32_t handle, int en)
{
    int newState  = en ? 1 : 0;

	if(mEnabled != newState) {
        if (!mEnabled) {
            open_device();
        }

		mEnabled = newState;
        setDelay(0,200000000);
        if (!mEnabled) {
            close_device();
        }
	}
	return 0;
}

int KXTE9Sensor::setDelay(int32_t handle, int64_t ns)
{
	char cmd[8];
	int fd;

    if (mEnabled) {
        if (ns < 0)
            return -EINVAL;

		int delay = ns / 1000000;
		LOGE("fengzhe delay=0x%x",delay);
		sprintf(cmd,"%d",delay);
		LOGE("fengzhe delay cmd=%s\n",cmd);
		fd  = open("/sys/devices/i2c-0/0-000f/delay",O_WRONLY);
		if(fd < 0){
			LOGE("fengzhe error setup delay");
			return -1;
		}
		if(write(fd,cmd,strlen(cmd)) < 0){
			LOGE("fengzhe write failed to setup delay");
		}
		close(fd);	

    }
	return 0;
}

int KXTE9Sensor::readEvents(sensors_event_t* data, int count)
{
	if (count < 1)
        return -EINVAL;

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
        return n;

    int numEventReceived = 0;
    input_event const* event;

	while (count && mInputReader.readEvent(&event)) {
		int type = event->type;
		if (type == EV_ABS) {
			processEvent(event->code, event->value);
		} else if (type == EV_SYN) {
            mPendingEvent.timestamp = timevalToNano(event->time);
            *data++ = mPendingEvent;
            count--;
            numEventReceived++;
        } else {
            LOGE("KXTE9Sensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }

    return numEventReceived;
}

void KXTE9Sensor::processEvent(int code, int value)
{
    switch (code) {
        case EVENT_TYPE_ACCEL_X:
            mPendingMask = 1;
            mPendingEvent.acceleration.x = ((float)((value >>2) - 32)) * CONVERT_A_X;
            break;
        case EVENT_TYPE_ACCEL_Y:
            mPendingMask = 1;
            mPendingEvent.acceleration.y = ((float)((value >>2) - 32)) * CONVERT_A_Y;
			break;
        case EVENT_TYPE_ACCEL_Z:
            mPendingMask = 1;
            mPendingEvent.acceleration.z = ((float)((value >>2) - 32)) * CONVERT_A_Z;
            break;
    }
}
