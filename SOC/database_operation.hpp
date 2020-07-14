

#ifndef database_operation_hpp
#define database_operation_hpp

#include "queryItem.hpp"

class database_operation{
    
public:
    
    //连接到mysql的表上
    virtual void connctDatabase() = 0;
    
    //打印表的字段
    virtual void display_tables_ziduan() = 0;
    
    //在mysql中查询
    virtual void queryDatabase(queryItem & queryItem) = 0;
    //释放连接
    virtual void free_connct() = 0;
};
#endif /* database_operation_hpp */
