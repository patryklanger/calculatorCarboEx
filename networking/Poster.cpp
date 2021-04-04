//
//  Poster.cpp
//  projekt pk4
//
//  Created by Patryk Langer on 20/03/2021.
//

#include "headers/Poster.hpp"

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
Poster::Poster(std::string url, std::string mode)
{
    this->url = url;
    this->mode = mode;
}
Poster Poster::setJsonData(Json::Value jsonData)
{
    this->jsonData = jsonData;
    return *this;
}
void Poster::post(void)
{
    if(!mode.compare("PATCH"))
    {
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
    }



    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    std::stringstream tempMess;
    std::unique_ptr <Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(jsonData, &tempMess);
    std::string message = tempMess.str();

    curl = curl_easy_init();
    try
    {
        std::stringstream httpData;
        long httpCode(0);
        
        if(!curl) throw std::runtime_error("Unable to post data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, this->mode.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        
        std::cout << "Posted with status code: " << httpCode << "\n";
        if(res!=CURLE_OK) throw std::runtime_error("Unable to post data");
        
        curl_easy_cleanup(curl);
        curl_global_cleanup();


    } catch (std::exception& err)
    {
        QMessageBox msgBox;
        msgBox.setText(err.what());
        msgBox.exec();
        std::cout << err.what() << std::endl;
        
    }
}

std::string Poster::getUrl()
{
    return url;
}

Json::Value Poster::getJsonData()
{
    return jsonData;
}

char* Poster::encodeUrl(std::string input)
{
    char *output = curl_easy_escape(curl, input.c_str(), input.length());
    return output;
}
