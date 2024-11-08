#include <stdio.h>                  /*  Marr-Hildreth.c  (or marrh.c) */
#include <math.h>
#define  PICSIZE 256
#define  MAXMASK 100

int pic[PICSIZE][PICSIZE];
double outpic1[PICSIZE][PICSIZE];
double outpic2[PICSIZE][PICSIZE];
int edgeflag[PICSIZE][PICSIZE];
int peaks[PICSIZE][PICSIZE];
int finalPic[PICSIZE][PICSIZE];
double xmask[MAXMASK][MAXMASK];
double ymask[MAXMASK][MAXMASK];
double xconv[PICSIZE][PICSIZE];
double yconv[PICSIZE][PICSIZE];
double ival[PICSIZE][PICSIZE];

int main(argc,argv)
int argc;
char **argv;
{
        int     i,j,p,q,s,t,mr,centx,centy;
        int high = 100;
        int low = 35;
        double maskxval, maskyval, sumx, sumy, sig, maxval, minval, maxival, minival;
        char pic1[100], pic2[100], pic3[100], pic4[100];
        FILE    *fo1, *fo2,*fp1, *fopen();
        char    *foobar;
        float slope = 0.00;

        printf("Enter source file name:\n");
        scanf("%s", pic1);
        foobar = pic1;

        if((fp1=fopen(pic1,"r"))==NULL) printf("can't open input file\n");
        printf("found %s \n", pic1);
        fp1 = fopen(foobar, "rb");

        // Magnitude
        printf("Enter first output file name:\n");
        scanf("%s", pic2);
        foobar = pic2;
        fo1 = fopen(foobar, "wb");

        // Hi Threshold
        printf("final output file name:\n");
        scanf("%s", pic3);
        foobar = pic3;
        fo2 = fopen(foobar, "wb");
        sig = 1.0;

        fprintf(fo1, "P5\n256 256\n255\n");
        fprintf(fo2, "P5\n256 256\n255\n");

        mr = (int)(sig * 3);
        centx = (MAXMASK / 2);
        centy = (MAXMASK / 2);

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                }
        }

        // Create masks for the first x and y derivatives
        for (p = -mr; p <= mr; p++)
        {
            for (q = -mr; q <= mr; q++)
            {
                maskxval = -q * (exp(-1 * ((p * p + q * q) / (2 * sig * sig))));
                maskyval = -p * (exp(-1 * ((p * p + q * q) / (2 * sig * sig))));
                xmask[p + centy][q + centx] = maskxval;
                ymask[p + centy][q + centx] = maskyval;
            }
        }

        // Convolve with the x mask
        for (i = mr; i <= 255 - mr; i++)
        {
            for (j = mr; j <= 255 - mr; j++)
            {
                sumx = 0;
                sumy = 0;
                for (p = -mr; p <= mr; p++)
                {
                    for (q = -mr; q <= mr; q++)
                    {
                        sumx += pic[i + p][j + q] * xmask[p + centy][q + centx];
                        sumy += pic[i + p][j + q] * ymask[p + centy][q + centx];
                    }
                }
                xconv[i][j] = sumx;
                yconv[i][j] = sumy;
            }
        }

        // squareroot of squares
        maxival = 0;
        for (i = mr; i < 256 - mr; i++)
        {
            for (j = mr; j < 256 - mr; j++)
            {
                ival[i][j] = sqrt((double)((xconv[i][j] * xconv[i][j]) +
                                           (yconv[i][j] * yconv[i][j])));
                if (ival[i][j] > maxival)
                    maxival = ival[i][j];
            }
        }

        for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
             ival[i][j] = (ival[i][j] / maxival) * 255;
             fprintf(fo1,"%c",(char)((int)(ival[i][j])));

            }
          }
        printf("MAG\n: %f", maxival);

        printf("peaks algorithm \n");
        for (i = mr; i < 256 - mr; i++) {

            for (j = mr; j < 256 - mr; j++) {

                // Set any zero values to a tiny value so we don't divide by zero
                if (xconv[i][j] == 0.0) {
                    xconv[i][j] = 0.00001;
                }

                slope = yconv[i][j]/xconv[i][j];

                if ((slope <= .4142) && (slope > -.4142)) {
                    if ((ival[i][j] > ival[i][j-1]) && (ival[i][j] > ival[i][j+1])) {
                        peaks[i][j] = 255;
                    }
                }
                else if ((slope <= 2.4142) && (slope > .4142)) {
                    if ((ival[i][j] > ival[i-1][j-1]) && ((ival[i][j] > ival[i+1][j+1]))) {
                        peaks[i][j] = 255;
                    }

                }
                else if ((slope <= -.4142) && (slope > -2.4142)) {
                    if ((ival[i][j] > ival[i+1][j-1]) && ((ival[i][j] > ival[i-1][j+1]))) {
                        peaks[i][j] = 255;
                    }
                }
                else {
                    if ((ival[i][j] > ival[i-1][j]) && (ival[i][j] > ival[i+1][j])) {
                        peaks[i][j] = 255;
                    }
                }
            }
        }

        // Part 3
        /*
        printf("start of part3\n");
        for (i = mr; i < 256 - mr; i++)
        {
            for (j = mr; j < 256 - mr; j++)
            {
                // ON = 255 ?
                if (peaks[i][j] == 255) {
                    if (ival[i][j] > high) {
                        peaks[i][j] = 0;
                        finalPic[i][j] = 255;
                    } else if(ival[i][j] < low) {
                        peaks[i][j] = 0;
                        finalPic[i][j] = 0;
                    }
                }

            }
        }
        /*
        int moreToDo = 1;
        while (moreToDo) {
            printf("starting moretodo loop \n");
            moreToDo = 0;
            for (i = mr; i < 256 - mr; i++) {
                for (j = mr; j < 256 - mr; j++) {

                    if (peaks[i][j] == 255) {

                        for (int p = -1; p <= 1; p++) {
                            for (int q = -1; q <= 1; q++) {
                                if (finalPic[i+p][j+q] == 255) {
                                    peaks[i][j] == 0;
                                    finalPic[i][j] == 255;
                                    moreToDo = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        */


    for (i=0;i<256;i++)
    { for (j=0;j<256;j++)
      {  if (ival[i][j] == 255) ival[i][j] = 0;
         else ival[i][j]=255;
         fprintf(fo1,"%c",(char)((int)(ival[i][j])));
      }
    }

    for (i=0;i<256;i++)
    { for (j=0;j<256;j++)
      {  if (peaks[i][j] == 255) peaks[i][j]=0;
         else peaks[i][j]= 255;
         fprintf(fo2,"%c",((peaks[i][j])));
      }
    }
}

