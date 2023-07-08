use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::path::PathBuf;
use serde_json::to_string_pretty;
use tokio::io::{AsyncWriteExt, Result};
use tokio::fs::File;

#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct ExchangeRates{
    base: String,
    date: String,
    time_last_updated: u64,
    rates: Rates,
}

#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct Rates{
    #[serde(flatten)]
    currencies: HashMap<String, f64>
}

impl Rates{
    fn get_rate(&self, currency: &str) -> Option<&f64>{
        self.currencies.get(currency)
    }
}


impl ExchangeRates{
    /// Get the latest exchange rate
    pub async fn new(base: &str) -> Self{
        let base = base.to_uppercase();
        let address = format!("https://api.exchangerate-api.com/v4/latest/{base}");
        reqwest::get(address).await.unwrap().json().await.unwrap()
    }
    /// Get the rate of a particular currency
    pub fn get_rate(&self, currency: &str) -> Option<&f64>{
        self.rates.get_rate(currency)
    }
    pub async fn save(&self, path: PathBuf) -> Result<()>{
        let str = to_string_pretty(self).unwrap();
        let mut file = File::create(path).await?;
        file.write_all(str.as_bytes()).await?;
        Ok(())
    }
}
