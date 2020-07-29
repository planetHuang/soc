/ Copyright 2018-2020 Bizard-lab. All rights reserved.
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
    

#include "mysqlOP.hpp"
#include "all_header.h"
#include "cacheItem.hpp"
#include "queryItem.hpp"




using namespace std;


//初始化连接数据库需要的相关的参数
mysqlOP::mysqlOP(const string _DB_USERNAME,const string _DB_PASSWORD,const string _DB_DBNAME,const string _DB_TABLENAME):DB_USERNAME(_DB_USERNAME),DB_PASSWORD(_DB_PASSWORD),DB_DBNAME(_DB_DBNAME),DB_TABLENAME(_DB_TABLENAME){
}


//连接数据库中的某个表
void mysqlOP::connctDatabase(){
    
    /*连接之前。先用mysql_init初始化MYSQL连接句柄*/
    mysql_init(&mysql);
    /*使用mysql_real_connect连接server,其參数依次为MYSQL句柄。serverIP地址。登录mysql的username，password，要连接的数据库等*/
    if (!mysql_real_connect(&mysql, "localhost", DB_USERNAME.c_str(), DB_PASSWORD.c_str(), DB_DBNAME.c_str(), 0, NULL, 0)){
        printf("连接数据失败!\n");
        cout<<mysql_error(&mysql)<<endl;
        exit(0);
    }
    
    string queryStr = "desc "+ DB_TABLENAME ;
    
    //查询数据库
    if( mysql_query(&mysql,queryStr.c_str()) != 0){
        cout<<"获得表字段失败"<<endl;
        cout<<mysql_error(&mysql)<<endl;
        exit(0);
    }
    
    //获得结果集
    MYSQL_RES *result;
    result = mysql_store_result(&mysql);
    
    //输出受影响的行
    MYSQL_ROW row ;
    while((row = mysql_fetch_row(result)) != NULL) {
        table_ziduan.push_back(row[0]);
    }

    mysql_free_result(result); //释放结果集

    
    prefix_sql  = "select ";
    for(int i = dimsNum ; i < totalNum;++i ){
        prefix_sql += "sum(" + table_ziduan[i]  + "), ";
    }
    prefix_sql.pop_back();
    prefix_sql.pop_back(); //去掉最后的", "
    
    prefix_sql += " from " + string(DB_TABLENAME);
    
    
}

void mysqlOP::display_tables_ziduan(){
    for(auto a : table_ziduan){
        cout<<a<<endl;
    }
}


//执行查询
void mysqlOP::queryDatabase( queryItem & queryItem) {
    
    dims_type query =queryItem.getDims();
    string where;
    
    for(int i = 0 ; i < dimsNum;++i){
        if(query[i] != 0  ){
            where += " " + table_ziduan[i]+" = "+ to_string(query[i])+ " and" ;
        }
    }

    where.erase(where.end()-3,where.end());


    string queryStr = prefix_sql  + " where "+ where ;
    
    //queryItem.display();
    //cout<< "对应的sql为： " <<queryStr<<endl; 
    
    //查询数据库
    
    if( mysql_query(&mysql,queryStr.c_str()) ){
        cout<<"查询基本表失败！"<<endl;
        cout<<mysql_error(&mysql)<<endl;
        exit(0);
    }
    
    //获得结果集
    MYSQL_RES *result;
    result = mysql_store_result(&mysql);

    //保存查询到的度量值
    measure_type measure = 0.0;

    //输出受影响的行
    MYSQL_ROW row ;
   
    if((row = mysql_fetch_row(result)) != NULL) {
        for(int i = 0 ; i < totalNum - dimsNum ; ++i) {
            if(   row[i]   == NULL){
                cout<<"在mysql上找不到"<<endl;
                queryItem.setMeasure(-0.0);
                exit(0);
            }
            //cout<<row[i]<<endl;
            measure = std::atof( row[i] ) ;
        }
    }
    cout<<"measure : "<<measure<<endl;
    queryItem.setMeasure(measure);

    mysql_free_result(result); //释放结果集
}

void mysqlOP::free_connct(){
    /*关闭连接*/
    mysql_close(&mysql);
}

