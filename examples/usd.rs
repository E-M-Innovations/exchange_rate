use exchange_rate::ExchangeRates;

#[tokio::main]
async fn main() {
    let exchange = ExchangeRates::new("usd").await;
    // find cad rate
    let cad_rate = exchange.get_rate("CAD");
    println!("{:?}", cad_rate);
}