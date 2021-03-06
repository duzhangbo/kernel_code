
#include "fb.h"

struct r_jpeg_error_mgr
{
	struct jpeg_error_mgr pub;
	jmp_buf envbuffer;
};


int is_jpeg(char *filename)
{
	int fd;
	unsigned char id[10];

	fd = open(filename,O_RDONLY);
	if(fd==-1) 
		return 0;

	read(fd,id,10);

	close(fd);
	
	if(id[6] == 'J' && id[7] == 'F' && id[8] == 'I' && id[9] == 'F') 
		return 1;

	if(id[0] == 0xff && id[1] == 0xd8 && id[2] == 0xff)
		return 1;

	return 0;
}


void jpeg_cb_error_exit(j_common_ptr cinfo)
{
	struct r_jpeg_error_mgr *mptr;
	mptr = (struct r_jpeg_error_mgr*) cinfo->err;
	cinfo->err->output_message(cinfo);
	longjmp(mptr->envbuffer,1);
}

int jpeg_load(char *filename,unsigned char *buffer, int x,int y)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_decompress_struct *ciptr;
	struct r_jpeg_error_mgr emgr;
	unsigned char *bp;
	int px;
	int py;
	int c;
	FILE *fh;
	JSAMPLE *lb;

	ciptr = &cinfo;

	if(!(fh = fopen(filename,"rb"))) 
		return -1;

	ciptr->err = jpeg_std_error(&emgr.pub);

	emgr.pub.error_exit = jpeg_cb_error_exit;
	if(setjmp(emgr.envbuffer) == 1)
	{
		jpeg_destroy_decompress(ciptr);
		fclose(fh);
		return -1;
	}

	jpeg_create_decompress(ciptr);
	jpeg_stdio_src(ciptr,fh);
	jpeg_read_header(ciptr,TRUE);
	
	ciptr->out_color_space = JCS_RGB;
	
	jpeg_start_decompress(ciptr);

	px = ciptr->output_width; 
	py = ciptr->output_height;
	c = ciptr->output_components;


	if(c == 3)
	{
		lb = ciptr->mem->alloc_small((j_common_ptr)ciptr,JPOOL_PERMANENT, c * px);
		bp = buffer;
		while(ciptr->output_scanline < ciptr->output_height)
		{
			jpeg_read_scanlines(ciptr, &lb, 1);
			memcpy(bp,lb,px * c);
			bp += px * c;
		}					   

	}

	jpeg_finish_decompress(ciptr);
	jpeg_destroy_decompress(ciptr);
	fclose(fh);
	return 0;
}

int jpeg_getsize(char *filename,int *x,int *y)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_decompress_struct *ciptr;
	struct r_jpeg_error_mgr emgr;
	int px,py,c;
	FILE *fh;

	ciptr = &cinfo;
	if(!(fh = fopen(filename,"rb"))) 
		return -1;

	ciptr->err = jpeg_std_error(&emgr.pub);

	emgr.pub.error_exit = jpeg_cb_error_exit;
	if(setjmp(emgr.envbuffer) == 1)
	{
		jpeg_destroy_decompress(ciptr);
		fclose(fh);
		return -1;
	}

	jpeg_create_decompress(ciptr);

	jpeg_stdio_src(ciptr,fh);

	jpeg_read_header(ciptr,TRUE);

	ciptr->out_color_space = JCS_RGB;

	jpeg_start_decompress(ciptr);
	
	px = ciptr->output_width; 
	py = ciptr->output_height;
	c = ciptr->output_components;
	
	*x = px;
	*y = py;

	jpeg_destroy_decompress(ciptr);

	fclose(fh);
	
	return 0;
}

