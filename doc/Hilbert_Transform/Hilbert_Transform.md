#### For given discrete signal $x[n]$, its FFT, $X[k]$ is given by


$$
\Large{
	X[k] = \sum^{N-1}_{n=0}x[n]e^{-\frac{2i\pi nk}{N}} \tag{1}
}
$$

$$
\Large{

  }
$$

#### Now let the $Fourier$ spectrum of the $Hilbert$ transform of $x[n]$ is $Z[k]$,

$$
\Large{
	\begin{eqnarray}
	Z[k] =
		\begin{cases}
			X[k], &k=0 \\
			2X[k], &k=1, 2, 3, \cdots,\frac{N}{2}-1 \\
			0, &k=\frac{N}{2}, \frac{N+1}{2},\cdots,N-1
		\end{cases}
	\end{eqnarray} \tag{2}
}
$$

#### Doing $IFFT$ on $ Z[k] $, the imaginary part of $IFFT[Z[k]]$ is the $Hilbert$ transform of $x[n]$, $h[n]$,

$$
\Large{
	h[n]=\mathscr{I}[\sum_{k=0}^{N-1}Z[k]e^{\frac{2i\pi nk}{N}}] \tag{3}
}
$$

