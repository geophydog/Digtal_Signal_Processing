#include <stdio.h>
#include <stdlib.h>
#include "sacio.h"
#include "seis_dsp.h"

int main(int argc, char *argv[]){
    if(argc != 5){
        fprintf(stderr, "Usage: lowp sacin sacout fc order\n");
        exit(1);
    }
    float *x, *y, fc, fs;
    int order;
    SACHEAD hd;
    fc = atof(argv[3]); order = atoi(argv[4]);
    x = read_sac(argv[1], &hd);
    y = (float *) malloc(sizeof(float) * hd.npts);
    fs = 1. / hd.delta;
    lp(x, hd.npts, y, fs, fc, order);
    write_sac(argv[2], hd, y);
    free(x); free(y);
    return 0;
}
