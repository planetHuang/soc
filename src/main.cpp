/

#include "all_header.h"
#include "cacheItem.hpp"
#include "queryItem.hpp"
#include "cache_manager.hpp"
#include "SOC.hpp"
#include "LRU.hpp"
#include "LFU.hpp"
#include "database_operation.hpp"
#include "mysqlOP.hpp"
#include "sqliteOP.hpp"


using namespace std;



void soc(){
   
    
    database_operation *database_op =  new sqliteOP();
    
    database_op->connctDatabase();
    
    
    cache_manager  *manager = new SOC();
    
    vector<queryItem>  queryItemSet = manager->load_query_file();

    cout<<"开始查询"<<endl;
    
    int hit = 0;
    
    
    time_t start,end;
    start = time(NULL);
    
    int i = 1;
    for(auto& querydata : queryItemSet){
        cout<<"第"<<i++<<"条"<<endl;
        querydata.display();
        
        bool flag = manager->query_in_cache(querydata);
       
        if(flag){
            cout<<"本条在缓存中找到了 ：====================================="<<endl;
            hit++;
            querydata.display();
        }else{
           
            database_op->queryDatabase(querydata);
          
            
         
            manager->refresh_cache(querydata);

            
        }
    }
    
    end = time(NULL);
    
    manager->displasy_cachaItem();
    
    cout<<"SOC"<<endl;
    cout<<"时间 （秒）： "<<end - start<<endl;
    cout<<"命中率 ："<<(hit/(float)queryItemSet.size())<<endl;
    

   
    
    
    manager->dispaly_experimental_result_to_file(queryItemSet.size(),hit,end - start);
    
    database_op->free_connct();
    
}

void lru(){
    
  
    database_operation *database_op =  new sqliteOP();
    
    database_op->connctDatabase();
    
    
    cache_manager  *manager = new LRU();
    
    
    vector<queryItem>  queryItemSet = manager->load_query_file();
    
    cout<<"开始查询"<<endl;
    
    int hit = 0;
    
    
    time_t start,end;
    start = time(NULL);
    
    int i = 1;
    for(auto& querydata : queryItemSet){
        cout<<"第"<<i++<<"条"<<endl;
        querydata.display();
        
        bool flag = manager->query_in_cache(querydata);
       
        if(flag){
            cout<<"本条在缓存中找到了 ：====================================="<<endl;
            hit++;
            querydata.display();
        }else{
           
            database_op->queryDatabase(querydata);
         
            manager->refresh_cache(querydata);
           
        }
    }
    
    end = time(NULL);
    
    manager->displasy_cachaItem();
    
    cout<<"LRU"<<endl;
    cout<<"时间 （秒）： "<<end - start<<endl;
    cout<<"命中率 ："<<(hit/(float)queryItemSet.size())<<endl;
    
   
    
    manager->dispaly_experimental_result_to_file(queryItemSet.size(),hit,end - start);
    
    database_op->free_connct();
   
}

void lfu(){
  
    database_operation *database_op =  new sqliteOP();
    database_op->connctDatabase();
    
    cache_manager  *manager = new LFU();
    
    vector<queryItem>  queryItemSet = manager->load_query_file();
    
    cout<<"开始查询"<<endl;
    
    int hit = 0;
    
    
    time_t start,end;
    start = time(NULL);
    
    int i = 1;
    for(auto& querydata : queryItemSet){
        cout<<"第"<<i++<<"条"<<endl;
        querydata.display();
        
       
        bool flag = manager->query_in_cache(querydata);
       
        
        if(flag){
            cout<<"本条在缓存中找到了 ：====================================="<<endl;
            hit++;
            querydata.display();
        }else{
           
            database_op->queryDatabase(querydata);
         
           
            manager->refresh_cache(querydata);
            
        }
    }
    
    end = time(NULL);
    
    manager->displasy_cachaItem();
    
    cout<<"LFU"<<endl;
    cout<<"时间 （秒）： "<<end - start<<endl;
    cout<<"命中率 ："<<(hit/(float)queryItemSet.size())<<endl;
    
   
    
    
    manager->dispaly_experimental_result_to_file(queryItemSet.size(),hit,end - start);
    
    database_op->free_connct();
    
}

int main(void){


  
    soc();


   
//    lru();
//
//
//  
//    lfu();


    
    return 0;
}

