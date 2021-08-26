

#include "kmeans.h"
#include <limits>

// 求质心
struct element mean_value(const std::vector<struct element> &v) {
    struct element e, t;
    int n = v.size();
    if (n < 1) return e;
    for (int i = 0; i < n; ++i) {
        t.p.x_ += v[i].p.x_;
        t.p.y_ += v[i].p.y_;
    }
    e.p.x_ = t.p.x_ / n;
    e.p.y_ = t.p.y_ / n;
    return e;
};

void kmeans(const struct kmeans_args &ka, struct kmeans_result &kr) {
    const std::vector<struct element> &v = *(ka.v);
    // 1.参数校验
    unsigned int k = ka.num_clusters;
    unsigned int n = v.size();
    unsigned int max_it_count = ka.max_it_count;
    if (k < 1 || n < 1) return;
    if (k > n) k = n;
    if (max_it_count < 1) max_it_count = 1;
    std::vector<struct cluster> &kc = kr.result;  // k个簇 
    kc.reserve(k);
    struct cluster cluster_obj;
    for (unsigned int i = 0; i < k; ++i) {
        kc.push_back(cluster_obj);
    }

    // 2.选择k个初始质心 kmeans++
    // std::vector<struct element> m(k);
    // m[0] = v[0];
    kc[0].mean = v[0];      // 作为第1个簇中心
    std::vector<unsigned long long int> dist(n);
    unsigned long long int min_dist = 0, max_dist = 0;
    unsigned long long int d = 0;
    int max_index = -1, min_index = 0;
    for (unsigned int i = 1; i < k; ++i) {
        max_dist = std::numeric_limits<unsigned long long int>::min();
        for (unsigned int j = 0; j < n; ++j) {
            min_dist = std::numeric_limits<unsigned long long int>::max();
            for (unsigned int y = 0; y < i; ++y) {
                d = (v[j].p - kc[y].mean.p).len2();
                if (d < min_dist) {
                    min_dist = d;
                }
            }
            dist[j] = min_dist;
            if (dist[j] > max_dist) {
                max_dist = dist[j];
                max_index = j;
            }
        }
        kc[i].mean = v[max_index];
    }


    // 3.计算各个点与所有质心间的距离, 将距离最小的点分类到对应质心类中 
    bool fini = false;
    while (max_it_count--) {   // 最大迭代次数完毕 或者 完成迭代则退出
        // 清理
        for (unsigned int i = 0; i < k; ++i) {
            kc[i].elements.clear();
        }
        // 计算各个点与所有质心间的距离, 将距离最小的点分类到对应质心类中
        for (unsigned int i = 0; i < n; ++i) {
            min_dist = std::numeric_limits<unsigned long long int>::max();
            min_index = 0;
            for (unsigned int j = 0; j < k; ++j) {
                d = (v[i].p - kc[j].mean.p).len2();
                if (d < min_dist) {
                    min_dist = d;
                    min_index = j;
                }
            }
            kc[min_index].elements.push_back(v[i]);
        }

        // 4.重新计算每个类中的质心
        fini = true;
        for (unsigned int i = 0; i < k; ++i) {
            struct element e = mean_value(kc[i].elements);              // 新的质心
            unsigned long long int err = (e.p - kc[i].mean.p).len2();   // 与老的质心的距离
            kc[i].mean.p = e.p;     // 给新质心赋值
            if (err > ka.err_dist * ka.err_dist) {
                fini = false;
            }
        }
        if (fini) {
            break;
        }
    }
    if (fini) {
        kr.use_it_count = ka.max_it_count - max_it_count;
    } else {
        kr.use_it_count = ka.max_it_count - max_it_count - 1;
    }
}


