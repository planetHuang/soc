

#ifndef sqliteOP_hpp
#define sqliteOP_hpp

#include "all_header.h"
#include "database_operation.hpp"

//下一级缓存为sqlite，这是它的操作类
class sqliteOP : public database_operation{
private:
    sqlite3 *db;            //sqlite连接句柄
    char *zErrMsg = 0;      //错误消息
    string prefix_sql;      //sql查询语言的前缀
    
public:
    static vector<string> table_ziduan;    //保存表的字段
    
    virtual void connctDatabase();          //连接到mysql的表上
    
    virtual void display_tables_ziduan();    //打印表的字段
    
    virtual void queryDatabase(queryItem & queryItem);  //在sqlite中查询
    
    virtual void free_connct();           //释放连接
    
};
#endif /* sqliteOP_hpp */
