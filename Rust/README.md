# Exchange Rate 

The `exch_rate` library provides abstractions to get the latest currency exchange rate from the `exchangerate-api` which returns a table of currencies and their rates given a base currency. 

Current Features: 
- Gets the latest rates given a base currency 
    - `ExchangeRates::new(base)`
- Gets the rate of a given currency if exists
    - `ExchangeRates::get_rate(currency) -> Option<&f64>`
- Saves the exchange rates in a JSON file given the file's path. 
    - `ExchangeRates::save(path)`


Things to work on: 
- [ ] Historical rates given a start and end date 
- [ ] Blocking feature for synchronous operations
- [ ] Conversion functionality 
- [ ] Different language ports
- [ ] Better error handling 
- [ ] Documentation and examples