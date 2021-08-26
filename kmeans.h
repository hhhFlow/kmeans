
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
// 参数
struct kmeans_args {
    unsigned int num_clusters;         // 需要划多少类
    std::vector<struct element> *v;    // 元素集
    unsigned int max_it_count;         // 最大迭代次数
    unsigned long long int err_dist;   // 误差距离
    void clear() {
        num_clusters = 0;
        v = NULL;
        max_it_count = 0;
        err_dist = 0;
    }

};

// 簇信息
struct cluster {
    // struct point p;                          // 簇中心点
    struct element mean;                     // 簇中心点
    std::vector<struct element> elements;    // 簇元素集
};

// 结果
struct kmeans_result {
    int use_it_count;
    std::vector<struct cluster> result;     // 簇列表
    void clear() {
        use_it_count = 0;
        result.clear();
    }
};

// 求质心
struct element mean_value(const std::vector<struct element> &v);
// kmeans
void kmeans(const struct kmeans_args &ka, struct kmeans_result &kr);


#endif // __KMEANS_H__