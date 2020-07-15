

#ifndef mysqlOP_hpp
#define mysqlOP_hpp

#include "all_header.h"
#include "queryItem.hpp"
#include "database_operation.hpp"

using namespace std;

class mysqlOP:public database_operation {
private:
    MYSQL mysql;    //连接mysql的句柄
    
    const string DB_USERNAME;
    const string DB_PASSWORD;
    const string DB_DBNAME;
    const string DB_TABLENAME;
    
    vector<string> table_ziduan;
    string prefix_sql;
    
public:
    //构造函数
    mysqlOP(const string _DB_USERNAME,const string _DB_PASSWORD,const string _DB_DBNAME,const string _DB_TABLENAME);
    
    //连接到mysql的表上
    virtual void connctDatabase();
    
    //打印表的字段
    virtual void display_tables_ziduan();
    
    //在mysql中查询
    virtual void queryDatabase(queryItem & queryItem);
    //释放连接
    virtual void free_connct();
    
};

#endif /* mysqlOP_hpp */
