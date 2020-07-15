
#ifndef cacheItem_hpp
#define cacheItem_hpp

#include "all_header.h"
#include "queryItem.hpp"

using namespace std;

class cacheItem{             //缓存对象类，这个类就是缓存项，它会放在支持双重索引的容器中
private:
    
    bound_type upper;    //缓存项上界
    bound_type lowers;   //缓存项下界
    
    measure_type  measure;    //缓存项度量值，聚集函数只考虑一个度量值，这个是双重索引之一，在缓存项更新时用到
    data_cell_num_type sz ;                    //缓存项中上下界个数之和，即缓存项中的数据单元的个数
    ca_type ca  ;                   //covering capacity，即缓存项的响应能力
    
    layer_type low_min_layer;          //层号最小下界的值，这个是双重索引之一，查询数据在缓存中匹配时用到
    //layer_type upper_layer_index;    //上界层号做索引
    
    friend class SOC;    //为支持双重索引，需声明SOC_maxca为友元类
    
public:
    
    cacheItem() = delete;                   //禁止调用cacheItem的默认构造函数
    cacheItem(queryItem self_queryItem);    //生成缓存项，查询项自己构成上下界
    
    inline data_cell_num_type getSz()const;             //获得缓存项中上下界个数之和
    inline ca_type getCa()const;                        //获得covering capacity
    inline layer_type getLow_min_layer()const;          //获得层号最小下界的值
    
    
    void update_state();                    //更新状态
    void update_eqClass_sz();               //更新等价类中数据单元个数
    void update_ca();                       //更新等价类的Ca值
    
    
    inline bound_type getUp()const;         //获取上界
    inline bound_type getLow()const;        //获取下界
    inline measure_type getMeasure()const;                   //获取度量值
    
    inline bool sameMeasure(const queryItem& cur_queryItem) const;      //判断缓存项和查询项是否有相同的度量值，需要先判断度量值是否相等，然后在判断是否满足4种j连接情况
    bool addToCacheItem(const dims_type& queryItem_dims,int & state);   //向缓存中添加查询项（4中情况）
    
    void merge_up(const cacheItem& merged_cacheItem);      //合并缓存项，由于存在误判的情况，因此需要合并等价类
    
    void merge_low(const cacheItem& merged_cacheItem);
    
    void display()const;                          //打印缓存项
    
    
    //静态函数
    static bool cover(const dims_type& left_queryItem_dims,const dims_type& right_queryItem_dims);   //判断覆盖关系
    static const dims_type conjunction(const dims_type & left ,const dims_type & right);            //conjunction 运算
    static ca_type std_ca(const pair<dims_type,dims_type>&  region);                                //计算一个上界和一个下界的ca
};

//inline 函数定义
// 获得缓存项中上下界的总数
inline data_cell_num_type cacheItem::getSz()const{
    return  upper.size() + lowers.size();
}

//covering capacity
inline ca_type cacheItem::getCa()const{
    return ca;  //这个值在cacheItem::update_state()更新
}

//获取等价类的最小下界层号
inline layer_type cacheItem::getLow_min_layer()const{
    
    return low_min_layer;          //这个值在cacheItem::update_state()更新
    //return upper_layer_index;
}


inline bound_type cacheItem::getUp()const{
    return upper;
}

inline bound_type cacheItem::getLow()const{
    return lowers;
}

inline measure_type cacheItem::getMeasure()const{
    return measure;
}

inline bool  cacheItem::sameMeasure(const queryItem& cur_queryItem) const{
    
    return this->measure == cur_queryItem.getMeasure();
}

#endif /* equivalentClass_hpp */
