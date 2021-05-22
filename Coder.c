#include <stdio.h>
#include <stdlib.h>

#define __DEBUG

#define BMPINPUTFILE "test.bmp"
#define MAXCHAR 1000

int main(int argc, char *argv[])
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
	
	// --------------------------------- TXT Reader ------------------------------------------
	
	FILE *fp;
    char str[MAXCHAR];
    char* SecretMessage = "SecretMessage.txt";
	
	int i = 0;
	char SM[MAXCHAR];
 
    fp = fopen(SecretMessage, "r");
    if (fp == NULL){
        printf("Could not open file %s",SecretMessage);
        return 1;
    }
	
    while (fgets(str, MAXCHAR, fp) != NULL){
        printf("%s", str);
	}   fclose(fp);
	
	printf("\n");

	// --------------------------------- END TXT Reader --------------------------------------
	
	// --------------------------------- ENCODER ---------------------------------------------
	
	int inputBMP=5;
	char inputTXT[7];
	char output[7];
    itoa(str[0], inputTXT, 2);	// Conversion to binary
	
	//printf("pixel: %d\n", inputPixels[1]);
	//inputBMP = (inputPixels[1]%2);// if the number is odd, then lsb 1 is 0 otherwise.
	
	i=0;
	int k=0;
	while(str[i]!=NULL){ 
	
		itoa(str[i], inputTXT, 2);	// Conversion to binary
		
		printf("letter: %c\n", str[i]);
		printf("%s\n", inputTXT);
		int t=0;
		while(t<=7){
			inputBMP = (inputPixels[k]%2);  // if the number is odd, then lsb 1 is 0 otherwise.
			printf("pixel: %d\n", inputPixels[k]);
			printf("%d\n", inputBMP);

			printf("%d",k);
			k++;
			t++;
		}

		i=i+1;
	}
	
	// --------------------------------- END ENCODER -----------------------------------------
	
	fclose(inputFilePointer);
    free(inputPixels);
    return 0;
}