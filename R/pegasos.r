#' pegasos
#' 
#' Pegasos SVM solver.
#' 
#' @description
#' If \code{intercept=TRUE}, the data is not literally modified to include a
#' column of ones.  However, this is conceptually what we do.
#' 
#' @param x
#' The features matrix.
#' @param y
#' The 2-class response vector. Note that the groups must be +/- 1.
#' See \code{recode()} 
#' @param intercept
#' Should the model include an intercept term?
#' @param k
#' TODO, currently ignored
#' @param lambda
#' Regularization parameter.
#' @param niter
#' The number of iterations.
#' 
#' @return
#' An object of class pegasosSVM.
#' 
#' @references
#' Shalev-Shwartz, Shai, et al. "Pegasos: Primal estimated sub-gradient solver
#' for svm." Mathematical programming 127.1 (2011): 3-30.
#' 
#' @examples
#' \dontrun{
#' library(ssvm)
#' 
#' y <- recode(iris$Species == "setosa")
#' x <- as.matrix(iris[, -5])
#' 
#' pegasos(x, y)
#' }
#' 
#' @author
#' Drew Schmidt
#' 
#' @export
pegasos <- function(x, y, intercept=TRUE, k=5, lambda=.1, niter=1e5)
{
  check.is.flag(intercept)
  check.is.posint(k)
  check.is.scalar(lambda)
  check.is.posint(niter)
  
  if (!is.double(x))
    storage.mode(x) <- "double"
  if (!is.integer(y))
    storage.mode(y) <- "integer"
  
  w <- .Call(R_svm_pegasos_fit, intercept, as.integer(k), as.double(lambda), as.integer(niter), x, y)
  nm <- colnames(x)
  if (!is.null(nm))
  {
    if (intercept)
      nm <- c("Intercept", nm)
    
    names(w) <- nm
  }
  
  svm <- list(w=w, niter=niter, intercept=intercept)
  class(svm) <- "pegasosSVM"
  
  svm
}



#' @export
print.pegasosSVM <- function(x, ...)
{
  cat(paste0("SVM model (Method=Pegasos, Iterations=", x$niter, ")\n"))
  print(x$w)
}



#' @export
predict.pegasosSVM <- function(object, newdata, ...)
{
  .Call(R_svm_pegasos_pred, newdata, object$w, object$intercept)
}
