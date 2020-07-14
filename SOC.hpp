

#ifndef SOC_hpp
#define SOC_hpp

#include "all_header.h"
#include "queryItem.hpp"
#include "cacheItem.hpp"
#include "cache_manager.hpp"

#include <stdio.h>
class SOC:public cache_manager{
private:
    
    struct by_layer{};    //以层号作为索引
    struct by_measure{};  //以度量值作为索引
    
    typedef boost::multi_index_container<
        cacheItem,
        indexed_by<
            ordered_non_unique< tag<by_layer>,BOOST_MULTI_INDEX_MEMBER(cacheItem,layer_type,low_min_layer) >,
            hashed_non_unique< tag<by_measure>,BOOST_MULTI_INDEX_MEMBER(cacheItem,measure_type,measure) >
        >
    > cacheItem_Index;
    
    cacheItem_Index SOC_Container;            //管理cacheItem对象的容器实例

   
public:
    //虚函数 实现
     virtual equivalence_class_num_type get_the_number_of_equivalence_classes()const;                             //获取等价类的个数
    
    virtual data_cell_num_type get_the_number_of_data_units()const;                                 //获取所有数据单元的个数
    
    virtual bool query_in_cache(queryItem& queryItem);            //在缓存中查询，共有4种
    
    virtual void refresh_cache(const queryItem& queryItem);               //更新缓存，共有4种
    
    virtual void cache_replacement_policy();                                   //缓存替换策略，共有4种
    
    virtual void dispaly_experimental_result_to_file(data_cell_num_type queryItemSet_size,int hit,time_t all_time)const;             //打印结果到文件中，有4种
    
    
    virtual vector<queryItem>  load_query_file();                           //从文件加载查询文件,并预处理，共有4种
    virtual void displasy_cachaItem()const;                                 //打印缓存项，共有4种

  
    
    
    virtual void get_ca_frequency()const;    //获取不同Ca值的频次
    virtual void temp() {
       
        int ret1 = 0;

        for(auto a : SOC_Container){
           
                ret1 += a.getUp().size() + a.getLow().size();
                
          
        }
        cout<<"数据单元个数(临时对照): "<<ret1<<endl;
    }
};


#endif /* SOC_hpp */
