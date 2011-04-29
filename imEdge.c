#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iplib2New.c"

// typedef unsigned char *image_ptr;


image_ptr read_pnm(char *filename, int *rows, int *cols, int *type);
int getnum(FILE *fp);
void write_pnm(image_ptr ptr, char *filename, int rows, int cols, int type);

int ROWS, COLS, TYPE;


int main(int argc, char **argv)
{
 int rows, cols, type, b, a, n, K = 1;
 double threshH, threshV, thresh;
 unsigned long sum =0, sum1 = 0, sum2 = 0, sum3;
 int avgOrig, avgEdgeH, avgEdgeV, avgEdge;
 double  stdOrig, stdEdgeH, stdEdgeV, stdEdge;
 image_ptr imagePtr = read_pnm(argv[1], &rows, &cols, &type);
 image_ptr imagePtr2, imagePtrv, imagePtrh, imagePtra, imagePtrbh, imagePtrbv, imagePtrb;
 unsigned char image2[rows][cols], imageh[rows][cols], imagev[rows][cols], imagea[rows][cols];
 unsigned char binEdgeV[rows][cols], binEdgeH[rows][cols], binEdge[rows][cols];
 image_ptr imageNegPtr;
 int tempv, temph;
 int sh[3][3] = { {-1, -2, -1},{ 0, 0, 0},{ 1, 2, 1}};
 int sv[3][3] = { {-1, 0, 1},{ -2, 0, 2},{ -1, 0, 1}};
       
 int i=0, j=0,  value=0, count=0;
 int tp;
 double ave=0;
 char aveStr[10], *aveStrEnd;

 /* check inputs */
 if (argc != 8)
   {
     printf("wrong inputs: use %s infile out1 out2 out3 out4 out5 out6\n", argv[0]);  
     return 0;
   } 

	n =rows*cols;

 tp = 5;  /* type==5 */

 count=0; 
 for (i=0; i<rows; i++)
   for (j=0; j< cols; j++)
   {
		image2[i][j]=imagePtr[i*cols + j];
		sum += (int)image2[i][j];
   }
	avgOrig = sum/ n ;
	sum =0;
 
 
 imagePtr2=(image_ptr) image2;

 for(i=1; i<(rows-1); i++){
	for(j = 1; j<(cols-1) ; j++){
	tempv =0;
	temph =0;
		for(b = -1; b <= 1; b++){
			for(a = -1; a <= 1; a++){
				tempv += sv[b+1][a+1]*(int)image2[i+b+1][j+a+1];
				temph += sh[b+1][a+1]*(int)image2[i+b+1][j+a+1];
					if(tempv > 255)
						tempv = 255;
					if(temph > 255)
						temph = 255;
			}
		}
	imagev[i][j] = (unsigned char)tempv;
	imageh[i][j] = (unsigned char)temph;
	sum += (int)imagev[i][j];
	sum1 += (int)imageh[i][j];
	imagea[i][j] = (unsigned char) (abs(tempv)+abs(temph));
	sum2 += (int)imagea[i][j];
	}
}
	avgEdgeV = sum / n;
	avgEdgeH = sum1 / n;
	avgEdge = sum2 / n;
	printf("sums %lu %lu %lu\n", sum, sum1, sum2);
	sum2 = 0;
	sum = 0;
	sum1 =0;
	sum3 =0;
	
	for(i=1; i<rows; i++){
		for(j = 1; j<cols ; j++){
			sum += ((int) imageh[i][j] - avgEdgeH)*((int) imageh[i][j] - avgEdgeH);  
			sum1 += ((int) imagev[i][j] - avgEdgeV)*((int) imagev[i][j] - avgEdgeV);
			sum2 += ((int) imagea[i][j] - avgEdge)*((int) imagea[i][j] - avgEdge);
			sum3 += ((int) image2[i][j] - avgEdge)*((int) image2[i][j] - avgEdge);
		}
	}
	
	stdOrig=sqrt(sum2/(n-1));
	stdEdgeH=sqrt(sum/(n-1));
	stdEdgeV=sqrt(sum1/(n-1));
	stdEdge=sqrt(sum3/(n-1));
	threshH = avgEdgeH + K*stdEdgeH;
	threshV = avgEdgeV + K*stdEdgeV;
	thresh = avgEdge + K*stdEdge;	
	printf("ThreshV = %f  ThreshH = %f  Thresh = %f\n", threshV, threshH, thresh);
	
	printf("avg %d %d %d\n", avgEdgeV, avgEdgeH, avgEdge);
	printf("stddev %f %f %f\n", stdEdgeV, stdEdgeH, stdEdge);
	printf("n %d\n", n);
	for(i=1; i<rows; i++){
		for(j = 1; j<cols ; j++){
			if((int)imagev[i][j] >= threshV)
				binEdgeV[i][j] = (unsigned char) 255;
			else
				binEdgeV[i][j] = (unsigned char) 0;
			if((int)imageh[i][j] >= threshH)
				binEdgeH[i][j] = (unsigned char) 255;
			else
				binEdgeH[i][j] = (unsigned char) 0;
			if((int)imagea[i][j] >= thresh)
				binEdge[i][j] = (unsigned char) 255;
			else
				binEdge[i][j] = (unsigned char) 0;
		}
	}
 imagePtrh=(image_ptr) imageh;
 imagePtrv=(image_ptr) imagev;
 imagePtra=(image_ptr) imagea;
 imagePtrbh=(image_ptr) binEdgeH;
 imagePtrbv=(image_ptr) binEdgeV;
 imagePtrb=(image_ptr) binEdge;

 write_pnm(imagePtrh, argv[2], rows, cols, tp); 
 write_pnm(imagePtrv, argv[3], rows, cols, tp);
 write_pnm(imagePtra, argv[4], rows, cols, tp);
 write_pnm(imagePtrbh, argv[5], rows, cols, tp); 
 write_pnm(imagePtrbv, argv[6], rows, cols, tp);
 write_pnm(imagePtrb, argv[7], rows, cols, tp);

 return 0;
}

