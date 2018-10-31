import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
import re

from helpers import apology, login_required, lookup, usd, get_total

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    cash = db.execute("SELECT cash FROM users WHERE id = :user_id",  user_id=session["user_id"])[0]["cash"]
    portfolio_complete = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
    if portfolio_complete:
        index_table = get_total(portfolio_complete, lookup, usd)
        grand_total = index_table["total_sum"] + cash
        return render_template("index.html",  index_table=index_table["table"], cash=usd(cash), grand_total=usd(grand_total))
    else:
        index_table = get_total(portfolio_complete, lookup, usd)
        grand_total = index_table["total_sum"] + cash
        return render_template("index.html",  index_table=index_table["table"], cash=usd(cash), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # render buy template
    if request.method == "GET":
        return render_template("buy.html")
    # buy the share
    elif request.method == "POST":
        try:
            int(request.form.get("shares"))
        except ValueError:
            return apology("please input a posite integer")
        if not request.form.get("shares") or not float(request.form.get("shares")).is_integer() or int(request.form.get("shares")) < 1:
            return apology("please input a posite integer")
        # the lookup function returns and object with the stock symbol current price and name else returns None
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Quote not found")
        else:
            whole_prize = quote["price"] * int(request.form.get("shares"))
            user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                                   user_id=session["user_id"])

            if user_cash[0]["cash"] < whole_prize:
                return apology("Not enough funds")
            else:
                new_user_cash = user_cash[0]["cash"] - whole_prize
                update_user_cash = db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                                              cash=new_user_cash, user_id=session["user_id"])
                # save purchase history in history table
                history = db.execute("INSERT INTO history (user_id, bought, buying_price, num_shares, date, symbol, share) VALUES(:user_id, :bought, :buying_price, :num_shares, :date, :symbol, :share)",
                                     user_id=session["user_id"], bought=1, buying_price=quote["price"], num_shares=int(request.form.get("shares")),
                                     date=datetime.now(), symbol=quote["symbol"], share=quote["name"])
                # if this insert returns positive it means the symbol didn't exist because it must be unique
                # create a new record if the user has no shares from this symbol's name
                new_user_portfolio = db.execute("INSERT INTO portfolio (user_id, share, num_of_shares, symbol) VALUES(:user_id, :share, :num_of_shares, :symbol)",
                                                user_id=session["user_id"], share=quote["name"],
                                                num_of_shares=int(request.form.get("shares")),
                                                symbol=quote["symbol"])
                if new_user_portfolio:
                    portfolio_complete = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
                    # the function get_total returns a dictionary with all the info for the index table
                    index_table = get_total(portfolio_complete, lookup, usd)
                    grand_total = index_table["total_sum"] + new_user_cash
                    return render_template("index.html", index_table=index_table["table"], cash=usd(new_user_cash), grand_total=usd(grand_total))
                else:
                    # update stocks if the user has stocks with this symbol
                    stock_shares_num = db.execute("SELECT num_of_shares FROM portfolio WHERE user_id = :user_id AND symbol = :symbol",
                                                  user_id=session["user_id"], symbol=quote["symbol"])
                    new_shares = stock_shares_num[0]["num_of_shares"] + int(request.form.get("shares"))
                    update_shares = db.execute("UPDATE portfolio SET num_of_shares = :new_shares WHERE user_id = :user_id AND symbol = :symbol",
                                               new_shares=new_shares, user_id=session["user_id"], symbol=quote["symbol"])
                    # again render a complete info table for the user
                    portfolio_complete = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
                    index_table = get_total(portfolio_complete, lookup, usd)
                    grand_total = index_table["total_sum"] + new_user_cash
                    return render_template("index.html",  index_table=index_table["table"], cash=usd(new_user_cash), grand_total=usd(grand_total))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM history WHERE user_id = :user_id", user_id=session["user_id"])
    if not history:
        flash("You have no history")
    # make it user friendly
    for item in history:
        # here an example of a ternary operator
        item["bought"] = 'yes' if item["bought"] else ''
        item["sold"] = 'yes' if item["sold"] else ''
        item["buying_price"] = usd(item["buying_price"]) if item["buying_price"] else ''
        item["sale_price"] = usd(item["sale_price"]) if item["sale_price"] else ''
    return render_template("history.html", history_table=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("You are now logged in")
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
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        # the lookup function returns and object with the stock symbol current price and name else returns None
        quote = lookup(request.form.get("symbol"))
        if quote:
            # quoted html gives has a table that represents the quote's data
            return render_template("quoted.html", quote=quote, price=usd(quote["price"]))
        elif not quote:
            return apology("Quote not found")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        if len(request.form.get("password")) < 3:
            return apology("password must be longer than 2 characters", 400)
        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)
        if request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords must be the same", 400)
        password = request.form.get("password")
        if not re.search("[0-9]", password):
            return apology("password must contain at least one number", 400)
        # insert user into databse if user exist
        user_pass = request.form.get("password")
        hashed_pass = generate_password_hash(user_pass, method='pbkdf2:sha256', salt_length=8)
        new_user = db.execute("INSERT INTO users (username, hash) VALUES(:name, :password)",
                              name=request.form.get("username"), password=hashed_pass)
        # according to cs50 username and password must be unique
        if not new_user:
            return apology("user already exist and/or password already taken", 400)
        elif new_user:
            session["user_id"] = new_user
    flash("You are now registered and logged in")
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # get an array of stock symbols to display in view as a select tag
    share_to_sell = db.execute("SELECT symbol FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
    if request.method == "POST":
        if not request.form.get("symbol") or int(request.form.get("shares")) < 1:
            return apology("please select a symbol and give a positive integer")

        else:
            number_of_shares = db.execute("SELECT num_of_shares FROM portfolio WHERE user_id = :user_id AND symbol = :symbol",
                                          user_id=session["user_id"], symbol=request.form.get("symbol"))
            if not number_of_shares:
                return apology("User doesn't have this stock")
            # does user has enough shares to sell
            if number_of_shares[0]["num_of_shares"] >= int(request.form.get("shares")):
                # sell
                quote = lookup(request.form.get("symbol"))
                shares_price = int(request.form.get("shares")) * quote["price"]
                old_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
                sales_plus_old_cash = shares_price + old_cash
                new_cash = db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id",
                                      new_cash=sales_plus_old_cash, user_id=session["user_id"])

                # save sale history in history table
                history = db.execute("INSERT INTO history (user_id, sold, sale_price, num_shares, date, symbol, share) VALUES(:user_id, :sold, :sale_price, :num_shares, :date, :symbol, :share)",
                                     user_id=session["user_id"], sold=1, sale_price=quote["price"], num_shares=int(request.form.get("shares")),
                                     date=datetime.now(), symbol=quote["symbol"], share=quote["name"])

                new_shares = number_of_shares[0]["num_of_shares"] - int(request.form.get("shares"))
                # if user sells all his shares for that symbol
                if new_shares == 0:
                    delete_symbol = db.execute("DELETE FROM portfolio WHERE user_id = :user_id AND symbol = :symbol",
                                               user_id=session["user_id"], symbol=request.form.get("symbol"))
                    return redirect("/")
                else:
                    update_shares = db.execute("UPDATE portfolio SET num_of_shares = :new_shares WHERE user_id = :user_id AND symbol = :symbol",
                                               new_shares=new_shares, user_id=session["user_id"], symbol=request.form.get("symbol"))
                    return redirect("/")
            else:
                return apology("not enough shares")
    # if get request return sell.html
    if len(share_to_sell) == 0:
        flash("You have no shares to sell")
        return render_template("sell.html", shares=share_to_sell)
    return render_template("sell.html", shares=share_to_sell)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
