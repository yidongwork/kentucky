library(geoRglm)

if(!exists(".Random.seed", envir=.GlobalEnv, inherits = FALSE))
set.seed(1234)

prior5 <- prior.glm.control(phi.prior='fixed',phi=.1)
mcmc5.tune <- mcmc.control(S.scale=.1,thin=1)
test2 <- pois.krige.bayes(p50,prior=prior5,mcmc.input=mcmc5.tune)

names(test2)
post<-test2$posterior
names(post)
postdist.beta.hat <- post$beta$sample
postdist.sigmasq.hat <- post$sigmasq$sample
postdist.phi.hat <- post$phi$sample
par(mfrow=c(1,3))
hist(postdist.beta.hat)
hist(postdist.sigmasq.hat)
hist(postdist.phi.hat)
