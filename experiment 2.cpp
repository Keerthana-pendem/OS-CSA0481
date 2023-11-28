#include<stdio.h>
int main()
{
	FILE *sourceFile,*destinationFile;
	char ch;
	sourceFile=fopen("file1.txt","rb");
	if(sourceFile==NULL)
	{
		perror("error opening in source File");
		return 1;
	}
	destinationFile=fopen("file2.txt","wb");
	if(destinationFile==NULL)
	{
		perror("error opening in destination File");
		fclose(sourceFile);
		return 1;
	}
	while((ch=fgetc(sourceFile))!=EOF)
	{
		fputc(ch,destinationFile);
	}
	fclose(sourceFile);
	fclose(destinationFile);
	printf("File copied successfully.\n");
	return 0;
}
