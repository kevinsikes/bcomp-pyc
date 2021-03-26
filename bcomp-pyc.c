/************************************
Beyond Compare conversion program
Mask header bytes 4-15 for .pyc files
Author: Kevin Sikes
*************************************/

#include <stdio.h>

#define BUFFER_SIZE 4096
#define IGNORE_OFFSET_BEGIN	 4
#define IGNORE_OFFSET_END	15

int main(int argc, char* argv[])
{
	int retval = 1;
	
	if (argc > 2)
	{
		FILE *infile, *outfile;
		if ((infile = fopen(argv[1], "rb")) != NULL)
		{
			if ((outfile = fopen(argv[2], "wb")) != NULL)
			{
				size_t len;
				char buf[BUFFER_SIZE];
				int firstTime = 1;
				
				while (!feof(infile) && (len = fread(buf, sizeof(char), BUFFER_SIZE, infile)) > 0)
				{
					if (firstTime)
					{
						/* zero out the unimportant header bytes */
						int i;
						for (i = IGNORE_OFFSET_BEGIN; i <= IGNORE_OFFSET_END; i++)
						{
							buf[i] = 0;
						}
						firstTime = 0;
					}
					fwrite(buf, sizeof(char), len, outfile);
				}
				fclose(outfile);
				retval = 0;
			}
			fclose(infile);
		}
	}
	
	return retval;
}