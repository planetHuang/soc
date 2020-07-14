

#include "LRU.hpp"



equivalence_class_num_type LRU::get_the_number_of_equivalence_classes()const{
    cout<<"cache_manager_LRU::get_the_number_of_equivalence_classes()const 不需要实现，如果错误调用则u退出"<<endl;
    exit(0);
    return 0;
}

//获取数据单元的个数
data_cell_num_type LRU::get_the_number_of_data_units()const{                                 //获取所有数据单元的个数
    
    return LRU_Container.size();
}


bool LRU::query_in_cache(queryItem& queryItem){           //在缓存中查询
    bool flag = false;
    
  
    
    if(LRU_Container.empty()){
        return false;
    }
    
    for(auto iter =  LRU_Container.begin(); iter != LRU_Container.end(); ++iter){
        if(iter->getDims() == queryItem.getDims()){
            queryItem.setMeasure(iter->getMeasure());
            LRU_Container.push_front(*iter);
            LRU_Container.erase(iter);
            flag = true;
            break;
        }
    }
   
    //return flag;
    if(flag){
      
        return true;
    }else{
      
        return false;
    }
    
}

void LRU::refresh_cache(const queryItem& queryItem){       //更新缓存
    
    LRU_Container.push_front(queryItem);
    
    while(get_the_number_of_data_units() > data_cells_limit_size){
        cache_replacement_policy();
    }
    
}



void  LRU::cache_replacement_policy(){                                   //删除ca和用户模式最小的缓存项
    
    LRU_Container.pop_back();
    
}


vector<queryItem>  LRU::load_query_file(){
    
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
       
        dims_type temp_dims = {0};
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



void LRU::displasy_cachaItem()const{                        //打印缓存项
    cout<<endl<<endl<< "数据单元个数 : "<<get_the_number_of_data_units()<<endl;
   
    for_each(LRU_Container.begin(),LRU_Container.end(), [](const queryItem& every_queryItem){
        every_queryItem.display();
    });
}



void LRU::dispaly_experimental_result_to_file(data_cell_num_type queryItemSet_size,int hit,time_t all_time)const{
    ofstream alg;
    alg.open(basePath+"LRU算法.txt",ios::trunc);
    if (!alg.is_open())
    {   cout<<"实验结果回写文件失败"<<endl;
        exit(0);
    }
    alg<<"算法名：LRU"<<endl;
    alg<<"查询项个数 ： "<<queryItemSet_size<<endl;
    alg<<"缓存限制大小(数据单元个数)："<<data_cells_limit_size<<endl;
    alg<<"hit 次数 ： "<<hit<<endl;
    alg<<"hit rate :"<< (float)hit/queryItemSet_size<<endl;
    alg<<"总体耗时(秒) : "<<all_time<<endl;
    alg<<"数据单元的个数 ："<<get_the_number_of_data_units()<<endl;
}

