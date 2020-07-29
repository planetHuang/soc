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

#include "queryItem.hpp"

//构造函数
queryItem::queryItem(dims_type _dims,measure_type _measure):dims(_dims),measure(_measure){
    layer =  dimsNum - count(dims.begin(), dims.end(), 0);
    
    LFU_count = 0;
}

//显示查询项内容
void queryItem::display()const{
    cout<<" 维度值 : ";
    for_each(dims.begin(), dims.end(), [](const int& num){
        cout<<num<<",";
    });
    
    cout<<" 度量值 :"<<measure<<" 层号 : "<<layer<<endl;
}


void queryItem::add_LFU_count(){
    ++LFU_count;
}
int queryItem::get_LFU_count()const{
    return LFU_count;
}
