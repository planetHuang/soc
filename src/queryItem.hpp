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

#ifndef querySet_hpp
#define querySet_hpp

#include "all_header.h"

//查询项对象

class queryItem{
private:
    
    dims_type  dims;            //维度值
    measure_type    measure;    //度量值
    layer_type layer ;          //层号
    
    
    int LFU_count; // 仅用于LFU算法
    
public:
    
    queryItem() = delete ;                                      //构造函数，禁止调用queryItem的默认构造函数
    queryItem(dims_type _dims,measure_type _measure);                  //构造函数
    
    inline void setMeasure(measure_type _measure);               //设置度量值
    inline measure_type getMeasure()const;                       //获得度量值
    
    
    inline dims_type getDims()const ;           //获得维度值
    inline layer_type getLayer()const;                 //获取层号
    
    void display()const;                 //显示查询项内容
    
    void add_LFU_count();
    
    int get_LFU_count()const;
    
};


//inline函数
//设置度量值，查询命中是使用
inline void queryItem::setMeasure(measure_type _measure){
    measure = _measure;
}

//获取度量值
inline measure_type queryItem::getMeasure()const{
    return measure;
}

//获取维度值
inline dims_type queryItem::getDims()const{
    return dims;
}

//获取层号
inline layer_type queryItem::getLayer()const{
    return layer;
}


#endif /* querySet_hpp */
