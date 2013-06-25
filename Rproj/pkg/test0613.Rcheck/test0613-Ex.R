pkgname <- "test0613"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
options(pager = "console")
library('test0613')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
cleanEx()
nameEx("mytestfun")
### * mytestfun

flush(stderr()); flush(stdout())

### Name: mytestfun
### Title: hello
### Aliases: mytestfun
### Keywords: ~kwd1 ~kwd2

### ** Examples

##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function (a, b) 
{
    print(a)
    print(b)
    print(a + b)
    return(a * b)
  }



cleanEx()
nameEx("result")
### * result

flush(stderr()); flush(stdout())

### Name: result
### Title: hello_result
### Aliases: result
### Keywords: datasets

### ** Examples

data(result)
## maybe str(result) ; plot(result) ...



### * <FOOTER>
###
options(digits = 7L)
base::cat("Time elapsed: ", proc.time() - base::get("ptime", pos = 'CheckExEnv'),"\n")
grDevices::dev.off()
###
### Local variables: ***
### mode: outline-minor ***
### outline-regexp: "\\(> \\)?### [*]+" ***
### End: ***
quit('no')
