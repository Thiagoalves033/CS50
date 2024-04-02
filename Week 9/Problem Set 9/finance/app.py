import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    SHARES = db.execute(
        "SELECT symbol, SUM(amount) as shares FROM shares WHERE user_id = ? GROUP BY symbol",
        session["user_id"],
    )
    print(SHARES)
    TOTAL = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
        "cash"
    ]

    CASH = TOTAL

    for dictionary in SHARES:
        if lookup(dictionary["symbol"]) == None:
            return apology("NONE")

        lookprice = lookup(dictionary["symbol"])
        current_price = lookprice["price"]
        dictionary["price"] = current_price
        dictionary["total"] = current_price * dictionary["shares"]
        TOTAL += dictionary["total"]

    return render_template("index.html", shares=SHARES, total=TOTAL, cash=CASH)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        SYMBOL = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")

        # Ensure correct values are sent to the server
        if not SYMBOL or SYMBOL == None:
            return apology("invalid symbol", 400)
        elif not shares:
            return apology("invalid number of shares", 400)

        try:
            shares = int(shares)
        except (TypeError, ValueError):
            return apology("invalid number of shares", 400)

        if shares < 1:
            return apology("invalid number of shares", 400)

        # Check the amount of cash the user has
        cash_list = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        cash = float(cash_list[0]["cash"])

        # Check if user is able to buy
        price = SYMBOL["price"] * shares
        if cash < price:
            apology("not enough money", 400)

        else:
            post_cash = cash - price
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", post_cash, session["user_id"]
            )
            db.execute(
                "INSERT INTO transactions (user_id, symbol, amount, price, pre_transaction, post_transaction, transaction_type, date_and_time) VALUES (?, ?, ?, ?, ?, ?, 'BUY', datetime('now'))",
                session["user_id"],
                SYMBOL["name"],
                shares,
                price,
                cash,
                post_cash,
            )
            db.execute(
                "INSERT INTO shares (user_id, symbol, amount) VALUES (?, ?, ?)",
                session["user_id"],
                SYMBOL["symbol"],
                shares,
            )

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    HISTORY = db.execute(
        "SELECT symbol, amount, price, transaction_type, date_and_time FROM transactions WHERE user_id = ? ORDER BY date_and_time DESC",
        session["user_id"],
    )
    return render_template("history.html", history=HISTORY)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        SYMBOL = lookup(request.form.get("symbol"))

        if not SYMBOL:
            return apology("Invalid symbol", 400)

        return render_template("quoted.html", symbol=SYMBOL)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not confirmation:
            return apology("must provide confirmation", 400)

        # Ensure password has numbers, letters and minimum/maximum size
        if len(password) < 4 or len(password) > 10:
            return apology("password requires 4-10 characters, letters and numbers")
        else:
            num, let = False, False

            for character in password:
                if character.isalpha() == True:
                    let = True
                elif character.isdigit() == True:
                    num = True

        if num == False or let == False:
            return apology("password requires 4-10 characters, letters and numbers")

        # Ensure the passwords are the same
        elif password != confirmation:
            return apology("passwords do not match", 400)

        # Query for the username
        in_use = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Check if the username is already in use
        if len(in_use) == 1:
            return apology("username already in use", 400)

        # Register the user
        else:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                generate_password_hash(password, method="pbkdf2", salt_length=16),
            )

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was submitted correctly and update value for easier usage
        if not symbol:
            return apology("invalid symbol")
        else:
            symbol = lookup(symbol)

        # Query for number of shares user has
        amount_shares = int(
            db.execute(
                "SELECT SUM(amount) as nshares FROM shares WHERE (user_id = ?) AND (symbol = ?)",
                session["user_id"],
                symbol["symbol"],
            )[0]["nshares"]
        )

        # Check user money
        cash_list = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        cash = float(cash_list[0]["cash"])

        # Ensure number of shares was submitted
        if not shares or int(shares) < 1:
            return apology("invalid number of shares")

        # Ensure number of shares is at least 1
        elif amount_shares < int(shares):
            return apology("not enough shares")

        # Transaction
        else:
            post_cash = cash + (symbol["price"] * int(shares))
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", post_cash, session["user_id"]
            )
            db.execute(
                "INSERT INTO transactions (user_id, symbol, amount, price, pre_transaction, post_transaction, transaction_type, date_and_time) VALUES (?, ?, ?, ?, ?, ?, 'SELL', datetime('now'))",
                session["user_id"],
                symbol["name"],
                int(shares),
                symbol["price"],
                cash,
                post_cash,
            )

            for i in range(int(shares)):
                db.execute(
                    "UPDATE shares SET amount = (amount - 1) WHERE rowid = (SELECT MIN(rowid) FROM shares WHERE (symbol = ?) AND (user_id = ?))",
                    symbol["name"],
                    session["user_id"],
                )
                db.execute(
                    "DELETE FROM shares WHERE (amount <= 0) AND (user_id) = ?",
                    session["user_id"],
                )

            return redirect("/")

    else:
        SELECT = db.execute(
            "SELECT symbol FROM shares WHERE user_id = ? GROUP BY symbol",
            session["user_id"],
        )
        return render_template("sell.html", select=SELECT)
