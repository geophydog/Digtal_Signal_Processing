#ifndef _SEIS_DSP_H
#define _SEIS_DSP_H

/* ---------------------------- Get nfft for FFT ----------------------------- */
int pow_next2(int n);

/* --------------------------- Low-pass filter ------------------------------- */
void lowpass_exp(float *x, int n, float *y, float fs, float fc, int order);

/* ---------------------- Butterworth low-pass filter -----------------------  */
void lowpass_butter(float *x, int n, float *y, float fs, float fc, int order);

/* ------------------------ Butterwort high-pass filter ---------------------  */
void highpass_butter(float *x, int n, float *y, float fs, float fc, int order);

/* ---------------------- Butterworth band-pass filter ----------------------  */
void bandpass_butter(float *x, int n, float *y, float fs, float f1, float f2, int order);

/* ------------------------- Discrete Hilbert Transform ---------------------- */
void hil_trans(float *d, int n, float *s);

/* ---------------------------- Envelope of Signal --------------------------- */
void envelope(float *d, int n, float *s);

/* ---------------------- De-space or de-newline character ------------------- */
void fine_str(char *ps);

/* --------------- Stack SAC files with time-scale PWS method ---------------- */
void ts_pws(char *fname, char *out_name, int v);


#endif
