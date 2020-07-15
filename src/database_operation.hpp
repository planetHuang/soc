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
