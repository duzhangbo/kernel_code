#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define MYNAME duzhangbo

int xres, yres, bits_per_pixel, fbsz;
int *fb;
void usage(const char *str, const char *devstr)
{
	fprintf(stderr, "usage:\n");
	fprintf(stderr, "      %s /dev/fbx pic\n", str);
	exit(1);
}


void draw_point(int x, int y, int col)
{
	*(fb + y*xres + x) = col;
}

int main(int argc, char *argv[])
{
	int fd;
	int pic_fd;
	int ret, num;
	struct fb_var_screeninfo info;
	if ((argc != 3)) {
		usage(argv[0], argv[1]);
	}

	fd = open(argv[1], O_RDWR | O_NDELAY);
	assert(fd >= 0);
	ret = ioctl(fd, FBIOGET_VSCREENINFO, &info);
	assert(ret == 0);
	xres = info.xres;
	yres = info.yres;
	bits_per_pixel = info.bits_per_pixel;
	fbsz = xres*yres*bits_per_pixel>>3;

	fb = mmap(NULL, fbsz, PROT_READ | PROT_WRITE,
					MAP_SHARED, fd, 0);
	if (fb == MAP_FAILED) {
			perror("mmap");
			exit(1);
	}

	pic_fd = open(argv[2], O_RDONLY | O_NDELAY);
	assert(pic_fd > 0);
	
	num = 0;

	while(1) {
		lseek64(pic_fd, num*fbsz, SEEK_SET);
		read(pic_fd, fb, fbsz);
		num++;
		if (num > 19) {
			num = 0;
		}
		sleep(1);
		printf("%d \n",num);
	}

	munmap(fb, fbsz);
	close(fd);
	close(pic_fd);

	return 0;
}
