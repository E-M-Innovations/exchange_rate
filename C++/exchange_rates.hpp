#ifndef EXCHANGE_RATES_H
#define EXCHANGE_RATES_H

#include <string>
#include <unordered_map>

//> A table of currency rates based on a target currency
struct Rates
{
    std::unordered_map<std::string, double> currencies;

    double get_rate(const std::string &currency) const;
};

//> An exchange rate given a base currencies and the various rates for it
struct ExchangeRates
{
    std::string base;
    std::string date;
    uint64_t time_last_updated;
    Rates rates;

    static const std::string api_url;

    static ExchangeRates
    get_latest(const std::string &base);

    double get_rate(const std::string &currency) const;

    void save(const std::string &path) const;
};

#endif // EXCHANGE_RATES_H
