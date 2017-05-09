library(ssvm)

y <- recode(iris$Species == "setosa")
x <- as.matrix(iris[, -5])

set.seed(1234)
truth <-
structure(c(-0.138687298992951, -0.468900779129492, 0.682738598681026, 
0.338677882941678), .Names = c("Sepal.Length", "Sepal.Width", 
"Petal.Length", "Petal.Width"))
test <- pegasos(x, y, intercept=FALSE)$w
stopifnot(all.equal(test, truth))


truth <-
structure(c(-0.0798928770978866, -0.124892553609644, -0.457169655873265, 
0.681240396757289, 0.335477893119601), .Names = c("Intercept", 
"Sepal.Length", "Sepal.Width", "Petal.Length", "Petal.Width"))
test <- pegasos(x, y, intercept=TRUE)$w
stopifnot(all.equal(test, truth))
