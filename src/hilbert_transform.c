#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sacio.h"
#include "seis_dsp.h"

int main(int argc, char **argv){
    SACHEAD hd;
    float *d, *s;
    int n = 0;
    d = read_sac(argv[1], &hd);
    n = hd.npts;
    s = (float *) malloc(sizeof(float) * n);
    hil_trans(d, n, s);
    write_sac(argv[2], hd, s);
    free(s);
    return 0;
}
