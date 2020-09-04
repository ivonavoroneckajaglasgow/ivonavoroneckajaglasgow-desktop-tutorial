#ifndef MOE_GATE_H
#define MOE_GATE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "armadillo"
#include "Expert.h"
#include "Node.h"

using namespace std;
using namespace arma;


class Gate: public Node{
    public:
    Gate(); //constructor
    vec gamma; //parameter associated with this gate length rp
    mat Omega; //prior variance for gamma
    void addChild(Node* aChild);
    void printChildren();
    void printDescendants();
    void printTerminalNodes();
    vector<Node*> getChildren();
    vector<Node*> getDescendantsInternal(vector<Node*>* desc);
    vector<Node*> getTerminalNodesInternal(vector<Node*>* terminal);
    int countChildren();
    int countDescendants();
    int refId();
    void issueID();
    void issueID_helper1(int* gate_id, int* expert_id);
    void issueID_helper2(int* gate_id, int* expert_id);
    double loglik(mat z, mat pi);
    double loglik(mat X, vec gamma, mat z);
    mat pi_calculator(mat X, vec gamma);
    mat pi_calculator2(mat X, vec gamma);
    mat pi_calculator3(mat X, vec gamma);
    vec score(mat X, mat z, mat pi);
    mat hessian(mat X, mat pi);
    vec findGammaMLEChol(mat X, mat z, mat Omega, mat* L); //Cholesky decomposition
    vec findGammaMLEChol(mat X, mat z, mat Omega);         //Cholesky decomposition
    vec findGammaMLEQR(mat X, mat z, mat Omega, mat* R);   //QR decomposition
    vec findGammaMLEQR(mat X, mat z, mat Omega);           //QR decomposition
    vec findGammaMLE(mat X, mat z, mat Omega);             //no decomposition
    mat makeAchol(vec pi);
    mat makeAchol2 (vec pi);
    mat getXout(mat X, mat pi);
    vec getZeta(mat z, mat pi);
    vec findGammaQR(mat X, mat z, mat Omega, mat* R);
    vec findGammaQR(mat X, mat z, mat Omega);
    vec updateGamma(vec gammaold, mat X, mat z, mat Omega);
    vec logmvndensity(vec response, vec mean, mat Sigma);
    vec logmvndensity(vec response, vec mean, mat* R);
    mat getRowSumsMat(mat A);
    int getDescendantIndex(Node* node);
    int issueIDLR(int start);
    int issueIDLR();
    int rightMostNodeID();
    int isInRange(Node* node);
    rowvec getZ_perpoint(Node* node);
    mat getZ(vector<Node*> z_final);
    vector<Node*> updateZ(vec y, mat X, vector<Node*> z_final); //returns a vector of updated allocations as pointers to Experts 
    vec getSampleProbsForZ(vec y, mat X); //y and X are for one i, returns alpha vector of pi*density
    Node* updateZ_onepoint_sample(vec alpha);// allocates an expert with supplied probabilities
    double getPathProb_internal(Node* node, mat X, double result);
    double getPathProb(Node* node, mat X); //X is for one i, returns path probability down from this to node
    vec getPathProb_mat(Node* node, mat X); //returns path probabilities (rows are observations and columns are experts)
    vec getChildrenIndicesLR(); //returns LR indices of children
    int whichChild(Node* node); //returns which child node is (to help identify the reference split)
    vec predict(mat X);
    void MCMC_internal(vec y, mat X, double logsigma_sq, vec mu_beta, mat Sigma_beta, double a, double b, vector<Node*> z_final); 
    vector<Node*> MCMC_OneRun(vec y, mat X, double logsigma_sq, vec mu_beta, mat Sigma_beta, double a, double b, vector<Node*> z_final);  
    vector<Node*> MCMC(int N, vec y, mat X, double logsigma_sq, vec mu_beta, mat Sigma_beta, double a, double b, vector<Node*> z_final);    
    string createJSON();
    string createJSON2(string s);
    string createJSON3();
    string jsonify(int indent);
};

#endif //MOE_GATE_H