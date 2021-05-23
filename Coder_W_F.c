#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG

#define BMPINPUTFILE "CP2_Encoded.bmp"
#define MAXCHAR 1000

void Encoder(int argc, char *argv[]);

//void Decode(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	Encoder();
	
	return 0;
}

void Encoder(int argc, char *argv[])
{
	// --------------------------------- START CODE ------------------------------------------
	
	if(argc > 1);
	{
		printf("Help");
	}
	
    /* #ifdef __DEBUG
        printf("DEBUG info: BMP transformer\n");
    #endif */

    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }

     #ifdef __DEBUG
        printf("info: Opening File OK: %s\n", BMPINPUTFILE);
    #endif 

    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header

    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

    #ifdef __DEBUG
        printf("info: breedte = %d\n", breedte);
        printf("info: hoogte = %d\n", hoogte);
    #endif
	
    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file

/*   for(int i =0; i <= 3*8 -1; i+=3)
	{
		printf("pixel %d: B= %d, G=%d, R=%d\n", i/3+1, inputPixels[i], inputPixels[i+1], inputPixels[i+2]);
	} */
	
	// --------------------------------- END START CODE --------------------------------------
	
	// --------------------------------- TXT Reader ------------------------------------------
	
	FILE *fp;
    char str[MAXCHAR];
    char* SecretMessage = "SecretMessage.txt";
	
	int i = 0;
	char SM[MAXCHAR];
 
    fp = fopen(SecretMessage, "rb");
    if (fp == NULL){
        printf("Could not open file %s",SecretMessage);
        return 1;
    }
	
	printf("\nSecret message is: ");
	
    while (fgets(str, MAXCHAR, fp) != NULL){
        printf("%s", str);
	}   
	fclose(fp);
	
	printf("\n");

	// --------------------------------- END TXT Reader --------------------------------------
	
	// --------------------------------- ENCODER ---------------------------------------------
	
	int inputBMP=5;
	char inputTXT[8];
	char output[8];
	
	for(int i=0;i<strlen(str);i++)
	{
		itoa(str[i], inputTXT, 2);	// Conversion to binary
		
/* 		printf("\nletter: %c\n", str[i]);
		printf("%s\n", inputTXT); */
		
		for(int t=0;t<8;t++)
		{
			inputBMP = (inputPixels[i]%2);  // if the number is odd, then lsb 1 is 0 otherwise.
			
			/* printf("\ninputBMP: %d", inputBMP);
			//DEBUG
			printf("\n before: %d",inputPixels[i]); */
			
			if(inputBMP==0)
			{
				if(inputTXT[t]==1);
				{
					inputPixels[i]++;
				}
			}			
			
			else if(inputBMP==1)
			{
				if(inputTXT[t]==0);
				{
					inputPixels[i]--;
				}
			}
			
			/* printf("\n After: %d\n",inputPixels[i]); */
		}
	}

	// --------------------------------- END ENCODER -----------------------------------------
	
	FILE* BMPOut = fopen("BMPOut.bmp","wb");
	
	for(int k=0;k<54;k++)
	{
		fputc(bmpHeader[k],BMPOut);
	}
	
	for(int k=0;k<imageSize;k++)
	{
		fputc(bmpHeader[k],BMPOut);
	}
	
	fclose(inputFilePointer);
    free(inputPixels);
    return 0;
}

/* void Decode(int argc, char *argv[])
{
	
	// --------------------------------- START CODE ------------------------------------------
	
	if(argc > 1);
	{
		printf("Help");
	}
	
    #ifdef __DEBUG
        printf("DEBUG info: BMP transformer\n");
    #endif

    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }

    #ifdef __DEBUG
        printf("DEBUG info: Opening File OK: %s\n", BMPINPUTFILE);
    #endif

    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header

    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

    #ifdef __DEBUG
        printf("DEBUG info: breedte = %d\n", breedte);
        printf("DEBUG info: hoogte = %d\n", hoogte);
    #endif
	
    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file

  	for(int i =0; i <= 3*8 -1; i+=3)
	{
		printf("pixel %d: B= %d, G=%d, R=%d\n", i/3+1, inputPixels[i], inputPixels[i+1], inputPixels[i+2]);
	}
	
	// --------------------------------- END START CODE --------------------------------------
	
	// --------------------------------- DECODER ---------------------------------------------
	
	int inputBMP=5;
	char outputTXT[7];
	char output[MAXCHAR];
	int ENDCODE[7] = {0,0,1,0,1,0,1,0};
    itoa(str[0], inputTXT, 2);	// Conversion to binary
	
	//printf("pixel: %d\n", inputPixels[1]);
	//inputBMP = (inputPixels[1]%2);// if the number is odd, then lsb 1 is 0 otherwise.
	
	i=0;
	int k=0;
	while(outputTXT != ENDCODE){ 
	
		int t=0;
		while(t<=7){
			inputBMP = (inputPixels[k]%2);  // if the number is odd, then lsb 1 is 0 otherwise.
			printf("\ninputBMP: %d", inputBMP);
			
			if(inputBMP==0)
			{
				outputTXT[t] = 0;
			}
			
			else if(inputBMP==1)
			{
				outputTXT[t] = 1;
			}
			
			printf("\n%s",outputTXT[t]);
			
			k++;
			t++;
		}

		i=i+1;
	}
	
 	if(str[i+1]==NULL)
	{
		
		int t=0;
		
		printf("\n*");
		
		while(t<=7){  // END the encoder with * 00101010
			
				inputBMP = (inputPixels[k]%2);  // if the number is odd, then lsb 1 is 0 otherwise.
				
				printf("\ninputTXT: %d", inputTXT[t]);
				
				printf("\ninputBMP: %d", inputBMP);
				
				printf("\n before: %d",inputPixels[k]);
				
				if(inputBMP==0)
				{
					if(inputTXT[i]==1);
					{
						inputPixels[k]++;
					}
				}			
				
				else if(inputBMP==1)
				{
					if(inputTXT[i]==0);
					{
						inputPixels[k]--;
					}
				}			
			
			printf("\n After: %d\n",inputPixels[k]);
			
			k++;
			t++; 
		}
	} 
	
	//fwrite(&bmpfheader,sizeof(BITMAPFILEHEADER),1,fptr);
	
	//fwrite(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer);
	
	// --------------------------------- END DECODER -----------------------------------------

	fclose(inputFilePointer);
    free(inputPixels);
    return 0;
} */