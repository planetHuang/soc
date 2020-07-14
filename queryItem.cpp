

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
