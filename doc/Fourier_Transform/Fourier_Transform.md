### Fourier Transform

#### Xuping Feng

###### $Dec. \ 1^{st}, \ 2019$

***

***

#### 1. Orthogonality of trigonometric functions

##### The trigonometric function system is given by

$$
\large{
\begin{aligned}
&\{0, 1, sinx,cosx,sin2x,cos2x,...,sinnx,cosnx,...,...\}\\
 &\qquad \qquad \qquad \qquad \qquad \qquad \qquad \Downarrow\\
&\{sin0x,cos0x,sinx,cosx,sin2x,cos2x,\cdots,sinnx,cosnx,\cdots\}
\end{aligned}
\tag{1}
}
$$

##### where, $n=0,1,2,\cdots,+\infty$.

##### Here, for given $n,m=0,1,2,\cdots,+\infty$, we calculate the following integrations,

$$
\large{
\begin{aligned}
	\int^{\pi}_{-\pi}sin(nx)cos(mx)dx&=0
\end{aligned} \tag{2}
}
$$

##### $sin(nx)cos(mx)$ is an odd function, its integration between the symmetric interval $[-\pi,\pi]$ is zero.


$$
\large{
\begin{aligned}
	\int_{-\pi}^{\pi}sin(nx)sin(mx)dx
	&=
	\left \{
		\begin{aligned}
			&\int_{-\pi}^{\pi}0dx,n=m=0
			\\
			&\int_{-\pi}^{\pi}\frac{[1-cos(2nx)]}{2}dx,n=m\not=0
			\\
			&\int_{-\pi}^{\pi}\frac{1}{2}[cos(n-m)x-cos(n+m)x]dx,n\not=m\\
		\end{aligned}
	\right.
	\\
	&=
	\left \{
		\begin{aligned}
			&0,n=m=0
			\\
			&\frac{x}{2}|_{-\pi}^{\pi}-\frac{sin(2nx)}{4n}|_{-\pi}^{\pi},n=m\not=0
			\\
			&\frac{1}{4(n-m)}sin(n-m)x|_{-\pi}^{\pi}-\frac{1}{4(n+m)}sin(n+m)x|_{-\pi}^{\pi},n\not=m
		\end{aligned}
	\right.
	\\
	&=
	\left \{
		\begin{aligned}
			&0,n=m=0
			\\
			&\pi,n=m\not=0
			\\
			&0,n\not=m
		\end{aligned}
	\right.
\end{aligned} \tag{3}
}
$$

$$
\large{
\begin{aligned}
	\int_{-\pi}^{\pi}cos(nx)cos(mx)dx
	&=
	\left \{
		\begin{aligned}
			&\int_{-\pi}^{\pi}1dx,n=m=0
			\\
			&\int_{-\pi}^{\pi}\frac{1+cos(2nx)}{2}dx,n=m\not=0
			\\
			&\int_{-\pi}^{\pi}\frac{1}{2}[cos(n-m)x+cos(n+m)x]dx,n\not=m
		\end{aligned}
	\right.
	\\
	&=
	\left \{
		\begin{aligned}
			&2\pi,n=m=0
			\\
			&\pi,n=m\not=0
			\\
			&\frac{1}{4(n-m)}sin(n-m)x|_{-\pi}^{\pi}+\frac{1}{4(n+m)}sin(n+m)x|_{-\pi}^{\pi},n\not=m
		\end{aligned}
	\right.
	\\
	&=
	\left \{
		\begin{aligned}
			&2\pi,n=m=0
			\\
			&\pi,n=m\not=0
			\\
			&0,n\not=m
		\end{aligned}
	\right.
\end{aligned} \tag{4}
}
$$

##### We proved the orthogonality of trigonometric functions.

***

#### 2. Fourier Series

##### We assume that a function $f(x)$ has a period $2\pi$, namely  $f(x)=f(x+2\pi)$. If $f(x)$ satisfies $Dirichlet$ condition,

$$
\large{
	\boxed{1. f(x) \text{ has finite discontinuity points of the first kind in a period;}
		\\
		2. f(x) \text{ has finite extreme points in a period.}
	}
}
$$



##### $f(x)$ can be expanded as $Fourier$ series.

$$
\large{
	f(x)=\sum_{n=0}^{+\infty}[a_ncos(nx)+b_nsin(nx)] \tag{5}
}
$$

##### Here, we usually write $eq. (5)$ as

$$
\large{
f(x)=\frac{a_0}{2}+\sum_{n=1}^{+\infty}[a_ncos(nx)+b_nsin(nx)] \tag{6}
}
$$

##### where, $\frac{a_0}{2}=[a_0cos(0x)+b_0sin(0x)]$.

$$
\Large{
	\boxed{Finding \ a_0}
}
$$



##### We integrate $f(x)$ on $[-\pi, \pi]$,

$$
\large{
	\begin{aligned}
		\int_{-\pi}^{\pi}f(x)dx&=\int_{-\pi}^{\pi}\frac{a_0}{2}dx+\sum_{n=1}^{+\infty}[a_n\int_{-\pi}^{\pi}cos(0n)cos(nx)dx+b_n\int_{-\pi}^{\pi}cos(ox)sin(nx)dx]\\
		&=\frac{a_0}{2}\int_{-\pi}^{\pi}dx+\sum_{n=1}^{+\infty}[a_n\cdot 0+b_n\cdot 0]\\
		&=a_0\pi
	\end{aligned} \tag{7}
}
$$

##### So

$$
\large{
	a_0=\frac{1}{\pi}\int_{-\pi}^{\pi}f(x)dx \tag{8}
}
$$

$$
\large{}
$$

$$
\Large{
	\boxed{Finding \ a_n}
}
$$

##### We integrate $f(x)cos(mx)$ on $[-\pi,\pi]$,

$$
\large{
	\begin{aligned}
		\int_{-\pi}^{\pi}f(x)cos(mx)dx&=\int_{-\pi}^{\pi}\frac{a_0}{2}cos(mx)dx+\int_{-\pi}^{\pi}\sum_{n=1}^{\infty}a_ncos(nx)cos(mx)dx\\
		& \qquad +\int_{-\pi}^{\pi}\sum_{n=1}^{+\infty}b_nsin(nx)cos(mx)dx\\
		&=\frac{a_0}{2}\int_{-\pi}^{\pi}cos(0x)cos(mx)dx+\sum_{n=1}^{+\infty}\int_{-\pi}^{\pi}a_ncos(nx)cos(mx)dx\\
		&\qquad+\sum_{n=1}^{+\infty}\int_{-\pi}^{\pi}b_nsin(nx)cos(mx)dx\\
		&=0+[\int_{-\pi}^{\pi}a_1cos(1x)cos(mx)dx+\int_{-\pi}^{\pi}a_2cos(2x)cos(mx)dx\\
		& \qquad +...+\int_{-\pi}^{\pi}a_ncos(1x)cos(mx)dx]+\sum_{n=1}^{+\infty}0\\
		&=\int_{-\pi}^{\pi}a_ncos(nx)cos(nx)dx \ (n=m)\\
		&=a_n\pi
	\end{aligned} \tag{9}
}
$$

##### We have

$$
\large{
	a_n=\frac{1}{\pi}\int_{-\pi}^{\pi}f(x)cos(nx)dx \tag{10}
}
$$

$$
\Large{
	\boxed{Finding \ b_n}
}
$$



##### Similarly, we integrate $f(x)sin(mx)$ on $[-\pi,\pi]$

$$
\large{
	\begin{aligned}
		\int_{-\pi}^{\pi}f(x)sin(mx)dx&=\int_{-\pi}^{\pi}\frac{a_0}{2}sin(mx)dx+\int_{-\pi}^{\pi}\sum_{n=1}^{+\infty}a_ncos(nx)sin(mx)dx\\
		&\qquad +\int_{-\pi}^{\pi}\sum_{n=1}^{\infty}b_nsin(nx)sin(mx)dx\\
		&=\frac{a_0}{2}\int_{-\pi}^{\pi}cos(0x)sin(mx)dx+\sum_{n=1}^{+\infty}\int_{-\pi}^{\pi}a_ncos(nx)sin(mx)dx\\
		&\qquad+\sum_{n=1}^{+\infty}\int_{-\pi}^{\pi}b_nsin(nx)sin(mx)dx\\
		&=0+\sum_{n=1}^{+\infty}0+[b_1\int_{-\pi}^{\pi}sin(1x)sin(mx)dx\\
		&\qquad+b_2\int_{-\pi}^{\pi}sin(2x)sin(mx)dx+\cdots+b_n\int_{-\pi}^{\pi}sin(nx)sin(mx)dx]\\
        &=\int_{-\pi}^{\pi}sin(nx)sin(nx)dx \ (n=m)\\
		&=b_n\pi
	\end{aligned} \tag{11}
}
$$

##### So we get

$$
\large{
	b_n=\frac{1}{\pi}\int_{-\pi}^{\pi}f(x)sin(nx)dx \tag{12}
}
$$

***

#### 3. Series expansion of function with a period of $2L$

##### We have function $f(t)$, and $f(t)=f(t+2L)$. $2L$ is the minimum of positive period of $f(t)$.

##### Here, we let

$$
\large{
	x=\frac{\pi}{L}t \tag{13}
}
$$

##### And

$$
\large{
	\begin{aligned}
		f(t)&=f(\frac{L}{\pi}x)\\
		&=g(x)
	\end{aligned} \tag{14}
}
$$

##### The Fourier series of $g(x)$ is given by

$$
\large{
	\left \{
		\begin{aligned}
			&g(x)=\frac{a_0}{2}+\sum_{n=1}^{+\infty}[a_ncos(nx)+b_nsin(nx)]\\
			&a_0=\int_{-\pi}^{\pi}f(x)dx\\
			&a_n=\int_{-\pi}^{\pi}cos(nx)dx\\
			&b_n=\int_{-\pi}^{\pi}sin(nx)dx
		\end{aligned}
	\right. \tag{15}
}
$$

##### We change $x$ to $t$ using $eq. (13)$ and we have

$$
\large{
	\left\{
		\begin{aligned}
			&cos(nx)=cos(n\frac{\pi}{L}t)\\
			&sin(nx)=sin(n\frac{\pi}{L}t)\\
			&\frac{1}{\pi}\int_{-\pi}^{\pi}dx=\frac{1}{\pi}\int_{-L}^{L}d\frac{\pi}{L}t=\frac{1}{L}\int_{-L}^{L}dt\\
			&\pi\rightarrow L\\
			&-\pi\rightarrow -L
		\end{aligned} \tag{16}
	\right.
}
$$

##### Using $eq. (16)$, the Fourier series of $f(t)$ can be described as

$$
\large{
	\left \{
		\begin{aligned}
			&f(t)=\frac{a0}{2}+\sum_{n=1}^{+\infty}[a_ncos(n\frac{\pi}{L}t)+b_nsin(n\frac{\pi}{L}t)\\
			&a_0=\frac{1}{L}\int_{-L}^{L}f(t)dt\\
			&a_n=\frac{1}{L}\int_{-L}^{L}f(t)cos(n\frac{\pi}{L}t)dt\\
			&b_n=\frac{1}{L}\int_{-L}^{L}f(t)sin(n\frac{\pi}{L}t)dt
		\end{aligned} \tag{17}
	\right.
}
$$

##### Alternatively, we let $2L=T$, and we have

$$
\large{
	\left \{
		\begin{aligned}
			&f(t)=\frac{a0}{2}+\sum_{n=1}^{+\infty}[a_ncos(n\frac{2\pi}{T}t)+b_nsin(n\frac{2\pi}{T}t)\\
			&a_0=\frac{2}{T}\int_{0}^{T}f(t)dt\\
			&a_n=\frac{2}{T}\int_{0}^{T}f(t)cos(n\frac{2\pi}{T}t)dt\\
			&b_n=\frac{2}{T}\int_{0}^{T}f(t)sin(n\frac{2\pi}{T}t)dt
		\end{aligned} \tag{18}
	\right.
}
$$

##### Let $\omega=\frac{2\pi}{T}$,  and we change $eq. (18)$ to

$$
\large{
	\left \{
		\begin{aligned}
			&f(t)=\frac{a0}{2}+\sum_{n=1}^{+\infty}[a_ncos(n\omega t)+b_nsin(n\omega t)\\
			&a_0=\frac{2}{T}\int_{0}^{T}f(t)dt\\
			&a_n=\frac{2}{T}\int_{0}^{T}f(t)cos(n\omega t)dt\\
			&b_n=\frac{2}{T}\int_{0}^{T}f(t)sin(n\omega t)dt
		\end{aligned} \tag{19}
	\right.
}
$$



***

#### 4. Complex number form of Fourier series

##### The $Euler's$ formula is given by

$$
\large{
	\left \{
		\begin{aligned}
			&e^{i\theta}=cos\theta+isin\theta\\
			&cos\theta=\frac{e^{i\theta}+e^{-i\theta}}{2}\\
			&sin\theta=-i\frac{e^{i\theta}-e^{-i\theta}}{2}
		\end{aligned} \tag{20}
	\right.
}
$$

##### Here, we constitute $Euler's$ formula into $eq.(19)$ and we get

$$
\large{
	\begin{aligned}
		f(t)&=\frac{a_0}{2}+\sum_{n=1}^{+\infty}[a_n\frac{e^{in\omega t}+e^{-in\omega t}}{2}-ib_n\frac{e^{in\omega t}-e^{-in\omega t}}{2}]\\
			&=\frac{a_0}{2}+\sum_{n=1}^{+\infty}\frac{a_n-ib_n}{2}e^{in\omega t}+\sum_{n=1}^{+\infty}\frac{a_n+ib_n}{2}e^{-in\omega t}\\
			&=\frac{a_0}{2}+\sum_{n=1}^{+\infty}\frac{a_n-ib_n}{2}e^{in\omega t}+\sum_{n=-\infty}^{-1}\frac{a_{-n}+ib_{-n}}{2}e^{in\omega t}\\
			&=\sum_{n=0}^{0}\frac{a_0}{2}e^{in\omega t}+\sum_{n=1}^{+\infty}\frac{a_n-ib_n}{2}e^{in\omega t}+\sum_{n=-\infty}^{-1}\frac{a_{-n}+ib_{-n}}{2}e^{in\omega t}\\
			&=\sum_{-\infty}^{+\infty}c_ne^{in\omega t}
	\end{aligned} \tag{21}
	
}
$$

##### where

$$
\large{
	c_n=
	\left \{
		\begin{aligned}
			&\frac{a_0}{2},n=0\\
			&\frac{a_n-ib_n}{2},n=1,2,3,\cdots,+\infty\\
			&\frac{a_{-n}+ib_{-n}}{2},n=-1,-2,-3,...,-\infty
		\end{aligned}
	\right. \tag{22}
}
$$

##### Use $eq.(19)$  and the coefficient $c_n$ is given by

$$
\large{
	c_n=
	\left \{
		\begin{aligned}
			&\frac{a_0}{2}=\frac{1}{2}\frac{2}{T}\int_{0}^{T}f(t)dt=\frac{1}{T}\int_{0}^{T}f(t)dt=\frac{1}{T}\int_{0}^{T}f(t)e^{-in\omega t}dt \quad (n=0)
			\\
			&
			\begin{aligned}
				\frac{a_n-ib_n}{2}&=\frac{1}{2}\frac{2}{T}\int_{0}^{T}f(t)cos(n\omega t)dt-\frac{i}{2}\frac{2}{T}\int_{0}^{T}f(t)sin(n\omega t)dt\\
				&=\frac{1}{T}\int_{0}^{T}f(t)[cos(n\omega t)-isin(n\omega t)]dt\\
				&=\frac{1}{T}\int_{0}^{T}f(t)e^{-in\omega t}dt \quad (n=1,2,3,\cdots,+\infty)
			\end{aligned}
			\\
			&
			\begin{aligned}
				\frac{a_{-n}+ib_{-n}}{2}&=\frac{1}{2}\frac{2}{T}\int_{0}^{T}f(t)cos(-n\omega t)dt+\frac{i}{2}\frac{2}{T}\int_{0}^{T}f(t)sin(-n\omega t)dt\\
				&=\frac{1}{T}\int_{0}^{T}f(t)[cos(n\omega t)-isin(n\omega t)]dt\\
				&=\frac{1}{T}\int_{0}^{T}f(t)e^{-in\omega t}dt \quad (n=-1,-2,-3,\cdots,-\infty)
			\end{aligned}
		\end{aligned} 
	\right. \tag{23}
}
$$

##### So

$$
\large{
	c_n=\frac{1}{T}\int_{0}^{T}f(t)e^{-in\omega t}dt \tag{24}
}
$$

##### Let $\omega_0=\frac{2\pi}{T}$,  here we call $\omega_0$ basic frequency, and we have

$$
\large{
	\left \{
		\begin{aligned}
			&
			\begin{aligned}
				f_T(t)&=\sum_{n=-\infty}^{\infty}c_ne^{in\omega_0 t}\\
					  &=[\cdots+c_{-n}e^{i(-n)\omega_0 t}\\
					  &\qquad +\cdots+c_{-1}e^{i(-1)\omega_0 t}+c_0e^{i0\omega_0 t}+c_{1}e^{i(1)\omega_0 t}\\
					  &\qquad+\cdots+c_{n}e^{i(n)\omega_0 t}+\cdots]
			\end{aligned}
			\\
			&c_n=\frac{1}{T}\int_{\frac{-T}{2}}^{\frac{T}{2}}f_T(t)e^{-in\omega_0 t}dt
		\end{aligned}
	\right. \tag{25}
}
$$

##### If the function $f(t)$ is non-period, namely, $T\to +\infty$ and $f(t)=\lim\limits_{T\to+\infty}f_T(t)$, then we have

$$
\large{
	\begin{aligned}
		\Delta \omega&=(n+1)\omega_0-n\omega_0\\
		&=\omega_0\\
		&=\frac{2\pi}{T}
	\end{aligned} \tag{26}
}
$$

##### and let

$$
\large{
	\begin{aligned}
		\omega&=n\omega_0\\
				&=n\Delta \omega
		\end{aligned} \tag{27}
}
$$


$$
\large{
	\begin{aligned}
		c_n&=\frac{1}{T}\int_{-\infty}^{\infty}f(t)e^{-in\Delta \omega t}dt\\
		   &=\frac{\Delta \omega}{2\pi}\int_{-\infty}^{\infty}f(t)e^{-in\Delta \omega t}dt\\
		   &=\frac{\Delta \omega}{2\pi}\int_{-\infty}^{\infty}f(t)e^{-i\omega t}dt
    \end{aligned} \tag{28}
}
$$

##### Constitute $eq.(28)$ to $f(t)=\sum_{n=-\infty}^{\infty}c_ne^{in\Delta \omega t}$, and $f(t)$ will be

$$
\large{
	\begin{aligned}
		f(t)&=\sum_{n=-\infty}^{\infty}\frac{\Delta \omega}{2\pi}\int_{-\infty}^{\infty}f(t)e^{i\omega t}dte^{-i\omega t}\\
        &=\frac{1}{2\pi}\sum_{n=-\infty}^{\infty}[\int_{-\infty}^{\infty}f(t)e^{-i\omega t}dt]e^{i\omega t}\Delta \omega\\
        &=\frac{1}{2\pi}\int_{-\infty}^{\infty}\boxed{\int_{-\infty}^{\infty}f(t)e^{-i\omega t}dt}e^{i\omega t}d\omega
	\end{aligned} \tag{29}
}
$$

$$
\large{
	\boxed{
		NOTE\\
		\text{The definition of integration is described by}\\
		\int h(x)dx=\lim\limits_{\Delta x \to 0}\sum h(x)\Delta x\\
		So \ \sum_{-\infty}^{\infty}\boxed{\cdots}e^{i\omega t}\Delta \omega=\int_{-\infty}^{\infty}\boxed{\cdots}e^{i\omega d\omega} \text{described in eq.(29). }
	}
}
$$

##### Here, we define $F(\omega)=\mathscr{F}[f(t)]$ as the $Fourier \ Transform$ of function $f(t)$, and $F(\omega)$ is closed by black box in $eq(29)$. 

##### Finally, we derive $\mathscr{F}[f(t)]$ and $\mathscr{F}^{-1}[F(\omega)]$

$$
\large{
	\left \{
		\begin{aligned}
			&
			\begin{aligned}
				F(\omega)&=\mathscr{F}[f(t)]\\
				&=\int_{-\infty}^{\infty}f(t)e^{-i\omega t}dt
			\end{aligned}
			\\
			&
			\begin{aligned}
				f(t)&=\mathscr{F}^{-1}[F(\omega)]\\
				&=\frac{1}{2\pi}\int_{-\infty}^{\infty}F(\omega)e^{i\omega t}d\omega
			\end{aligned}
		\end{aligned}
	\right. \tag{30}
}
$$

##### where, $f(t)=\frac{1}{2\pi}\int_{-\infty}^{\infty}F(\omega)e^{i\omega t}d\omega$ is the inversed $Fourier \  Transform$ of $F(\omega)$.

***

#### 5. Bibliography

$$
\boxed{
	\text{ DR_CAN (2018). Fourier Transform. Retrieved} \ Dec. \ 1^{st}, 2019, \\
	\text{from https://www.bilibili.com/video/av34364399?from=search&seid=2646408214755087213}
}
$$

