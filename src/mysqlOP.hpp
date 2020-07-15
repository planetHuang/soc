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
