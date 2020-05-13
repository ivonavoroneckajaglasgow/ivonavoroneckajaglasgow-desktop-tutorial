#ifndef MOE_FAMILY_H
#define MOE_FAMILY_H

#include <iostream>
#include <vector>
#include <cmath>
#include "armadillo"

using namespace std;
using namespace arma;

//This is a superclass of all Family objects 
//Most functions are virtual and overwritten at subclass levels

class GLMModel {
    public:
GLMModel();
virtual vec linkfun(vec mu); //link function for a vector of values of mu
virtual vec linkinv(vec eta); //the inverse of the link function
virtual vec dlinkfun(vec mu);
virtual vec varfun(vec mu); //the variance as function of the mean
virtual vec dmudeta (vec eta);// derivative dmu/deta
virtual vec loglik_vec(vec y, vec eta, double logsigma_sq); //returns the log-likelihood of the model 
virtual vec dloglik(vec y, vec eta, double logsigma_sq); //returns the derivative of log-likelihood 
virtual vec density(vec y, vec eta, double logsigma_sq); // returns density function
virtual vec logdensity(vec y, vec eta, double logsigma_sq); // returns log density function
virtual double deta(vec y, vec eta, double logsigma_sq);// returns the derivative of log likelihood wrt to eta
vec etafun(mat X, vec beta);
virtual vec a(vec phi); //a(phi) function in the exponential family expression for the family
virtual vec V(vec theta); //b''(theta) function in the exponential family expression for the family
vec initialiseBeta(vec y, mat X, vec phi);
vec findBeta(vec y, mat X, vec phi);
mat findR(vec y, mat X, vec phi);
vec proposeBeta(vec beta, mat R);
};


#endif //MOE_FAMILY_H