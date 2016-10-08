#' recode
#' 
#' Recode a class variable to -1, 1 groups for use with SVM.
#' 
#' @param response
#' The class variable.
#' @param validate
#' Should the response be checked for more than 2 classes? If
#' so and more than 2 are found, it will throw an error.
#' 
#' @return
#' An integer vector of +/- 1's.
#' 
#' @examples
#' \dontrun{
#' recode(1:2)
#' recode(1:3) # two-class only!
#' }
#' 
#' @export
recode <- function(response, validate=TRUE)
{
  check.is.flag(validate)
  if (!is.numeric(response) && !is.logical(response))
    stop("argument 'response' must be numeric or logical")
  
  if (!is.integer(response))
    storage.mode(response) <- "integer"
  
  .Call(R_svm_recode_response, response, validate)
}
