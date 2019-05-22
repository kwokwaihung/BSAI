#include <stdio.h>				//Include the header file of the standard library
#include "WindowDisplay.h"		//	Include the header file of the Image Display Library
//#include <iostream.h>
#include "Fast_Interpolation.h"		//		Include the header file of the FIL


void main()
{
CWindowDisplay wd_Input;
wd_Input.SetWindowTitle("Input");
CWindowDisplay wd_Output;
wd_Output.SetWindowTitle("Output");
	
int nWidth = 208;	//define the width of the video
int nHeight = 120;	//define the height of the video
int nFrame = 300;	//define the number of frames

unsigned char *pIn=new unsigned char [nWidth*nHeight*1.5]; //allocate memory for input frame
//	unsigned char *pOut=new unsigned char [nWidth*nHeight*6];// allocate memory for output frame
unsigned char* pOut=new unsigned char [nWidth*nHeight*24];//allocate memory for output frame
		
	//read and process the video 1 frame by frame
FILE *fp = fopen("video.yuv", "rb");
for(int i=0; i<nFrame; i++){	

fseek ( fp , nWidth*nHeight*3/2*i , SEEK_SET );
fread(pIn,1,nWidth*nHeight*3/2,fp);
		
//Processing the video here
fastBSAI4X(pIn, pOut, nWidth, nHeight);
//Display the result here

wd_Input.LoadYUV420(pIn, nWidth, nHeight);
wd_Output.LoadYUV420(pOut, nWidth*4, nHeight*4);

if(i==0){ printf("Click to start processing"); getchar();}
else if(i==nFrame-1){ printf("Finished processing"); getchar();}
}
	fclose (fp);
	delete pIn; delete pOut;
}

