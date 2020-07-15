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
    
#include "cacheItem.hpp"

using namespace std;

data_cell_num_type cache_data_cell_size = 0;    //这个是缓存项的所有数据单元的总和

const dims_type cacheItem::conjunction(const dims_type & left ,const dims_type & right){  //求conjunction
    
    if(left == right){        //元素相等,则随便返回一个,这种情况是存在的
        return left;
    }
    
    dims_type res;
    
    for(int i = 0; i < dimsNum;++i){
        
        res[i] = left[i] == right[i] ? left[i]:(left[i] != 0 ? left[i] : right[i]);
        
    }
    return res;
}

ca_type cacheItem::std_ca(const pair<dims_type,dims_type>& region){     //一个上界和一个下界时的ca
    
    const dims_type& up = region.first;
    const dims_type& low = region.second;
    
    layer_type layer_up = dimsNum - count(up.begin(), up.end(), 0);
    layer_type layer_low = dimsNum - count(low.begin(), low.end(), 0);
    
    return pow(2,layer_up - layer_low);
}

void Cij(int i, int j,vector<int> &r,int num,vector<vector<int> > & result) {
    //排列组合公式Cij

    if (j == 1) {
        for (int k = 0; k < i; k++) {
            vector<int> temp(num);
            r[num - 1] = k;
            for (int i = 0; i < num; i++) {
                temp[i] = r[i];
            }
            result.push_back(temp);
        }
    } else if (j == 0) {
        //do nothing!
    } else {
        for (int k = i; k >= j; k--) {
            r[j - 2] = k - 1;
            Cij(k - 1, j - 1, r, num, result);
        }
    }
}

//查询项自己构成上下界
cacheItem::cacheItem(queryItem self_queryItem){    
    
    upper.insert(self_queryItem.getDims());
    lowers.clear();      //当查询项自己构成上下界，下界是不保存的
    
    measure = self_queryItem.getMeasure();
    sz = 1;
    ca = 1;
    low_min_layer =  self_queryItem.getLayer();
    
}


//更新等价类的状态
void cacheItem::update_state(){
    //内部推导，多个上界一定能推出一个共同的上界

    
    if(upper.size() != 1){
        data_cell_num_type bef_up_size =  upper.size();
        
        dims_type common_upper={0};     //预先生成合并后的上界，用“0”填充
        //cout<<"多个上界一定能推出一个共同的上界"<<endl;
        for(int i = 0 ; i < dimsNum ;++i){
            for(auto every_upper : upper){
                if(every_upper[i] != 0){
                    common_upper[i] = every_upper[i];
                    break;
                }
            }
        }
        upper.clear();
        upper.insert(common_upper);
        cache_data_cell_size = cache_data_cell_size - bef_up_size + 1;
    }
    
    if(lowers.empty()){
        dims_type unique_upper = *upper.begin();
        low_min_layer =  static_cast<int> (dimsNum - count(unique_upper.begin(), unique_upper.end(),0));
    }else{
        int temp_layer = dimsNum;

        for_each(lowers.begin(), lowers.end(), [&temp_layer](const dims_type& every_lower){
            int every_layer = static_cast<int> (dimsNum - count(every_lower.begin(), every_lower.end(),0));
            if(temp_layer > every_layer){
                temp_layer = every_layer;
            }
        });

        low_min_layer = temp_layer;
    }
}

void cacheItem::update_eqClass_sz(){               //更新等价类中数据单元个数
    //更新缓存项中上下界的总数
    sz = upper.size() + lowers.size();
    cache_data_cell_size = cache_data_cell_size + sz;
}



 


void cacheItem::update_ca(){
    //更新Ca
    vector<dims_type> regions;    //保存多个下界
    map<int,dims_type> index;

    if(lowers.empty()){
        regions.push_back( *upper.begin());   //自己和自己构成上下界，没有下界
    }else{
        for(auto every_lower : lowers){
            regions.push_back(every_lower);
        }
    }

    int num = 0;      //容斥公式，每一项的结果
    ca = 0; //原ca置零
    for(int i = 0; i < regions.size();++i ){

        vector<int> resulttemp(i+1);
        vector<vector<int> > result;
        Cij((int)regions.size(),i+1,resulttemp,i+1,result);        //调用计算组合数函数
        //cout<<"第 "<<i<<" 项的组合情况"<<endl;
        num = 0;
        for(auto a :result){
            dims_type temp={0};
            string index_str;
            for(auto b : a){
                //cout<<b<<",";
                temp = cacheItem::conjunction(regions[b],temp);
            }
            //cout<<endl;
            num += cacheItem::std_ca(make_pair(*upper.begin(),temp));
        }

        resulttemp.clear();
        result.clear();

        if(i %2 != 0){
            ca += -1 * num;
        }else{
            ca += num;
        }
    }
}


//覆盖判断，left_queryItem_dims 能否覆盖到right_queryItem_dims上
bool cacheItem::cover(const dims_type& left_queryItem_dims,const dims_type& right_queryItem_dims){
    
    bool flag = false;
    
    for (int i = 0; i < dimsNum; ++i) {
        if( ( left_queryItem_dims[i]  == 0 )  ||  (left_queryItem_dims[i] ==  right_queryItem_dims[i]) ){
            flag = true;
        }else{
            flag = false;
            break;
        }
    }
    return flag;
}




bool cacheItem::addToCacheItem(const dims_type& queryItem_dims,int & state){

    bool only_cover_low = false;

    if(lowers.empty()){      //下界为空，即缓存项自己和自己构成上下界
        if(cacheItem::cover(queryItem_dims , *upper.begin())){
            cout<<"查询项能覆盖到缓存项的下界"<<endl;                          //查询项能覆盖到缓存项的下界
            state = 2;     //或4
            lowers.insert(queryItem_dims);
            update_state();
            cache_data_cell_size++;
            return true;
        }else if(cacheItem::cover(*upper.begin() ,queryItem_dims)){
            state = 1;     //或3
            cout<<"缓存项下界能覆盖到查询项"<<endl;                  //缓存项下界能覆盖到查询项
            lowers.insert(*upper.begin());
            upper.clear();
            upper.insert(queryItem_dims);
            cache_data_cell_size++;
 
            return true;
        }
    }else{                   //下界不为空
        if(cacheItem::cover(*upper.begin(),queryItem_dims )){
            state = 1;
            cout<<"缓存项上界能覆盖到查询项"<<endl;           //缓存项上界能覆盖到查询项
            upper.clear();
            upper.insert(queryItem_dims);
            return true;
        }else{
            for (auto iter = lowers.begin(); iter != lowers.end();  ++iter) {
              if( cacheItem::cover (*iter , queryItem_dims)){
                    state = 3;
                    cout<<"缓存项下界能覆盖到查询项"<<endl;                  //缓存项下界能覆盖到查询项
                    upper.insert(queryItem_dims);
                    cache_data_cell_size++;
                    update_state();
                    return true;
              }
            }
        }
        for (auto iter = lowers.begin(); iter != lowers.end(); ) {
            if( cacheItem::cover( queryItem_dims , *iter)){
                cout<<"查询项能覆盖到缓存项的下界"<<endl;                          //查询项能覆盖到缓存项的下界
                state = 4;
                lowers.erase(iter++);
                cache_data_cell_size--;
                only_cover_low = true;
            }else{
                ++iter;
            }
        }
        if(only_cover_low){
            lowers.insert(queryItem_dims);
            update_state();
            cache_data_cell_size++;
            return true;
        }
        
        if(cacheItem::cover(queryItem_dims,*upper.begin())){
            state = 2;
            cout<<"查询项只能覆盖到缓存项的上界"<<endl;
            lowers.insert(queryItem_dims);                      //插入新下界
            cache_data_cell_size++;
            update_state();
            return true;
        }
    }
    
    return false;
}

void cacheItem::merge_up(const cacheItem& merged_cacheItem){      //合并缓存项
   
    for(auto up : merged_cacheItem.getUp()){
        upper.insert(up);
    }
    
    for(auto low : merged_cacheItem.getLow()){
        lowers.insert(low);
    }
    
    //cout<<"合并缓存项e merge_up"<<endl;
}

void cacheItem::merge_low(const cacheItem& merged_cacheItem){      //合并缓存项

    for(auto up : merged_cacheItem.getUp()){
        upper.insert(up);
        
    }
    
    for(auto low : merged_cacheItem.getLow()){
        lowers.insert(low);
    }
    
}



void cacheItem::display()const{
    
    cout<<"一个上界 : "  <<endl;
    for_each(upper.begin(), upper.end(), [](const dims_type& every_upper){
        for_each(every_upper.begin(), every_upper.end(), [](const int& dims ){
            cout<<dims<<",";
        });
        cout<<endl;
    });
    
    
    cout<<endl<<"多个下界 : （如果下界没显示，则是自己和自己构成上下界）"<<endl;
    for_each(lowers.begin(), lowers.end(), [](const dims_type& every_lower){
        for_each(every_lower.begin(), every_lower.end(), [](const int& dims ){
            cout<<dims<<",";
        });
        cout<<endl;
    });
    
    cout<<"度量值 : "<<measure;
    
    cout<<endl<<"上下界总和 : "<<getSz()<<endl;
    cout<<"层号最小下界的值 : "<<getLow_min_layer()<<endl;
    cout<<"covering capacity :"<<getCa()<<endl;
    cout<<"---------分界线-----------"<<endl;
}
