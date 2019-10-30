#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#include "sacio.h"
#include "seis_dsp.h"

void fine_str(char *ps){
    char *pt = ps;
	    while ( *ps != '\0' ){
			if( *ps != ' ' && *ps != '\n' ){
				*pt++ = *ps;
			}
			++ps;
		}
		*pt = '\0';
	}


void ts_pws(char *fname, char *out_name, int v){
    fftw_complex *c;
	float mod, *s, **rd, *data, **hd, gcarc = 0.;
	FILE *fp;
	int m = 0, n = 0, index = 0;
	v = 2;
	char ss[128];
	SACHEAD sachd;

	// Get count of input SAC files.
	if(fp=fopen(fname, "r"))
		while(fgets(ss, 128, fp))
			m += 1;
	else
		fprintf(stderr, "Can not open file %s!!!\n", fname);
	fclose(fp);

	// Read in SAC data.
	if(fp=fopen(fname, "r")){
		while(fgets(ss, 128, fp)) {
			fine_str(ss);
			data = read_sac(ss, &sachd);

			// Calculate average distance.
			gcarc += sachd.gcarc / m;
			if(index < 1) {
				n = sachd.npts;
				s = (float *) malloc(sizeof(float) * n);
				c = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * n);
				rd = (float **) malloc(sizeof(float *) * m);
				hd = (float **) malloc(sizeof(float *) * m);
				for(int i = 0; i < m; i ++) {
					rd[i] = (float *) malloc(sizeof(float) * n);
					hd[i] = (float *) malloc(sizeof(float) * n);
				}
			}
			// Get original signal.
			for(int i = 0; i < n; i ++)
				rd[index][i] = *(data+i);
			// Get signal after hilber transform.
			hil_trans(data, n, hd[index]);
			index += 1;
		}
	} else
		fprintf(stderr, "Can not open file %s!!!\n", fname);
	fclose(fp);

	

	//printf("m: %d  n: %d  v: %d\n", m, n, v);
    for(int i = 0; i < n; i ++) {
		c[i][0] = 0.; c[i][1] = 0.;
		for(int j = 0; j < m; j ++){
			mod = sqrt( pow(rd[j][i], 2.) + pow(hd[j][i], 2.) );
			c[i][0] += ( rd[j][i] / mod / m ); 
			c[i][1] += ( hd[j][i] / mod / m );
		}
		for(int j = 0; j < m; j ++)
			*(s+i) += (rd[j][i] * pow(pow(c[i][0], 2.)+pow(c[i][1], 2.), v/2.) / m);
	}
	//printf("%f %f %f\n", s[0], s[1], s[2]);
	write_sac(out_name, sachd, s);

	// Release dynamice memories.
	for(int i = 0; i < m; i ++) {
		free(rd[i]);
		free(hd[i]);
	}
	free(rd); free(hd);
	free(s); free(data);
	fftw_free(c);
}


int main(int argc, char **argv){
	if(argc != 4){
		fprintf(stderr, "Usage: time_scale_pws sacfile outfile npower\n");
		exit(1);
	}
	ts_pws(argv[1], argv[2], atoi(argv[3]));
	return 0;
}
