#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#include "seis_dsp.h"
#include "sacio.h"

#define SIZE 512

/* --------------------------------------------------------------------- */
/* --------------------- Discrete Hilbert Tansform --------------------- */
void hil_trans(float *d, int n, float *s){
    fftw_complex *s_in, *s_out;
    fftw_plan p;
    int nf;
    float f;
    
    // Get integer power of 2.
    f = log((float)n) / log(2.);
    if( fabs(f-(int)f) > 0.)
        f += 1.;
    nf = (int)pow(2, (int)f);
    
    s_in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nf);
    s_out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nf);
    
    // Set values of forward FFT from input signal.
    for(int i = 0; i < nf; i ++) {
        if(i < n)
            s_in[i][0] = *(d+i);
        else
            s_in[i][0] = 0.;
        s_in[i][1] = 0.;
    }

    // Execute FFT.
    p = fftw_plan_dft_1d(nf, s_in, s_out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    // Set complex values of Hilbert Transform to backward FFT.
    for(int i = 1; i < nf; i ++) {
        if(i < (int)nf/2) {
            s_out[i][0] *= 2.; s_out[i][1] *= 2.;
        } else {
            s_out[i][0] = 0.; s_out[i][1] = 0.;
        }
    }

    // Execute IFFT.
    p = fftw_plan_dft_1d(nf, s_out, s_in, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    // Get imaginary part of IFFT: signal after Hilbert Transform.
    for(int i = 0; i < n; i ++)
        *(s+i) = s_in[i][1] / nf;

    fftw_destroy_plan(p);
    fftw_free(s_in); fftw_free(s_out);
}


/* --------------------------------------------------------------------- */
/* ---------------------- Envelope of Signal --------------------------- */
void envelope(float *d, int n, float *s) {
    float *h;
    h = (float *) malloc(sizeof(float) * n);

    // Get signal of Hilbert Transform.
    hil_trans(d, n, h);

    // Calculate envelope of input signals.
    for(int i = 0; i < n; i ++)
    *(s+i) = sqrt(pow(*(d+i), 2) + pow(*(h+i), 2));
    free(h);
}

/* --------------------------------------------------------------------- */
/* ------------------ de-space or de-newline character ----------------- */
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

/* --------------------------------------------------------------------- */
/* --------- Stack SAC files with phase-weighted-stacking method ------- */
void ts_pws(char *fname, char *out_name, int v){
    fftw_complex *c;
        float mod, *s, **rd, *data, **hd, gcarc = 0.;
        FILE *fp;
        int m = 0, n = 0, index = 0;
        char ss[SIZE];
        SACHEAD sachd;

        // Get count of input SAC files.
        if(fp=fopen(fname, "r"))
                while(fgets(ss, SIZE, fp))
                        m += 1;
        else
                fprintf(stderr, "Can not open file %s!!!\n", fname);
        fclose(fp);

        // Read in SAC data.
        if(fp=fopen(fname, "r")){
                while(fgets(ss, SIZE, fp)) {
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