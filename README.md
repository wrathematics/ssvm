# ssvm

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/ssvm.png)](https://travis-ci.org/wrathematics/ssvm)
* **License:** [![License](http://img.shields.io/badge/license-BSD%202--Clause-orange.svg?style=flat)](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


**ssvm** is a simple 2-class linear  SVM implementation using the Pegasos algorithm, written on my day off for fun.  The design philosophy for the project is:

1. Use a clean C interface to handle the heavy lifting.  Bloated idiomatic C++ interfaces look stupid and often wreck performance.
2. The implementation is reasonably efficient.  One could work a bit harder to make this faster, but I think all of the "easy" gains have already been achieved.
3. The R interface doesn't use formulas.  Oh my god do not get me started on fucking formulas.  If I could ban one thing from R, it would be formulas and I wouldn't even have to stop and think about it.
4. The secret ingredient is love.


## Installation

<!--To install the R package, run:-->

<!--```r-->
<!--install.package("ssvm")-->
<!-- ``` -->

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
### Pick your preference
devtools::install_github("wrathematics/ssvm")
ghit::install_github("wrathematics/ssvm")
remotes::install_github("wrathematics/ssvm")
```


## Package Use


```r
library(ssvm)

y <- recode(iris$Species == "setosa")
x <- as.matrix(iris[, -5])

set.seed(1234)
mdl <- pegasos(x, y)
mdl
## SVM model (Method=Pegasos, Iterations=1e+05)
##    Intercept Sepal.Length  Sepal.Width Petal.Length  Petal.Width 
##   -0.08139028  -0.12708726  -0.45953076   0.68090852   0.33553786  

mdl <- pegasos(x, y, intercept=FALSE)
mdl
## SVM model (Method=Pegasos, Iterations=1e+05)
## Sepal.Length  Sepal.Width Petal.Length  Petal.Width 
##   -0.1358138   -0.4659208    0.6824105    0.3382079 

p <- predict(mdl, x)
sum(which(p != y))
## 0
```
