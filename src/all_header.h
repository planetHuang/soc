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

#ifndef all_header_h
#define all_header_h


//多重索引支持
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>    //顺序索引
#include <boost/multi_index/hashed_index.hpp>     //散列（无序）索引
#include <boost/multi_index/composite_key.hpp>


//输入输出相关
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>

//标准库相关
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//容器相关
#include <array>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <sstream>
#include <map>

//字符串处理相关
#include <string.h>

//泛型算法支持
#include <algorithm>

//幂运算支持
#include<cmath>

//数据库相关
#include "mysql.h"
#include "sqlite3.h"


//计时相关
#include <sys/time.h>


//内建随机排列vector中数据
#include <algorithm>
#include <functional>
#include <cstdlib>


//辅助函数
#include "support_fun.hpp"

//导入命名空间
using namespace boost::multi_index;
using namespace std;

//静态全局变量
const string  soc_alg_name = "SOC_MinCa"  ;//文件名和算法名
const int dimsNum = 9;                                          //维度个数
const int totalNum = 10;                                         //维度+度量值个数
const unsigned int data_cells_limit_size =  80000000;            //限制缓存中数据单元的个数
const string  DB_USERNAME = "root";                             //数据库用户
const string  DB_PASSWORD = "33444433";                    //数据库密码
const string  DB_DBNAME = "qc_cache";                            //数据库名
const string  DB_TABLENAME = "E2_9_dims";                            //表名

const string  basePath = "/Users/YZR/Documents/论文/大论文/实验/";
const string  querySetFilePath = basePath + "queryset.txt";           //查询数据文件路径

///Users/YZR/Documents/论文/qc实验/test1/


//类型别名
typedef array<int,dimsNum> dims_type;     //维度值类型别名
typedef set<dims_type> bound_type;           //上界或下界的集合类型别名
typedef double measure_type;                     //度量值类型别名
typedef set<dims_type>::size_type data_cell_num_type;  //数据单元个数别名
typedef unsigned long equivalence_class_num_type;  //等价类个数别名
typedef unsigned int ca_type;                    //ca值类型别名
typedef unsigned short layer_type;               //层号类型别名

#endif /* all_header_h */
