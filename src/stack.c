/*************************************************/
/*FileName: stack.c                              */
/*Author  : xfeng                                */
/*Mail    : geophydogvon@gmail.com               */
/*Inst    : NJU                                  */
/*Time    :Tue 14 Feb 2017 03:05:02 PM CST       */
/*This is c programming language!                */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "sacio.h"


void str_no_void(char *ps){
    char *pt = ps;
    while ( *ps != '\0' ){
        if( *ps != ' ' && *ps != '\n' ){
            *pt++ = *ps;
        }
        ++ps;
    }
    *pt = '\0';
}


int main(int argc, char *argv[]){
    int i = 0, j = 0, size = 256, count = 0, npts;
    float *data, *sum, starttime, endtime;
    char* ss = (char*)malloc(size);
    FILE *fp;
    SACHEAD hd;

    starttime = clock();

    if( argc != 3 ){
        fprintf(stderr,"Usage: stack sacfile.lst outsac.name\n");
        fprintf(stderr,"       Return SAC format file after stacking inputing files.\n");
        fprintf(stderr,"              Similar to \"addf\" in Seismic Analysis Code.\n");
        fprintf(stderr,"       sacfile.lst:  File containing SAC format files;\n");
        fprintf(stderr,"       outsac.name:  Stacking out SAC format file name.\n");
        exit(1);
    }

    if( (fp = fopen(argv[1],"r")) == NULL ){
        fprintf(stderr,"Error reading file: %s\n",argv[1]);
        exit(1);
    }
    while( fgets(ss,size,fp) ){
        str_no_void(ss);
        data = read_sac(ss,&hd);
        if ( count == 0 ) {
            npts = hd.npts;
            sum = (float*) malloc(sizeof(float) * npts);
            for ( i = 0; i < hd.npts; i ++) sum[i] = 0.;
        }
        if ( count >= 1 && hd.npts != npts ) {
                fprintf(stderr, "ATTENTION!!! number of data points is not the same!\n");
                continue;
        }

        if ( !isnan(hd.depmin) || !isnan(hd.depmax) ) {
            for( i = 0; i < hd.npts; i ++ ) sum[i] += data[i];
            count += 1;
        }
        else continue;
    }
    fclose(fp); free(data);
    hd.user0 = count;
    for ( i = 0; i < hd.npts; i ++ ) {
        sum[i] /= (float)count;
    }
    write_sac(argv[2],hd,sum);
    endtime = clock();
    printf("Stacked out file %s costs %f seconds!\n",argv[2],(endtime-starttime)/CLOCKS_PER_SEC);
    return 0;
}
