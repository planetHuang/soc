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
