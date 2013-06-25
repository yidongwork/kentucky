rm(list = ls(all = TRUE))
#setwd('C:/main/projects/1.wnv/Buffalo/R/geoRglmCompile/Bayespoiskrig')
setwd('C:/Users/Administrator/Desktop/R-script')
load(file.choose()) #st.dat.Rdat

library(geoRglm)
dyn.load("C:/Rproj/geoRglm2.dll") #'geoRglm/src/geoRglm2.dll'
is.loaded('newmcmcrun5')

if(!exists(".Random.seed", envir=.GlobalEnv, inherits = FALSE))
set.seed(1234)

## glm
dat.org <- dat.org[1:10,]
#fmr.glmm<-as.formula(nvex~1+c.week+c.maxTemp+c.cum.pivex+c.wetland)
fmr.glmm<-as.formula(nvex~1+week)
glm.0<-glm(fmr.glmm,data=dat.org,family=poisson)
summary(glm.0)

## glm with spatio-temporal cov. modeling with changes in varcov.spatial
# construct 'geodata'
names(dat.org)
dat.S <- dat.org[,c(3:4,2,9,8)]
geodat<-as.geodata(dat.S,coords.col=1:3,data.col=4,covar.col=5,covar.names='week')

#temporal flow chart 
#to be decided in c code
source('prior.glm.control2.txt')
source('pois.krige.bayes2.txt')
source('.mcmc.bayes.conj.pois.log2.txt')
source('.pred.aux2.txt')
source('.krige.bayes.extnd2.txt')
source('krige.bayes2.txt')
source('prior.control2.txt')
source('varcov.spatial2.txt')

prior0 <- prior.glm.control2(beta.prior='normal',beta=c(-3.9,.2),
beta.var.std=matrix(c(2,0,0,1),nrow=2,byrow=T),
phi.discrete=seq(.1,4,.1),thetaS=1/87)
MC <- mcmc.control(S.scale=.1,phi.scale=.1, thin=2, n.iter=50, burn.in=10)
model0 <- model.glm.control(trend.d = trend.spatial(~week,geodat),cov.model='pure.nugget')
test.0 <- pois.krige.bayes2(geodat, prior = prior0, mcmc.input = MC, model=model0)
#need a setup

names(test.0)
post<-test.0$posterior
names(post)
postdist.beta.hat <- post$beta$sample
postdist.sigmasq.hat <- post$sigmasq$sample
postdist.phi.hat <- post$phi$sample
par(mfrow=c(1,3))
hist(postdist.beta.hat)
hist(postdist.sigmasq.hat)
hist(postdist.phi.hat)

