CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER,
    symbol TEXT NOT NULL,
    amount NUMERIC NOT NULL,
    price NUMERIC NOT NULL,
    pre_transaction NUMERIC NOT NULL,
    post_transaction NUMERIC NOT NULL,
    transaction_type TEXT NOT NULL,
    date_and_time DATETIME,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE shares (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER,
    symbol TEXT NOT NULL,
    amount NUMERIC NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

-- Querying for index.html
SELECT symbol, COUNT(symbol), price, SUM(price) FROM transactions WHERE user_id = ? GROUP BY symbol;


UPDATE shares SET amount = (amount - 1) WHERE symbol = (SELECT symbol FROM shares WHERE (symbol = 'NFLX')) LIMIT 1;