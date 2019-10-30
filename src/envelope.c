#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sacio.h"
#include "seis_dsp.h"

int main(int argc, char **argv){
    float *d, *e;
    SACHEAD hd;

    d = read_sac(argv[1], &hd);
    e = (float *) malloc(sizeof(float) * hd.npts);
    envelope(d, hd.npts, e);

    write_sac(argv[2], hd, e);

    free(e);

    return 0;

}
