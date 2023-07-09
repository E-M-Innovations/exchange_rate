#include "exchange_rates.hpp"
#include <iostream>

int main()
{
    auto rates = ExchangeRates::get_latest("USD");
    std::cout << "EUR: " << rates.get_rate("EUR") << std::endl;
    rates.save("rates.json");
}
