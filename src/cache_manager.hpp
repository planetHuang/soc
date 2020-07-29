/ Copyright 2018-2020 Bizard-lab. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef cache_manager_hpp
#define cache_manager_hpp

#include "all_header.h"
#include "queryItem.hpp"
#include "cacheItem.hpp"




class cache_manager{

public:
    
    
    virtual equivalence_class_num_type get_the_number_of_equivalence_classes()const = 0;                             //获取等价类的个数
    
    virtual data_cell_num_type get_the_number_of_data_units()const = 0;                                 //获取所有数据单元的个数
    
    virtual bool query_in_cache(queryItem& queryItem) = 0;            //在缓存中查询
    
    virtual void refresh_cache(const queryItem& queryItem) = 0;               //更新缓存
    
    virtual void cache_replacement_policy() = 0 ;                                   //缓存替换策略
    
    virtual void dispaly_experimental_result_to_file(data_cell_num_type queryItemSet_size,int hit,time_t all_time)const = 0;      //打印结果到文件中
    
  
    virtual vector<queryItem>  load_query_file()  = 0;                           //从文件加载查询文件,并预处理
    
    virtual void displasy_cachaItem()const =  0;                                 //打印缓存项
    
    virtual void temp() = 0;
};


#endif /* cache_manager_hpp */
