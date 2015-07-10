#include <stdlib.h>
#include "ui.h"
#include "test.h"
#include <videodev2.h>
#include <videodev2_samsung.h>
#include "event.h"
#include "process.h"
#include "event_queue.h"
#include <string.h>
#include "console.h"

int rtc_row;
int cw2015_row;
int fan54015_row;
int gyro_row;
static struct win board_test_win =
{
	.title = "Board Test",
	.cur = 0,
	.n = 0,
};

/* sdcard test function */
int sd_test(void)
{
#if 1//ly: sdcard test funciton
	int fd;
	int ret = FAIL;
	char rbuf[10];

	system("mount -t vfat /dev/block/mmcblk0p1 /sdcard");
	usleep(500*1000);

	fd = open("/sdcard/test_sdcard.txt", O_RDWR|O_CREAT, 00664);
	if(fd < 0)
		ret = FAIL;
	else {
		write(fd, "OK", 2);
		lseek(fd, 0, SEEK_SET);
		read(fd, rbuf, 10);
		if(strncmp(rbuf, "OK", 2) == 0)
			ret = OK;
	}

	system("rm -f /sdcard/test_sdcard.txt");

	return ret;
#endif
	return FAIL;
}

int gyro_test(void)
{
	int ret = FAIL;
	int fd = open("/sys/bus/i2c/devices/5-0068/pid", O_RDONLY);
	char pid[4];
	if (fd<0)
	{
		return FAIL;
	}
	read(fd, pid+1, 2);
	pid[0]='v';
	pid[3]='\0';
	if(pid[1] == '4' && pid[2] == '6')
	{
		ui_puts(pid, gyro_row, 6, font_color);
		ret = OK;
	}
	else
		ret = FAIL;

	close(fd);
	return ret;
}

int sensors_test(void)
{
	int ret = FAIL;
	int fd;
	fd = open("/dev/mpu", O_RDONLY);
	if (fd < 0)
	{
		ret = FAIL;
	}
	else
	{
		ret = OK;
		close(fd);
	}
	return ret;
}

#define LSENSOR_ENABLE_NODE "/sys/class/input/input0/enalbe_als"
#define PSENSOR_ENABLE_NODE "/sys/class/input/input0/enalbe_ps"
#define LVAL_NODE "/sys/class/input/input0/lux_adc"
#define PVAL_NODE "/sys/class/input/input0/raw_adc"
int psensor_test(void)
{
	int ret = FAIL;
	int fd;
	char c;
	fd = open(PVAL_NODE, O_RDONLY);
	if (fd < 0)
	{
		ret = FAIL;
	}
	else
	{
		system("echo 1 > " PSENSOR_ENABLE_NODE);
		read(fd, &c, 1);
		if (c < '0' || c > '9')
		{
			ret = FAIL;
		}
		else
		{
			ret = OK;
		}
		close(fd);
		system("echo 0 > " PSENSOR_ENABLE_NODE);
	}
	return ret;
}

int lsensor_test(void)
{
	int ret = FAIL;
	int fd;
	char c;
	fd = open(LVAL_NODE, O_RDONLY);
	if (fd < 0)
	{
		ret = FAIL;
	}
	else
	{
		system("echo 1 > " LSENSOR_ENABLE_NODE);
		read(fd, &c, 1);
		if (c < '0' || c > '9')
		{
			ret = FAIL;
		}
		else
		{
			ret = OK;
		}
		close(fd);
		system("echo 0 > " LSENSOR_ENABLE_NODE);
	}
	return ret;
}

int rtc_test(void)
{
	int ret;
	char date[11];
	char time[9];
	int fd;
	fd = open("/sys/class/rtc/rtc1/date", O_RDONLY);
	if (fd < 0)
	{
		ret = FAIL;
	}
	else
	{
		read(fd, date, 11);
		date[10] = '\0';
		ui_puts(date,rtc_row,5,font_color);
		ret = OK;
		close(fd);
	}
	return ret;
}

/* bluetooth test function  */
int bt_test(void)
{
	int ret = 0;

	ret = system("bteng");
	if (ret < 0)
		return FAIL;

	return OK;
}

int wifi_test(void)
{
	int ret = FAIL;
	int time = 10;
	do{
		if(!system("netcfg wlan0 up")){ 
			ret = OK;
			break;}
		sleep(1);
	}while(time--);
	return ret;
}

int gps_test(void)
{
	
	int fd;
  char nmea[10];
  int count;
	int ret = FAIL;
	system("chmod 777 /sys/class/gpio/export");
	system("echo 128 > /sys/class/gpio/export");
	system("echo 119 > /sys/class/gpio/export");
	sleep(3);
	system("chmod 777 /sys/class/gpio/gpio119/direction");
	system("chmod 777 /sys/class/gpio/gpio128/direction");
	system("chmod 777 /sys/class/gpio/gpio119/value");
	system("chmod 777 /sys/class/gpio/gpio128/value");
	
	system("echo out > /sys/class/gpio/gpio119/direction");
	system("echo out > /sys/class/gpio/gpio128/direction");
	system("echo 1 > /sys/class/gpio/gpio119/value");
  system("echo 1 > /sys/class/gpio/gpio128/value");
  
  system("mkdir /data/gps");
  system("chown system system /data/gps");
  
  system("echo '$pglirm,start_brm,/system/etc/gps/gpsconfig.xml, Periodic' > /data/gps/glgpsctrl");
  sleep(3);
	
	fd = open("/data/gps/nmea_out", O_RDONLY);
		
		if (fd < 0)
	{
		ret = FAIL;
	}
	else
	{
		 count = read(fd, nmea, 10);
		if(count > 0)
			ret = OK;
		else
			ret = FAIL;
		
	}
     system("echo 0 > /sys/class/gpio/gpio128/value");
	return ret;
}

static int audio_test(void)
{
	int times;
	int fd;
	int ret;
	unsigned char data[1024];

	/* set the spk mixer. some mixers just use dfl value */
	ret = system("tinymix 158 1");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 163 1");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 148 1");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 143 1");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 123 1");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 67 1");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 64 3");
	if (ret < 0)
		return FAIL;

	ret = system("tinymix 68 4");
	if (ret < 0)
		return FAIL;

	/* play the test music file for about 3 second */
	ret = system("tinyplay /system/media/audio/alarms/Barium.wav &");
	if (ret < 0)
		return FAIL;

	return OK;
}
#define CHARGER_PATH   "/sys/class/power_supply/54015_test"
#define CHARGER_INFO_PATH	"/sys/class/power_supply/54015_test/device/icinfo"
int charger_test(void)//mj
{
	int fd, ret;
	int exist = 0;
	char exist_str[20];
	char icinfo[8];
	fd = open(CHARGER_INFO_PATH, O_RDONLY);
	if(fd < 0)
	{
		//print("Fail to open %s\n", CHARGER_PATH);
		return FAIL;
	}
	read(fd, icinfo+1, 3);
	icinfo[0] = 'v';
	icinfo[4] = '\0';
	if(icinfo[1] == '1' && icinfo[2] == '4' && icinfo[3] == '8')
	{
		ui_puts(icinfo,fan54015_row,9,font_color);
		ret = OK;
	}
	else
		ret = FAIL;

	close(fd);
	return ret;
}
#define BAT_PATH 	"/sys/class/power_supply/cw2015_test"
#define BAT_VER_PATH	"/sys/class/power_supply/cw2015_test/device/version"
int cw2015_test(void)//mj
{
	int fd, ret;
	char ver[8];
	
	fd = open(BAT_VER_PATH, O_RDONLY);
	if(fd<0)
	{
		//print("Fail to open %s\n", BAT_PATH);
		return FAIL;
	}
	read(fd, ver+1, 3);
	ver[0] = 'v';
	ver[4] = '\0';
	if(ver[1] == '1' && ver[2] == '1' && ver[3] == '0')
	{
		ui_puts(ver,cw2015_row,8,font_color);
		ret = OK;
	}
	else
		ret = FAIL;
	close(fd);
	return ret;
}
#define BAT1_PATH 	"/sys/class/power_supply/max17058_test"
int max17058_test(void)//mj
{
	int fd, ret;
	int vol;
	
	fd = open(BAT1_PATH, O_RDONLY);
	if(fd<0)
	{
		//print("Fail to open %s\n", BAT1_PATH);
		return FAIL;
	}
	close(fd);
	return OK;
}

#if 1
int rear_camera_test(void)
{
               int ret = 0;
               int  index=0;
               int  fd;
               const char *fimc0_device   = "/dev/video0";
               struct v4l2_format fmt;
               struct v4l2_input input;
	        struct v4l2_control ctrl;
               
               fd = open(fimc0_device, O_RDWR);
               if (fd < 0) {
                       printf("fimc0 open fail!!! \n");
                       return -1;
               }
                input.index = index;
                 if (ioctl(fd, VIDIOC_S_INPUT, &input) < 0) {
                       printf("fimc set input fail!!!");
                       close(fd);//we should close fd whatever modify.lzy
                        return -1;
                        }
		#if 0
		//open the flash on 
		    ctrl.id = V4L2_CID_CAMERA_FLASH_MODE;
                  ctrl.value = TORCH_MODE_RECORD;
		    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);   
			if (ret < 0) {
				printf("(1)open flash on fail!!!");
                      	 close(fd);
      				  return -1;
  				  }
		    ctrl.id = V4L2_CID_CAMERA_FLASH_MODE;
		    ctrl.value=FLASH_MODE_TORCH;
		    ret = ioctl(fp, VIDIOC_S_CTRL, &ctrl);
			if (ret < 0) {
				printf("(2)open flash on fail!!!");
                      	 close(fd);
      				  return -1;
  				  }
		//close the flash	
		    ctrl.id=FLASH_MODE_OFF;
		    ret = ioctl(fp, VIDIOC_S_CTRL, &ctrl);
			if (ret < 0) {
				printf("close flash fail!!!");
                      	 close(fd);
      				  return -1;
  				  }
			#endif

			   close(fd);
       return 0;
}

int front_camera_test(void)
{
               int ret = 0;
               int  index=1;
               int  fd;
               const char *fimc0_device   = "/dev/video0";
               struct v4l2_format fmt;
               struct v4l2_input input;
               
               fd = open(fimc0_device, O_RDWR);
               if (fd < 0) {
                       printf("fimc0 open fail!!! \n");
                       return -1;
            			   }
                input.index = index;
                 if (ioctl(fd, VIDIOC_S_INPUT, &input) < 0) {
                       printf("fimc set input fail!!!");
                      close(fd);//we should close fd whatever modify.lzy
                        return -1;
                        }
               close(fd);
       return 0;
}
#endif

/**
 * shaoguodong:
 * if the test code is not ready yet,
 * make sure keep the 'test' feild as NULL
 * the test framework will know that this sub test
 * is NA yet
 */
static struct test_list works[] =
{
	{"SD:",	sd_test},
	{"SIM:", NULL},
	{"SN:", NULL},
	{"CW2015:", cw2015_test},
	{"Charger:", charger_test},
	//{"Max17058:", max17058_test},
	{"Audio:", audio_test},
	{"Bluetooth:", bt_test},
	{"WIFI:", wifi_test},
	{"GPS:", gps_test},
	{"Gyro:", gyro_test},
	{"GSensor:", sensors_test},
	{"MSensor:", sensors_test},
	{"PSensor:", psensor_test},
	{"LSensor:", lsensor_test},
	{"RTC:", rtc_test},
	{"RCamera:", rear_camera_test},
	{"FCamera:", front_camera_test},
	//{"MHL:", NULL},
	{"Flash:", NULL},
};

static void proc_event()
{
	struct event event;
	while (1) {
		dequeue_event_locked(&event);
		if (event.type == KEY_POWER ||
				event.type == HOST_EV_ENTER)
			return;
	}
}

void board_test_win_work(void)
{
	int i;
	int row = 2;
	char to_host[1000];
	char* p, rec;
	int n;
	char* head = "*#rst#*";

	draw_win(&board_test_win);
	for (i = 0; i < sizeof(works)/sizeof(struct test_list); i++) {
		if(!strcmp("RTC:", works[i].name))
		{
			rtc_row = row;
		}
		else if(!strcmp("CW2015:", works[i].name))
		{
			cw2015_row = row;
		}
		else if(!strcmp("Charger:", works[i].name))
		{
			fan54015_row = row;
		}
		else if(!strcmp("Gyro:", works[i].name))
		{
			gyro_row = row;
		}
		ui_puts(works[i].name, row, 1, font_color);
		
		// TODO: simple text  mode
		//print("%s", head);
		print("%s ", works[i].name);
		
		if (works[i].test != NULL) {
			if (works[i].test() == OK) {
				ui_puts_right("OK", row, ok_color);
				print("\033[30;32m OK \033[0m\n");
			}
			else {
				ui_puts_right("FAIL", row, fail_color);
				print("\033[30;31m FAIL \033[0m\n");
			}
		} else {
			ui_puts_right("N/A", row, na_color);
			print("N/A\n");
		}
		row++;

	}
	print("test finished\n");
	proc_event();
	return;
}
