//
//  Poster.hpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#ifndef Poster_hpp
#define Poster_hpp

#include <stdio.h>
#include <iostream>
#include <json/json.h>
#include <QMessageBox>
#include <curl/curl.h>

class Poster {
private:
    std::string url;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL;
    Json::Value jsonData;
    std::string mode;
public:
    Poster(std::string url, std::string mode="PATCH");
    Poster setJsonData(Json::Value jsonData);
    void post(void);
    std::string getUrl(void);
    Json::Value getJsonData();
    char* encodeUrl(std::string input);
    
    
};

#endif /* Poster_hpp */
