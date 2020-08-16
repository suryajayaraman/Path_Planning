#ifndef __KDTREE__
#define __KDTREE__

#include <vector>
#include <iostream>
#include <math.h>

/* Structure to reprsent a node of kd tree  
 * -----------
 * A structure for node is defined with four attributes - id, value, reference to 2 child nodes
*/
struct KDNode
{
    std::vector<double> point;
    KDNode* left;
    KDNode* right;
    unsigned int id;

    // constructor
    KDNode(std::vector<double> arr, unsigned int setID);
};


/* Class to reprsent a kd tree  
 * -----------
 * 
*/
class Kd_tree
{
    public:
        // constructor
        Kd_tree(unsigned int k);

        // destructor
        ~Kd_tree() {};

        // function to insert new point in tree
        void insert_point(const std::vector<double> &point, unsigned int id);
        std::vector<unsigned int> query_tree(const std::vector<double> &target_point, const double &dist_threshold);

    private:
        // private member variables
        KDNode* rootNode;

        // dimension of the point
        unsigned int k_dimension;

        // private member functions
        void recursive_insert(KDNode* root, const std::vector<double> &point, unsigned int id, unsigned int dimension);
        void recursive_search(KDNode* root, const std::vector<double> &target_point, std::vector<unsigned int> &nn_points, const double &dist_threshold, const unsigned int dimension);
        bool check_bdy_limit(KDNode* kdnode, const std::vector<double> &target_point, const double &dist_threshold);
        bool check_circular_limit(KDNode* kdnode, const std::vector<double> &target_point, const double &dist_threshold);
};

#endif /* __KDTREE__ */