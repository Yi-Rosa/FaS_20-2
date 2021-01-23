#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	FILE *outfp;
	int i = 0;

	fp = fopen("test (2).zip", "r");
	outfp = fopen("data.txt", "w");

	while (feof(fp) == 0) {

		unsigned long signature;
		fread(&signature, 1, sizeof(signature), fp);

		if (signature != 0x04034b50) {
			break;
		}
		++i;
		
		unsigned long uncompressed_size;
		unsigned short filename_len;
		fseek(fp, 18, SEEK_CUR);

		fread(&uncompressed_size, 1, sizeof(uncompressed_size), fp);

		fread(&filename_len, 1, sizeof(filename_len), fp);
		//printf("%x\n", filename_len);
		
		fseek(fp, 2, SEEK_CUR);
		
		char* filename = (char*)malloc(filename_len + 1);
		fread(filename, 1, filename_len, fp);
		filename[filename_len] = '\0';
		fwrite(filename, 1, filename_len, outfp);

		char* data = (char*)malloc(uncompressed_size);
		fread(data, 1, uncompressed_size, fp);
		fwrite(data, 1, uncompressed_size, outfp);
		int data_start = i * 30 + filename_len;

		

		printf("\nfilename : %s \t데이터 시작 offset : %d\n", filename, data_start);

		free(filename);
	}
	fclose(outfp);
	fclose(fp);
}