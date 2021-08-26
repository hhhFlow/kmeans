
#ifndef __KMEANS_H__
#define __KMEANS_H__

#include "point.h"
#include <vector>
#include <limits>

struct element {
    point p;
    void *custom;
    element() {
        p.clear();
        custom = 0;
    }
};
// args
struct kmeans_args {
    unsigned int num_clusters;         // How many classes do you need
    std::vector<struct element> *v;    // Element set
    unsigned int max_it_count;         // Max num of iterations
    unsigned long long int err_dist;   // error value
    void clear() {
        num_clusters = 0;
        v = NULL;
        max_it_count = 0;
        err_dist = 0;
    }

};

// cluster info
struct cluster {
    struct element mean;                     // cluster center info
    std::vector<struct element> elements;    // Element set
};

// kmeans result
struct kmeans_result {
    int use_it_count;                       // Actual number of iterations
    std::vector<struct cluster> result;     // cluster list
    void clear() {
        use_it_count = 0;
        result.clear();
    }
};

// calculate mean value
struct element mean_value(const std::vector<struct element> &v);
// kmeans algorithm
void kmeans(const struct kmeans_args &ka, struct kmeans_result &kr);


#endif // __KMEANS_H__