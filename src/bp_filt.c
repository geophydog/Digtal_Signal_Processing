#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include "sacio.h"

void bandpass(char *sacin, char *sacout, float f1, float f2);




void bandpass(char *sacin, char *sacout, float f1, float f2){
	SACHEAD hd;
	float *data, scale, f11, f22, fs;
	int n1, n2, n;
	fftw_complex *in, *out;
	fftw_plan p;

	f11 =f1; f22 = f2;
	while(f11 < 1.)
		f11 *= 10.;
	while(f22 < 1.)
		f22 *= 10.;
	scale = sqrt(f11+f22);

	data = read_sac(sacin, &hd);
	n = hd.npts;
	fs = 1 / hd.delta;
	n1 = (int)(f1/fs*n);
	n2 = (int)(f2/fs*n);
	in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * n);
	out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * n);
	for(int i = 0; i < n; i ++ ){
		in[i][0] = *(data+i); in[i][1] = 0.;
	}
	p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	for(int i = 0; i < n1; i ++) {
		out[i][0] = 0.; out[i][1] = 0.;
	}
	for(int i = n2; i < n; i ++){
		out[i][0] = 0.; out[i][1] = 0.;
	}
	p = fftw_plan_dft_1d(n, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_destroy_plan(p);
	for(int i = 0; i < n; i ++)
		*(data+i) = in[i][0] * scale;
	write_sac(sacout, hd, data);
	fftw_free(in); fftw_free(out); free(data);
}

int main(int argc, char *argv[]){
	if(argc != 5){
		fprintf(stderr, "Usage: bp_filt sacin sacout f1 f2\n");
		exit(1);
	}
	bandpass(argv[1], argv[2], atof(argv[3]), atof(argv[4]));

	return 0;
}
