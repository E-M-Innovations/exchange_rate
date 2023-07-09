#include "exchange_rates.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
const std::string ExchangeRates::api_url = "https://api.exchangerate-api.com/v4/latest/";

double Rates::get_rate(const std::string &currency) const
{
    auto it = currencies.find(currency);
    if (it != currencies.end())
    {
        return it->second;
    }
    else
    {
        return 0.0;
    }
}

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{
    std::string* response = (std::string*)up;
    response->append(buf, size * nmemb);
    return size * nmemb;
}

ExchangeRates ExchangeRates::get_latest(const std::string &base)
{
    std::string url = ExchangeRates::api_url + base;
    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    std::string response_text;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_text);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    auto json_response = json::parse(response_text);
    ExchangeRates result;
    result.base = json_response["base"];
    result.date = json_response["date"];
    result.time_last_updated = json_response["time_last_updated"];
    for (const auto &[key, value] : json_response["rates"].items())
    {
        result.rates.currencies[key] = value;
    }
    return result;
}

double ExchangeRates::get_rate(const std::string &currency) const
{
    return rates.get_rate(currency);
}

void ExchangeRates::save(const std::string &path) const
{
    json j;
    j["base"] = base;
    j["date"] = date;
    j["time_last_updated"] = time_last_updated;
    for (const auto &[key, value] : rates.currencies)
    {
        j["rates"][key] = value;
    }
    std::ofstream file(path);
    file << j.dump(4);
}
