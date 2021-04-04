//
//  fetch.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef fetch_hpp
#define fetch_hpp


#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <QMessageBox>
#include <json/json.h>

class Fetcher {
private:
    std::string url;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL;
    Json::Value jsonData;
public:
    
    /*------constructors------*/
    
    Fetcher(std::string _url);
    
    /*------methods------*/
    
    void fetch(void);
    Json::Value getJsonData();
};

#endif /* fetch_hpp */
