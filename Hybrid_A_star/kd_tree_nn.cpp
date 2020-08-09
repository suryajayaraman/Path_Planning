 #include "kd_tree_nn.h"


// Node constructor definition
Node::Node(std::vector<double> arr, unsigned int setID)
{
    point = arr;
    id    = setID;
    left  = nullptr;
    right = nullptr;
}



// Kd_tree constructor definition
Kd_tree::Kd_tree(unsigned int k)
{
    this-> k_dimension = k;
    this-> rootNode = nullptr;
}
 


// function to insert new point in tree
// insert till a leaf node is reached
void Kd_tree::insert_point(const std::vector<double> &point, unsigned int id)
{    
    recursive_insert(rootNode, point, id, 0);
    return;
}



void Kd_tree::recursive_insert(Node* root, const std::vector<double> &point, unsigned int id, unsigned int dimension)
{
    // if a leaf node, assign point and return
    if(root == nullptr)
    {
        root = new Node(point , id);
        return;
    } 

    // left node condition
    if(point[dimension % (this->k_dimension)] < root->point[dimension % (this->k_dimension)])
    {
        recursive_insert(root->left, point, id, dimension + 1);
    }

    // right node condition
    else
    {
        recursive_insert(root->right, point, id, dimension + 1);
    }
}



std::vector<unsigned int> Kd_tree::query_tree(const std::vector<double> &target_point, const double &dist_threshold)
{
    // list of closest points (ids)
    std::vector<unsigned int> nn_points {};
    recursive_search(rootNode, target_point, nn_points, dist_threshold, 0);
    return nn_points;
}



void Kd_tree::recursive_search(Node* root, const std::vector<double> &target_point, std::vector<unsigned int> &nn_points, const double &dist_threshold, const unsigned int dimension)
{

    // leaf node reached
    if(this->rootNode==nullptr)
    {
        return;
    }

    // insert point only if target_point is within radius of dist_threhsold
    // check limits first, then radius check as sqrt is expensive to compute
    if(check_bdy_limit(root, target_point, dist_threshold) == true)
    {
        if(check_circular_limit(root, target_point, dist_threshold) == true)
        {
            nn_points.push_back(root->id);
        }
    }

    // left node condition
    if(target_point[dimension % (this->k_dimension)] < root->point[dimension % (this->k_dimension)])
    {
        recursive_search(root->left, target_point, nn_points, dist_threshold, dimension + 1);
    }

    // right node condition
    else
    {
        recursive_search(root->right, target_point, nn_points, dist_threshold, dimension + 1);
    }

    return;
}



bool Kd_tree::check_bdy_limit(Node* node, const std::vector<double> &target_point, const double &dist_threshold)
{
    bool inside_limits {true};
    bool lower_limit_status {true};
    bool upper_limit_status {true};

    for(unsigned int i =0; i < target_point.size(); i++)
    {
        lower_limit_status = ((target_point[i] - node->point[i]) >=-dist_threshold) ? true : false;
        upper_limit_status = ((target_point[i] - node->point[i]) <= dist_threshold) ? true : false;

        if((lower_limit_status && upper_limit_status) == false)
        {
            inside_limits = false;
            break;
        }
    }
    return inside_limits;
}



bool Kd_tree::check_circular_limit(Node* node, const std::vector<double> &target_point, const double &dist_threshold)
{
    bool within_radius {true};
    for(unsigned int i =0; i < target_point.size(); i++)
    {
        if(sqrt(((target_point[i] - node->point[i]) * (target_point[i] - node->point[i]))) > dist_threshold)
        {
            within_radius = false;
            break;
        }
    }
    return within_radius;
}