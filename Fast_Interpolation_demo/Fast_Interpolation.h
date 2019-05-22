void fastBSAI2X(unsigned char *pIn, unsigned char *pOut, int nWidth,int nHeight);
//fast BSAI two times multiplicaiton  // input is yuv420 format

void fastBSAI4X(unsigned char *pIn, unsigned char *pOut, int nWidth,int nHeight);
//fast BSAI four times multiplicaiton  // input is yuv420 format

void fastBSAI(unsigned char *pOut, int nWidth,int nHeight);
//fast BSAI two times multiplicaiton       //After bicubic interpolation is used

void bicubicConvolutionYUV(unsigned char *pIn, unsigned char *pOut, int nWidth, int nHeight);
//bicubic interpolation   // input is yuv420 format

void bicubicConvolutionY(unsigned char *pIn, unsigned char *pOut, int nWidth, int nHeight);
//bicubic interpolation   // input is Y format

float expfp( float val);
//fast exponential operation