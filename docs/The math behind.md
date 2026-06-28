#### Mandelbrot set
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

#### Julia set
Julia set isn't that different from mandelbrot set, matter of facts thay are generated using the same function, same method and same variables, but there is a difference:
in mandelbrot set `Z` starts from the origin and `C` is any constant complex number 
but in julia set, `C` is a constant complex number and `Z` is variable 

#### Burning ship
when i started this project, i didn't know what are escape time fractals
but now that i know i can tell you that any fractal that is generated using escape time algorithm (see in [[C++ Implementation]]) is called and escape time fractal
so in future when i implement any other new fractals i would just specify the generating formula.

```Formula
Z(n+1) = (|Re(Z(n))| + i|Im(Z(n))|)^2 + c
```
where as `c` is a constant complex number representing a point in the board.