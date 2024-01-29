#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jpeglib.h>

//since pulling from spotify image is standard 640x640
#define IMAGE_HEIGHT 640
#define IMAGE_WIDTH 640

unsigned char buffer[IMAGE_HEIGHT * IMAGE_WIDTH];
unsigned char *row_pointer[1];

int main(void)
{
	//create struct
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	//open file
	FILE *fp = fopen("test2.jpeg", "rb");
	if (!fp)
	{
		printf("Can't open file\n");
		return 1;
	}

	cinfo.err = jpeg_std_error(&jerr);

	//initialize decompression
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE);
	//scale down image
	cinfo.scale_num = 1;
	cinfo.scale_denom = 3;

	//start decompression
	jpeg_start_decompress(&cinfo);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		row_pointer[0] = buffer;
		jpeg_read_scanlines(&cinfo, row_pointer, 1);

		if (cinfo.output_scanline % 3 == 0) //skip every 3rd line
		{
			for (unsigned int i=0; i<cinfo.output_width; i++)
			{
				unsigned char pixel = buffer[i*cinfo.output_components];
				const char *ascii = " .:-=+*#%@"; //shading
				int index = pixel / (256 / (strlen(ascii) - 1)); //get index of shading
				printf("%c", ascii[index]);
			}
			printf("\n");
		}
	}

	//clean up
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(fp);

	return 0;
}
