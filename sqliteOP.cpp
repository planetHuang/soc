

#include "sqliteOP.hpp"

vector<string> sqliteOP::table_ziduan;  //定义保存表的字段变量

//获取表的字段
static int get_table_ziduan(void *data, int argc, char **argv, char **azColName){
    sqliteOP::table_ziduan.push_back(argv[1]);
    return 0;
}

static double measure = 0.0;  //保存度量值得变量

//获取度量值
static int get_measure(void *data, int argc, char **argv, char **azColName){
    measure = atof(argv[0]);
    return 0;
}

//连接到数据库的表上
void sqliteOP::connctDatabase(){
    //打开数据库
    int rc = sqlite3_open("/Users/YZR/workspace/sqlite/qc_cache.db", &db);    //qc_cache.db是一个文件，要用绝对路径
    if( rc ){
        fprintf(stderr, "连接sqlite数据库失败 : %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    
    //获取表的字段
    string sql = "PRAGMA table_info('" + DB_TABLENAME +"')";
    // 执行sql语句
    rc = sqlite3_exec(db, sql.c_str(), get_table_ziduan,NULL,&zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL 错误: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    //合成sql查询的前缀，这样就不用在查询中每个都合成前缀
    prefix_sql  = "select ";
    for(int i = dimsNum ; i < totalNum;++i){
        prefix_sql += "sum(" + sqliteOP::table_ziduan[i]  + "), ";
    }
    prefix_sql.pop_back();
    prefix_sql.pop_back(); //去掉最后的", "
    
    prefix_sql += " from " + string(DB_TABLENAME);
    
}

//打印表的字段
void sqliteOP::display_tables_ziduan(){
    for(auto a : sqliteOP::table_ziduan){
        cout<<a<<endl;
    }
}

//在sqlite中查询
void sqliteOP::queryDatabase(queryItem & queryItem){
    
    dims_type query =queryItem.getDims();
    string where;
    
    for(int i = 0 ; i < dimsNum;++i){
        if(query[i] != 0  ){
            where += " " + sqliteOP::table_ziduan[i]+" = "+ to_string(query[i])+ " and" ;
        }
    }
    
    where.erase(where.end()-3,where.end());
    
    
    string queryStr = prefix_sql  + " where "+ where ;
    
    //queryItem.display();
    //cout<< "对应的sql为： " <<queryStr<<endl;
    
    //查询数据库
    
    int rc = sqlite3_exec(db, queryStr.c_str(), get_measure, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "查询失败: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    queryItem.setMeasure(measure);
}

//释放连接
void sqliteOP::free_connct(){
    sqlite3_close(db);
}

