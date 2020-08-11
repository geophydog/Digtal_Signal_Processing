#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#include "seis_dsp.h"
#include "sacio.h"

#define SIZE 512
#define EPS 1.0e-6
#define PI 3.1415926535

/* -------------------------- Get nfft for FFT ------------------------- */
int pow_next2(int n){
    int f, nf;
    f = (int)(log(n)/log(2.));
    if(abs(pow(2, f)-n) >= EPS )
        f += 1;
    nf = (int) (pow(2, f));
    return nf;
}


/* ----------------------- Filtering on Digital Signals ---------------- */
/* ----------------------- Butterworth low-pass filter ----------------- */
void lowpass_butter(float *x, int n, float *y, float fs, float fc, int order){
    float wc, w, tmp;
    int nfft;
    nfft = pow_next2(n);
    wc = 2 * PI * fc / fs;
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    for(int i = 0; i < nfft; i ++){
        if(i < n)
            in[i][0] = *(x+i);
        else
            in[i][0] = 0.;
        in[i][1] = 0.;
    }
    p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i=0; i < nfft; i ++){
        w = 2 * PI * i / nfft;
        tmp = 1. / (1.+pow(tan(w/2.)/tan(wc/2.), 2.*order));
        out[i][0] *= tmp; out[i][1] *= tmp;
    }
    p = fftw_plan_dft_1d(nfft, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i=0; i < n; i ++)
        *(y+i) = in[i][0] / nfft;
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
}

/* ------------------------ low-pass filter ---------------------------- */
void lowpass_exp(float *x, int n, float *y, float fs, float fc, int order){
    int i, nfft;
    fftw_complex *in, *out;
    fftw_plan p;
    float tmp, f, H;
    nfft = pow_next2(n);
    in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    for(i = 0; i < nfft; i ++){
        if(i < n)
            in[i][0] = *(x+i);
        else
            in[i][0] = 0.;
        in[i][1] = 0.;
    }
    p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(i = 0; i < (nfft/2); i ++){
        f = i*fs / nfft;
        tmp = -pow(f/fc, order);
        H = 2.*exp(tmp) / (1.+exp(tmp));
        out[i][0] *= H;
        out[i][1] *= H;
        out[nfft-1-i][0] = out[i][0];
        out[nfft-1-i][1] = out[i][1];
    }
    p = fftw_plan_dft_1d(nfft, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(i = 0; i < n; i ++)
        *(y+i) = in[i][0]/nfft*2.;
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
}

/* -------------------- Butterworth high-pass filter ------------------- */
void highpass_butter(float *x, int n, float *y, float fs, float fc, int order){
    int nfft;
    float w, tmp, wc;
    nfft = pow_next2(n);
    wc = 2 * PI * fc / fs;
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    for(int i = 0; i < nfft; i ++){
        if(i < n)
            in[i][0] = *(x+i);
        else
            in[i][0] = 0.;
        in[i][1] = 0.;
    }
    p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i=0; i < nfft; i ++){
        w = 2 * PI * i / nfft;
        tmp = 1. / (1.+pow(tan(wc/2.)/tan(w/2.), 2.*order));
        out[i][0] *= tmp; out[i][1] *= tmp;
    }
    p = fftw_plan_dft_1d(nfft, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i=0; i < n; i ++)
        *(y+i) = in[i][0] / nfft;
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);

}

/* ------------------- Butterworth band-pass filter -------------------- */
void bandpass_butter(float *x, int n, float *y, float fs,\
		     float f1, float f2, int order){
    int nfft;
    float w, w1, w2, tmp;
    nfft = pow_next2(n);
    w1 = 2. * PI * f1 / fs;
    w2 = 2. * PI * f2 / fs;
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * nfft);
    for(int i = 0; i < nfft; i ++){
        if(i < n)
            in[i][0] = *(x+i);
        else
            in[i][0] = 0.;
        in[i][1] = 0.;
    }
    p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i=0; i < nfft; i ++){
        w = 2 * PI * i / nfft;
        tmp = 1. / (1.+pow(tan(w1/2.)/tan(w/2.), 2.*order)) /\
                   (1.+pow(tan(w/2.)/tan(w2/2.), 4.*order));
        out[i][0] *= tmp; out[i][1] *= tmp;
    }
    p = fftw_plan_dft_1d(nfft, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for(int i=0; i < n; i ++)
        *(y+i) = in[i][0] / nfft;
    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
}

/* --------------------------------------------------------------------- */
/* --------------------- Discrete Hilbert Tansform --------------------- */
void hil_trans(float *d, int n, float *s){
    fftw_complex *s_in, *s_out;
    fftw_plan p;
    int nf;
    float f;
    
    // Get integer power of 2.
    nf = pow_next2(n);
    
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

