#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int masky[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
double ival[256][256], maxival;

void applyThreshold(double threshold, char *filename);

int main(argc, argv)
int argc;
char **argv;
{
    int i, j, p, q, mr, sum1, sum2;
    FILE *fo1, *fo2, *fo3, *fp1, *fopen();
    char *foobar;
    char pic1[100], pic2[100], pic3[100], pic4[100];

    printf("Enter source file name:\n");
    scanf("%s", pic1);
    foobar = pic1;

    if((fp1=fopen(pic1,"r"))==NULL) printf("can't open input file\n");
    printf("found %s \n", pic1);
    fp1 = fopen(foobar, "rb");


    // Magnitude
    printf("Enter magnitude output file name:\n");
    scanf("%s", pic2);
    foobar = pic2;
    fo1 = fopen(foobar, "wb");

    // Hi Threshold
    printf("Enter Hi Threshold output file name:\n");
    scanf("%s", pic3);
    foobar = pic3;
    fo2 = fopen(foobar, "wb");

    // Lo Threshold
    printf("Enter Lo Threshold output file name:\n");
    scanf("%s", pic4);
    foobar = pic4;
    fo3 = fopen(foobar, "wb");

    fprintf(fo1, "P5\n256 256\n255\n");
    fprintf(fo2, "P5\n256 256\n255\n");
    fprintf(fo3, "P5\n256 256\n255\n");

    for (i = 0; i < 256; i++)
    {
        for (j = 0; j < 256; j++)
        {
            pic[i][j] = getc(fp1);
            pic[i][j] &= 0377;
        }
    }

    mr = 1;
    for (i = mr; i < 256 - mr; i++)
    {
        for (j = mr; j < 256 - mr; j++)
        {
            sum1 = 0;
            sum2 = 0;
            for (p = -mr; p <= mr; p++)
            {
                for (q = -mr; q <= mr; q++)
                {
                    sum1 += pic[i + p][j + q] * maskx[p + mr][q + mr];
                    sum2 += pic[i + p][j + q] * masky[p + mr][q + mr];
                }
            }
            outpicx[i][j] = sum1;
            outpicy[i][j] = sum2;
        }
    }

    maxival = 0;
    for (i = mr; i < 256 - mr; i++)
    {
        for (j = mr; j < 256 - mr; j++)
        {
            ival[i][j] = sqrt((double)((outpicx[i][j] * outpicx[i][j]) +
                                       (outpicy[i][j] * outpicy[i][j])));
            if (ival[i][j] > maxival)
                maxival = ival[i][j];
        }
    }

    //applyThreshold(255, fo1); // Magnitude image

    printf("NEw style");
    for (i=0;i<256;i++)
      { for (j=0;j<256;j++)
        {
         ival[i][j] = (ival[i][j] / maxival) * 255;
         fprintf(fo1,"%c",(char)((int)(ival[i][j])));

        }
      }
    applyThreshold(50, fo2); // Hi Threshold
    applyThreshold(10, fo3);  // Lo Threshold

    fclose(fo1);
    fclose(fo2);
    fclose(fo3);
}

void applyThreshold(double threshold, char *filename)
{
    int i, j;
    for (i = 0; i < 256; i++)
    {
        for (j = 0; j < 256; j++)
        {
            ival[i][j] = (ival[i][j] / maxival) * 255;
            if (ival[i][j] > threshold)
                fprintf(filename, "%c", (char)255);
            else
                fprintf(filename, "%c", (char)0);
        }
    }
}


