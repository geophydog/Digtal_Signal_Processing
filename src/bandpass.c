#include <stdio.h>
#include <stdlib.h>
#include "sacio.h"
#include "seis_dsp.h"

int main(int argc, char *argv[]){
    if(argc != 6){
        fprintf(stderr, "Usage: bandpass sacin sacout f1 f2 order\n");
        exit(1);
    }
    float *x, *y, f1, f2, fs;
    int order;
    SACHEAD hd;
    f1 = atof(argv[3]); f2 = atof(argv[4]);
    order = atoi(argv[5]);
    x = read_sac(argv[1], &hd);
    y = (float *) malloc(sizeof(float) * hd.npts);
    fs = 1. / hd.delta;
    bandpass_butter(x, hd.npts, y, fs, f1, f2, order);
    write_sac(argv[2], hd, y);
    free(x); free(y);
    return 0;
}
