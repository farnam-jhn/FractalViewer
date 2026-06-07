In [The math behind](obsidian://open?vault=Mandelbrot%20Exploler&file=The%20math%20behind) we saw we need to check if a recursive function converges as its arguments moves to infinity 
however we don't have infinity in Computer world
as we don't have infinite resources

### Approach
since we have limited resources, there is a common approach to check if a complex constant like `c` is in the set or not:
we can use a loop that calculates `Z(n+1)` from `Z(n)` 
then we can check two things :
1. is `Z` getting bigger and bigger 
2. how many times we irritated the loop

#### Why number one matters :

to check the first thing we can choose a number as our bounding magnitude.
this is useful because `Z` starts from `(0,0)` and if it grows more than a curtain magnitude (breaks a limited bound) then it definitely gets unbounded and it can never shrink and get lower than that magnitude.
this is because when `|Z| >= magnitude` we have : `|Z|^2 >= magnitude * |Z|`.

#### Why number two matters :

iterations count matters because if a curtain `C` gives us divergence the computer would never know this.
this means the divergence checker function actually reaches a `C` that makes the `Z(n+1) = (Z(n))^2 + c` sequence divergence it just calculates more and more `Z`s. since we can't reach infinity (where we can make sure C makes the sequence divergent) we can limit the loop so after a curtain amount of iterations it supposes C makes the sequence divergent. 
#### Simple optimization 

instead of comparing the actual magnitude to a number we can compare norm of the `Z` to square of the magnitude:
```Math
Z = a + bi
|Z| = sqrt(a^2 + b^2)
norm(Z) = Z.conj(Z) = |Z|^2 = a^2 + b^2
```
using this approach we skipped a square root. this would make the calculations faster

this approach is called escape-time algorithm
see its [wikipedia page](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set)
### Using iterations

to make the visualization colorful we can use iterations count 
under the same wikipedia page there is an Histogram coloring algorithm that i implemented in this program
here's how it works:
you make a color palette and assign a color to each iteration count
this creates a problem: if iteration amount is huge then there would be a lot of colors to add to palette 
there are two approaches to fix this problem
1. Assigning multiple iteration to a singular color
2. Using **Lerp**

first approach makes the image look tasteless
for the second approach we generate exactly one color for each iteration amount 

### Lerp

Linear interpolation also known as Lerp is a method in mathematics to make a discrete functions continuous
you pick two points and using a formula get the point in between 
we use this for two colors and we generate a point between R, G, B and Alpha to create a new color
for more info : [Lerp Wikipedia page](https://en.wikipedia.org/wiki/Linear_interpolation)

### Multi-threading

to make the program faster i used multi-threading 
multi-threading works by simply splitting image into different parts 