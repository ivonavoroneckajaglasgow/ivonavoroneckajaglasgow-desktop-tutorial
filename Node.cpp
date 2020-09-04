#define _USE_MATH_DEFINES
#define EPS 2.22e-16

#include <vector>
#include <cmath>

#include "armadillo"
#include <boost/algorithm/string/join.hpp>

using namespace std;
using namespace arma;

#include "Node.h"
#include "Gate.h"

void Node::printParent() {
        cout << name << " parent is " << Parent->name << "." << endl;
}

void Node::printDescendants(){

}

void Node::printTerminalNodes(){

}

Gate* Node::getParent(){
    return Parent;
}

/**
 * @brief A dummy function, which is handled at expert and node levels.
 * 
 * @return vector<Node*> empty vector.
 */
vector<Node*> Node::getChildren() {
    vector<Node*> empty;
    return empty;
}

/**
 * @brief Retrieves ancestors of the node.
 * Calls the internal function getAncestorsInternal().
 * @return vector<Node*> vector of pointers to the ancestors of the node.
 */
vector<Node*> Node::getAncestors() {
    vector <Node*> ancest_test;
    ancest_test=this->getAncestorsInternal(&ancest_test);
    return ancest_test;
}

/**
 * @brief An internal helper function tht retrieves ancestors of the node.
 * 
 * @param ancest vector to be filled in with ancestors of the node.
 * @return vector<Node*> vector of pointers to the ancestors of the node.
 */
vector<Node*> Node::getAncestorsInternal(vector<Node*>* ancest) {

    if(this->Parent!=NULL){
        ancest->push_back(this->Parent);
        this->Parent->getAncestorsInternal(ancest);
    }
    return *ancest;

}

/**
 * @brief Retrieves the descendents of the node.
 * Calls the getDescendantsInternal() function from gate and expert levels.
 * @return vector<Node*> vector of pointers to the descendants of the node.
 */
vector<Node*> Node::getDescendants() {
    vector <Node*> desc_test;
    desc_test=this->getDescendantsInternal(&desc_test);
    return desc_test;
}

/**
 * @brief A dummy function, which is handled at expert and node levels.
 * @param desc 
 * @return vector<Node*> 
 */
vector<Node*> Node::getDescendantsInternal(vector<Node*>* desc){
vector<Node*> a;
return a;
}

/**
 * @brief Retrieves the terminal nodes descending from the node.
 * Calls the getTerminalNodesInternal() function from gate and expert levels.
 * @return vector<Node*> vector of pointers to the terminal nodes descending from the node.
 */
vector<Node*> Node::getTerminalNodes() {
    vector <Node*> terminal_test;
    terminal_test=this->getTerminalNodesInternal(&terminal_test);
    return terminal_test;
}

/**
 * @brief A dummy function, which is handled at expert and node levels.
 * 
 * @param terminal 
 * @return vector<Node*> 
 */
vector<Node*> Node::getTerminalNodesInternal(vector<Node*>* terminal){
vector<Node*> a;
return a;
}

int Node::countChildren() {
return 0;
}

/**
 * @brief A dummy function, which is handled at expert and node levels.
 * 
 */
void Node::issueID() {}
/**
 * @brief A dummy function, which is handled at expert and node levels.
 * 
 * @param gate_id 
 * @param expert_id 
 */
void Node::issueID_helper1(int* gate_id, int* expert_id){}
/**
 * @brief A dummy function, which is handled at expert and node levels.
 * 
 * @param gate_id 
 * @param expert_id 
 */
void Node::issueID_helper2(int* gate_id, int* expert_id) {}

int Node::issueIDLR(int start){
    return 0;
}

int Node::leftMostNodeID(){
    return this->idLR;
}

int Node::rightMostNodeID(){
    return 0;
}

int Node::isInRange(Node* node){
    return 0;
}

vec Node::getDescendantRange(){
    vec result;
    result<<this->leftMostNodeID()<<this->rightMostNodeID();
    return result;
}

int Node::countPoints(vector<Node*> node){
   int count=0;
   for(int i=0;i<node.size();i++){
    if(this->isInRange(node[i])==1){
       count=count+1;
    }
   }
   return count;
}

vec Node::getPointIndices(vector<Node*> node){
    vec range=this->getDescendantRange();    
    vec result(this->countPoints(node));
    int position=0;
    for(int i=0;i<node.size();i++){
        if(this->isInRange(node[i])==1){
            result[position]=i;
            position=position+1;
        }
    }
    return result;
}

mat Node::subsetX(mat X, vec index){
    mat result(index.size(),X.n_cols);
    for(int i=0;i<index.size();i++){
        result.row(i)=X.row(index[i]);
    }
    return result;
}

vec Node::subsetY(vec y, vec index){
    vec result(index.size());
    for(int i=0;i<index.size();i++){
        result[i]=y[index[i]];
    }
    return result;
}

// mat Node::getPathProbs(mat X, vector<Node*> z_final){
//     return 0;
// }

mat Node::pi_calculator(mat X, vec gamma){
    return 0;
}

void Node::MCMC_internal(vec y, mat X, double logsigma_sq, vec mu_beta, mat Sigma_beta, double a, double b, vector<Node*> z_final){
    
}

mat Node::getZ(vector<Node*> z_final){
    return 0;
}

string Node::createJSON(){
    return 0;
}

string Node::createJSON2(string s){
    return 0;
}

string Node::jsonify(int indent){
    return string("?");
}

std::string jsondict(std::map<std::string, std::string> m, int indent) {
    std::ostringstream os; 
    std::map<std::string, std::string>::iterator it;
    os << std::string(indent, ' ') << "{";    
    std::string s = std::string("");
    for (it = m.begin(); it!=m.end(); it++ ) {        
        os  << s << std::endl << std::string(indent+2, ' ') << "\"" << it->first << "\": " << it->second;
        s = std::string(",");
    }
    os << std::endl << std::string(indent, ' ') << "}";
    return os.str();
}

std::string dv2csv(std::vector<double> dv) {
  std::vector<std::string> sv;
  std::transform(std::begin(dv),
                 std::end(dv),
                 std::back_inserter(sv),
                 [](double d) {
                   std::ostringstream dos;
                   dos << std::scientific << d;
                   return dos.str();
                 });
  return boost::algorithm::join(sv, ", ");
}

std::string vec2arraystring(arma::vec b, int indent)
{
  std::vector<double> dv;
  std::ostringstream os; 
  dv = arma::conv_to<std::vector<double>>::from(b);
  os << std::string(indent, ' ') << "[ " << dv2csv(dv) << " ]";
  return os.str();
}

std::string mat2arraystring(arma::Mat<double> A, int indent)
{
  std::vector<double> dv;
  std::ostringstream os;
  for (size_t i = 0; i < A.n_rows; ++i)
  {
    dv = arma::conv_to<std::vector<double>>::from(A.row(i));
    if (i == 0)
    {
      os << std::string(indent, ' ') << "[ ";
    }
    else
    {
      os << std::string(indent + 2, ' ');
    }
    os << "[ " << dv2csv(dv) << " ]";
    if (i == A.n_rows - 1)
    {
      os << " ]";
    }
    else
    {
      os << "," << std::endl;
    }
  }
  return os.str();
}