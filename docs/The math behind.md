I believe mandelbrot set is one of the easiest sets to generate mathematically 

here's how it works

suppose you have a complex number like `c` 
this recursive equation is what leads us into mandelbrot set :
```Function
Z(n+1) = (Z(n))^2 + c
```
The starting point is 0 :
```
Z(0) = 0 + 0i
```
we start a random `c` on the complex plain
now `c` is inside mandelbrot set if `|Z(n)|` converges as `n -> ∞`
