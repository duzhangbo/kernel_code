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
int xres, yres, bits_per_pixel, fbsz;
int *fb;
void usage(const char *str, const char *devstr)
{
	fprintf(stderr, "usage:\n");
	fprintf(stderr, "      %s /dev/fbx\n", str);
	exit(1);
}


void draw_point(int x, int y, int col)
{
	*(fb + y*xres + x) = col;
}

int main(int argc, char *argv[])
{
	int fd;
	int j,i;
	int ret;
	struct fb_var_screeninfo info;
	if ((argc != 2)) {
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
	for (i < 0; i < yres; i++) {
		for (j = 0; j < xres; j++) {
				if ((i < yres/2) && (j < xres/2)) {
						draw_point(j, i, (0xff + i*j));
				} else if ((i < yres/2) && (j >= xres/2)) {
						draw_point(j, i, (0xff00 + i*j));
				} else if ((i >= yres/2) && (j < xres/2)) {
						draw_point(j, i, (0xff0000 + i*j));
				} else {
						draw_point(j, i, (0xffff00 + i*j));
				}
		} 

	}
	printf("xres = %d yres = %d \n",xres, yres);
	munmap(fb, fbsz);
	close(fd);

	return 0;
}
