#ifndef _SEIS_DSP_H
#define _SEIS_DSP_H

/* ------------------ Discrete Hilbert Transform ---------------- */
void hil_trans(float *d, int n, float *s);

/* --------------------- Envelope of Signal --------------------- */
void envelope(float *d, int n, float *s);

/* -------------- De-space or de-newline character -------------- */
void fine_str(char *ps);

/* -------- Stack SAC files with time-scale PWS method ---------- */
void ts_pws(char *fname, char *out_name, int v);


#endif
