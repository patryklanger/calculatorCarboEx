//
//  fetch.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//
#include "headers/Fetcher.hpp"

namespace
{
std::size_t callback(
                     const char* in,
                     std::size_t size,
                     std::size_t num,
                     std::string* out)
{
    std::string data(in, (std::size_t) size * num);
    *((std::stringstream*) out) << data;
    return size * num;
}
}


/*------constructors------*/

Fetcher::Fetcher(std::string _url) {
    url = _url;
}

/*------methods------*/

void Fetcher::fetch(void)
{
    headers = curl_slist_append(headers, "Accept: application/json");
    curl = curl_easy_init();
    try
    {
        if(!curl) throw std::runtime_error(std::string("Unable to fetch"));
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        long httpCode(0);
        std::stringstream httpData;
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        if(res != CURLE_OK) throw std::runtime_error(std::string("Unable to fetch"));
        if(httpCode != 200) throw std::runtime_error(std::string("Unable to fetch"));
        
        std::cout << "Fetched with status code: " << httpCode << "\n";
        
        Json::Value jsonData;
        Json::CharReaderBuilder jsonReader;
        std::string errs;
        
        if (!Json::parseFromStream(jsonReader, httpData, &jsonData, &errs)) throw std::runtime_error(std::string("Unable to fetch"));
        
        this->jsonData = jsonData;
        
    } catch (std::runtime_error err)
    {

        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
        this->jsonData = Json::Value(false);
        
    }
}

Json::Value Fetcher::getJsonData()
{
    return jsonData;
}
