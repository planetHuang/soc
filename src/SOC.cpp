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

#include "SOC.hpp"

extern data_cell_num_type cache_data_cell_size ;    //这个是缓存项的所有数据单元的总和



//获取等价类的个数
equivalence_class_num_type SOC::get_the_number_of_equivalence_classes()const{
    return  SOC_Container.size();
}

//获取数据单元的个数
data_cell_num_type SOC::get_the_number_of_data_units()const{                                 //获取所有数据单元的个数
    return cache_data_cell_size;
}

bool SOC::query_in_cache(queryItem& queryItem){           //在缓存中查询
    bool match_up = false;
    bool match_low = false;
    
 
    
    if(get_the_number_of_data_units() == 0){
        return false;
    }
    
    
    layer_type queryItem_index = queryItem.getLayer();

    cacheItem_Index::index<by_layer>::type& indexOfLayer = SOC_Container.get<by_layer>();  //用层号做索引


    cacheItem_Index::index<by_layer>::type::iterator start_index = indexOfLayer.upper_bound(0);   //大于0
    cacheItem_Index::index<by_layer>::type::iterator end_index = indexOfLayer.lower_bound(queryItem_index+1);   //不小于queryItem_index+1


//    auto start_index = cacheItem_Container.begin();    //不用索引
//    auto end_index = cacheItem_Container.end();
    
    while(start_index != end_index){

        //cout<<"层号 :"<<end_index->getLow_min_layer()<<endl;

            match_up = false;
            match_low = false;
            for(auto up : start_index->getUp()){
                if(cacheItem::cover(queryItem.getDims(), up)){
                    match_up = true;
                    break;
                }else{
                    match_up = false;
                }
            }
            if(match_up){
                if(start_index->getLow().empty()){
                    if(  cacheItem::cover(  *start_index->getUp().begin() , queryItem.getDims())){
                        match_low = true;
                    }else{
                        match_low = false;
                    }
                }else{
                    for(auto low : start_index->getLow()){
                        if(cacheItem::cover( low ,queryItem.getDims())){
                            match_low = true;
                            break;
                        }else{
                            match_low = false;
                        }
                    }
                }
            }

            if(match_up&&match_low){
                queryItem.setMeasure(start_index->getMeasure());  //其实这一步可以省略
                //start_index->display();
                break;
            }
            ++start_index;
        //cout<<"vvv"<<endl;
        }
    
    if(match_up&&match_low){
      
        return true;
    }else{
        
     
        return false;
    }
}

void SOC::refresh_cache(const queryItem& queryItem){       //更新缓存
    
    
    if(get_the_number_of_equivalence_classes() == 0){
        cacheItem new_cacheItem(queryItem);
        cache_data_cell_size++;
        //new_cacheItem.update_state();     //这里不需要做任何更新，因为在构造这个缓存项时，所有值已经正确设置好了
        SOC_Container.insert(new_cacheItem);
        //new_cacheItem.display();
        return;
    }

    
    vector<cacheItem> merge_case1;   //用于合并
    vector<cacheItem> merge_case2;   //用于合并
    
    bool can_refresh_cache = false;
    
    cacheItem_Index::index<by_measure>::type& indexOfMeasure = SOC_Container.get<by_measure>();  //用度量值做索引

//    cacheItem_Index::index<by_measure>::type::iterator start_index = indexOfMeasure.upper_bound(queryItem.getMeasure() - 1);
//    cacheItem_Index::index<by_measure>::type::iterator end_index = indexOfMeasure.lower_bound(queryItem.getMeasure() + 1);

    std::pair<cacheItem_Index::index<by_measure>::type::iterator,cacheItem_Index::index<by_measure>::type::iterator>  pair_range = indexOfMeasure.equal_range(queryItem.getMeasure());

    
    while(pair_range.first != pair_range.second){
        int state = 0;
        cacheItem temp = *pair_range.first;
        if(temp.addToCacheItem(queryItem.getDims(),state)){
            //indexOfMeasure.replace(start_index, temp);
            cache_data_cell_size = cache_data_cell_size - temp.getSz();
            indexOfMeasure.erase(pair_range.first++);
            can_refresh_cache = true;
            
            if(state == 1 || state == 3){
                merge_case1.push_back(temp);
                //            cache_data_cell_size = cache_data_cell_size - temp.getSz();
                //            indexOfMeasure.erase(start_index++);
            }else if(state == 2 || state == 4){
                merge_case2.push_back(temp);
                //            cache_data_cell_size = cache_data_cell_size - temp.getSz();
                //            indexOfMeasure.erase(start_index++);
            }
            
        }else{
            pair_range.first++;
        }
        
        //cout<<"死循环"<<endl;
    }
    
    //合并误判的缓存项
    if(merge_case1.size() != 0 ){
        //合并缓存项
        //cout<<"合并缓存项 查询数据作为上界"<<endl;
        vector<cacheItem>::iterator first = merge_case1.begin();
        for(auto iter = merge_case1.begin()+1; iter != merge_case1.end(); ++iter){
            first->merge_up(*iter);
        }
        
        first->update_eqClass_sz();
        first->update_state();
        first->update_ca();              //这3句话的顺序不能乱
        
        SOC_Container.insert(*first);
    }
    
    if(merge_case2.size() != 0){
        //合并缓存项
        //cout<<"合并缓存项 查询数据作为下界"<<endl;
        vector<cacheItem>::iterator first = merge_case2.begin();
        
        for(auto iter = merge_case2.begin()+1; iter != merge_case2.end(); ++iter){
            first->merge_low(*iter);
        }
       
        first->update_eqClass_sz();
        first->update_state();
        first->update_ca();                     //这3句话的顺序不能乱
       
        SOC_Container.insert(*first);
    }
    
    if(!can_refresh_cache){
        SOC_Container.insert(cacheItem(queryItem));//当前查询项构成的新缓存项,自己和自己构成上下界
        cache_data_cell_size++;
    }
    
    
    
    
    
        while(get_the_number_of_data_units() > data_cells_limit_size){
            cache_replacement_policy();
        }
   
    
}

void  SOC::cache_replacement_policy(){                                   //删除ca最小的缓存项
    

    auto min = SOC_Container.begin();
    for(auto a =  SOC_Container.begin(); a != SOC_Container.end();++a)  {
        if(a->getCa() < min ->getCa()){
            min = a;
        }
    }
    cache_data_cell_size = cache_data_cell_size - min->getSz();
    SOC_Container.erase(min);
}


vector<queryItem>  SOC::load_query_file(){
    
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


void SOC::displasy_cachaItem()const{                        //打印缓存项
    cout<<endl<<endl<< "打印所有等价类 ："<<endl;
    for(auto a : SOC_Container){
        a.display();
    }
    cout<<endl<<endl<< "总的等价类个数 : "<<get_the_number_of_equivalence_classes()<<endl;
}

void SOC::get_ca_frequency()const{    //获取不同Ca值的频次
    vector<int> ca_values ;        //保存所有等价类的Ca值
    for(auto a : SOC_Container){
        ca_values.push_back(a.getCa());
    }
    
    vector<int> temp_ca_values = ca_values;    //复制出一个临时变量
    
    sort(ca_values.begin(),ca_values.end());
    ca_values.erase(unique(ca_values.begin(), ca_values.end()), ca_values.end());    //对fre中保存的Ca值去重
    
       map<int,int> m;                     //保存不同Ca值对应的频次
        for(auto a : ca_values){
            m.insert(make_pair(a, 0));       //先把去重后的Ca值放入m中，并设置频次为0
        }
    
        for(auto& a : m){
            int count = 0;
            for(auto b:temp_ca_values){
                if(a.first == b){
                    count++;           //计算频次
                }
            }
            a.second = count;          //保存频次
        }
    
    
    cout<<"打印不同Ca值，以及对应的频次(这样打印出来是为了方便Python代码处理)"<<endl;
    for(auto a:m){
        cout<<"'"<<a.first<<"',";
    }
    cout<<endl<<endl;
    for(auto a:m){
        cout<<a.second<<",";
    }
    cout<<endl<<endl;
}


void SOC::dispaly_experimental_result_to_file(data_cell_num_type queryItemSet_size,int hit,time_t all_time)const{
        ofstream alg;
        alg.open(basePath+ soc_alg_name +"算法.txt",ios::trunc);
        if (!alg.is_open()){
            cout<<"实验结果回写文件失败"<<endl;
            exit(0);
        }
    
        alg<<"算法名：" + soc_alg_name<<endl;
        alg<<"查询项个数 ： "<<queryItemSet_size<<endl;
        alg<<"缓存限制大小(数据单元个数)："<<data_cells_limit_size<<endl;
        alg<<"hit 次数 ： "<<hit<<endl;
        alg<<"hit rate :"<< ((float)hit)/queryItemSet_size<<endl;
        alg<<"总体耗时(秒) : "<<all_time<<endl;
        alg<<"数据单元的个数 ："<<get_the_number_of_data_units()<<endl;
        alg<<"等价类个数 ："<<get_the_number_of_equivalence_classes()<<endl;
    
    
    vector<int> ca_values ;        //保存所有等价类的Ca值
    for(auto a : SOC_Container){
        ca_values.push_back(a.getCa());
    }
    
    vector<int> temp_ca_values = ca_values;    //复制出一个临时变量
    
    sort(ca_values.begin(),ca_values.end());
    ca_values.erase(unique(ca_values.begin(), ca_values.end()), ca_values.end());    //对fre中保存的Ca值去重
    
    map<int,int> m;                     //保存不同Ca值对应的频次
    for(auto a : ca_values){
        m.insert(make_pair(a, 0));       //先把去重后的Ca值放入m中，并设置频次为0
    }
    
    for(auto& a : m){
        int count = 0;
        for(auto b:temp_ca_values){
            if(a.first == b){
                count++;           //计算频次
            }
        }
        a.second = count;          //保存频次
    }
    
    
    alg<<"打印不同Ca值，以及对应的频次(这样打印出来是为了方便Python代码处理)"<<endl;
    for(auto a:m){
        alg<<"'"<<a.first<<"',";
    }
    alg<<endl<<endl;
    for(auto a:m){
        alg<<a.second<<",";
    }
    alg<<endl<<endl;
    
}

