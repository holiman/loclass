#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
/**
 * @brief checks if a file exists
 * @param filename
 * @return
 */
int fileExists(const char *filename) {
	struct stat st;
	int result = stat(filename, &st);
	return result == 0;
}

int saveFile(const char *preferredName, const char *suffix, const void* data, size_t datalen)
{
	int size = sizeof(char) * (strlen(preferredName)+strlen(suffix)+5);
	char * fileName = malloc(size);

	memset(fileName,0,size);
	int num = 1;
	sprintf(fileName,"%s.%s", preferredName, suffix);
	while(fileExists(fileName))
	{
		sprintf(fileName,"%s-%d.%s", preferredName, num, suffix);
		num++;
	}
	/* We should have a valid filename now, e.g. dumpdata-3.bin */

	/*Opening file for writing in binary mode*/
	FILE *fileHandle=fopen(fileName,"wb");
	if(!fileHandle) {
		printf("Failed to write to file '%s'\n", fileName);
		return 1;
	}
	fwrite(data, 1,	datalen, fileHandle);
	fclose(fileHandle);
	printf("Saved data to '%s'\n", fileName);
	free(fileName);

	return 0;
}


int loadFile(const char *fileName, void* data, size_t datalen)
{
	FILE *filehandle = fopen(fileName, "rb");
	if(!filehandle) {
		printf("Failed to read from file '%s'\n", fileName);
		return 1;
	}
	fread(data,datalen,1,filehandle); // read 10 bytes to our buffer
	return 0;
}
