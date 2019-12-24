# Digital Signal Processing Strategies

## :one:  Discrete Hilbert Transformation

## :two:  Evelope

## :three:  Phasw-weighted stacking

### For given discrete signal x[n], its FFT, X[K] is,


$$
\Large{
X[K] = \sum^{N-1}_{n=0}x[n]e^{-\frac{2i\pi nk}{N}} \\
}
$$

$$
\Large{

  }
$$

### Now let Z[K]  be,

$$
\large{
	\begin{eqnarray}
	Z[K] =
		\begin{cases}
			X[K], &k=0 \\
			2X[K], &k=1, 2, 3, \cdots,\frac{N-1}{2} \\
			0, &k=\frac{N}{2}, \frac{N+1}{2},\cdots,N-1
		\end{cases}
	\end{eqnarray}
}
$$

### Using IFFT on Z[K], the imaginary part of IFFT[Z[K]] is h[n],

$$
\large{
	h[n]=\mathscr{I}[\sum_{k=0}^{N-1}Z[K]e^{\frac{2i\pi nk}{N}}]
}
$$

