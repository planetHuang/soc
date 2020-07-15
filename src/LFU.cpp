/ Copyright 2019 Bizard-lab. All rights reserved.
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

#include "LFU.hpp"




equivalence_class_num_type LFU::get_the_number_of_equivalence_classes()const{
   cout<<"cache_manager_LRU::get_the_number_of_equivalence_classes()const 不需要实现，如果错误调用则退出"<<endl;
    exit(0);
    return 0;
}

//获取数据单元的个数
data_cell_num_type LFU::get_the_number_of_data_units()const{                                 //获取所有数据单元的个数
    return LFU_Container.size();
}

bool LFU::query_in_cache(queryItem& queryItem){           //在缓存中查询
 
   
    
    if(LFU_Container.empty()){
        return false;
    }
    
    bool flag = false;
    
    for(auto &a : LFU_Container){
        if(a.getDims() == queryItem.getDims()){
            queryItem.setMeasure(a.getMeasure());
            a.add_LFU_count();
            flag = true;
            break;
        }
    }
   
    if(flag){
       
        return true;
    }else{
        
       
        return false;
    }
  
}

void LFU::refresh_cache(const queryItem& queryItem){       //更新缓存

    LFU_Container.push_back(queryItem);
    
    
    while(get_the_number_of_data_units() > data_cells_limit_size){
        cache_replacement_policy();
    }
    
    
}

void  LFU::cache_replacement_policy(){                                   //删除ca和用户模式最小的缓存项
    auto min = LFU_Container.begin();
    
    for(auto a =  LFU_Container.begin()++ ; a != LFU_Container.end();++a)  {
        if(a->get_LFU_count() < min->get_LFU_count()){
            min = a;
        }
    }
    LFU_Container.erase(min);
}


vector<queryItem>  LFU::load_query_file(){
    
    //从文件中读取
    vector<vector<string>> temp_queryItemSet;           //用来保存从文件读取出来的查询数据
    
    ifstream infile(querySetFilePath);                          //打开查询项文件
    string temp;
    if (!infile.is_open()){
        cout << querySetFilePath + " 路径下文件没打开 " << endl;
        exit(0);
    }
    
    while(getline(infile,temp)) {
        vector<string> tempvec ;
        SplitString(temp,tempvec,",");
        temp_queryItemSet.push_back (tempvec);
    }
    infile.close();    //关闭文件
    
    
    //从文件读取出来的查询数据，需要区分维度值和度量值，然后放入queryItem对象中
    vector<queryItem> ret_queryItemSet;
    
    for(auto a:temp_queryItemSet){
       
        dims_type temp_dims;
        measure_type temp_measure = 0.0;
        
        for(int i = 0 ; i < dimsNum;++i){
            temp_dims[i] = atoi(a[i].c_str());
        }
        
         queryItem temp_queryItem(temp_dims,temp_measure);
        
        ret_queryItemSet.push_back(temp_queryItem);
    }
    
    //返回vector<queryItem> ret_queryItemSet,这个就是之后查询中用到的实际数据
    return ret_queryItemSet;
}



void LFU::displasy_cachaItem()const{                        //打印缓存项
    cout<<endl<<endl<< "数据单元的总个数 : "<<get_the_number_of_data_units()<<endl;
    
    for_each(LFU_Container.begin(), LFU_Container.end(),[](const queryItem& every_quertItem){
        every_quertItem.display();
    });
    
}



void LFU::dispaly_experimental_result_to_file(data_cell_num_type queryItemSet_size,int hit,time_t all_time)const{
    ofstream to_file;
    to_file.open(basePath+"LFU算法.txt",ios::trunc);
    if (!to_file.is_open()){
       cout<<"实验结果回写文件失败"<<endl;
        exit(0);
    }
    to_file<<"算法名：LFU"<<endl;
    to_file<<"查询项个数 ： "<<queryItemSet_size<<endl;
    to_file<<"缓存限制大小(数据单元个数)："<<data_cells_limit_size<<endl;
    to_file<<"hit 次数 ： "<<hit<<endl;
    to_file<<"hit rate :"<< (float)hit/queryItemSet_size<<endl;
    to_file<<"总体耗时(秒) : "<<all_time<<endl;
    to_file<<"数据单元的个数 ："<<get_the_number_of_data_units()<<endl;
}

