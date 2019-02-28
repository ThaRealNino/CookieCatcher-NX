#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include <switch.h>

#define PIXEL_CHAR '0'

char buffer[3600];
char backBuffer[3600];
int bucketPosition = 0;
int cookie1X = 0;
int cookie1Y = 1;

int flipFlop = 0;

bool printPixel(int position) {

	if(buffer[position] == PIXEL_CHAR) {
	
		return false;
		
	} else {
	
		buffer[position] = PIXEL_CHAR;
		return true;
	}
}

void printCookie(int cookie) {
	
	int printX = 0, printY = 0;
	
	if(cookie == 1) {
		
		printX = cookie1X;
		printY = cookie1Y;
	}
	
	printX += 3;
	printPixel(printY * 80 + (79 - printX));
	
	printX += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX -= 2;
	printY += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX += 3;
	printPixel(printY * 80 + (79 - printX));
	
	printX -= 4;
	printY += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX += 4;
	printPixel(printY * 80 + (79 - printX));

	printY += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX -= 2;
	printPixel(printY * 80 + (79 - printX));
	
	printX -= 3;
	printPixel(printY * 80 + (79 - printX));
	
	printX += 1;
	printY += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX += 3;
	printPixel(printY * 80 + (79 - printX));
	
	printX -= 1;
	printY += 1;
	printPixel(printY * 80 + (79 - printX));
	
	printX -= 1;
	printPixel(printY * 80 + (79 - printX));
	
}	

void printBucket() {
	
	int buckBackup = bucketPosition;

	printPixel(bucketPosition * 80 + 5);
	printPixel(bucketPosition * 80 + 6);
	
	bucketPosition += 1;
	
	printPixel(bucketPosition * 80);
	printPixel(bucketPosition * 80 + 1);
	printPixel(bucketPosition * 80 + 2);
	printPixel(bucketPosition * 80 + 3);
	printPixel(bucketPosition * 80 + 4);
	
	bucketPosition += 1;
	printPixel(bucketPosition * 80);
	
	bucketPosition += 1;
	printPixel(bucketPosition * 80);
	
	bucketPosition += 1;
	printPixel(bucketPosition * 80);
	
	bucketPosition += 1;
	printPixel(bucketPosition * 80);
	
	bucketPosition += 1;
	
	printPixel(bucketPosition * 80);
	printPixel(bucketPosition * 80 + 1);
	printPixel(bucketPosition * 80 + 2);
	printPixel(bucketPosition * 80 + 3);
	printPixel(bucketPosition * 80 + 4);
	
	bucketPosition += 1;
	
	printPixel(bucketPosition * 80 + 5);
	printPixel(bucketPosition * 80 + 6);
	
	bucketPosition = buckBackup;
}

int main(int argc, char* argv[])
{
	
    consoleInit(NULL);
	srand(time(NULL));
	
	
	for(int i = 0; i < 3600; i++) {
			
			buffer[i] = ' ';
	}
	
	strncpy(backBuffer, buffer, 3600);

    while (appletMainLoop())
    {
		strncpy(buffer, backBuffer, 3600);
		
        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break;
		
		if(kDown & KEY_DUP) {
		
			if(bucketPosition > 0) {
			
				bucketPosition -= 1;
			}
		
		} else if(kDown & KEY_DDOWN) {
		
			if(bucketPosition < 37) {
			
				bucketPosition += 1;
			}
		}
		
		consoleClear();
		
		if(flipFlop == 0) {
			
			if(cookie1X < 73) {
		
				cookie1X++;
		
			} else {
		
				cookie1Y = rand() % 39 + 1;
				cookie1X = 0;
			}
			
			flipFlop++;
			
		} else {
			
			flipFlop++;
			
			if(flipFlop == 3) {
			
				flipFlop = 0;
			}
		}
		
		
		printBucket();
		
		printCookie(1);
		
		printf(buffer);

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}