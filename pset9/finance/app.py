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

    # Pegar ações do usuário
    stocks = db.execute("""
        SELECT symbol, SUM(shares) as shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING shares > 0
    """, session["user_id"])

    # Pegar preços atuais e calcular totais
    total_value = 0
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["total"] = stock["price"] * stock["shares"]
        total_value += stock["total"]

    # Pegar saldo em dinheiro
    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = rows[0]["cash"]
    total_value += cash

    return render_template("index.html", stocks=stocks, cash=cash, total=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    # Validar entrada
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("deve fornecer um símbolo")
    if not shares or not shares.isdigit() or int(shares) <= 0:
        return apology("deve fornecer um número positivo de ações")

    shares = int(shares)
    quote = lookup(symbol)
    if quote is None:
        return apology("símbolo inválido")

    # Calcular custo total
    price = quote["price"]
    total_cost = price * shares

    # Verificar se usuário tem dinheiro suficiente
    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = rows[0]["cash"]

    if cash < total_cost:
        return apology("saldo insuficiente")

    # Atualizar banco de dados
    try:
        db.execute("BEGIN TRANSACTION")
        # Atualizar saldo
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_cost, session["user_id"])
        # Registrar transação
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price)
            VALUES (?, ?, ?, ?)
        """, session["user_id"], symbol.upper(), shares, price)
        db.execute("COMMIT")
    except:
        db.execute("ROLLBACK")
        return apology("erro na transação")

    flash(f"Comprado {shares} ações de {symbol} por {usd(total_cost)}!")
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("""
        SELECT symbol, shares, price, timestamp
        FROM transactions
        WHERE user_id = ?
        ORDER BY timestamp DESC
    """, session["user_id"])

    return render_template("history.html", transactions=transactions)


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

    if request.method == "GET":
        return render_template("quote.html")

    # Pegar símbolo do formulário
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("deve fornecer um símbolo")

    # Procurar cotação
    quote = lookup(symbol)
    if quote is None:
        return apology("símbolo inválido")

    # Mostrar resultado
    return render_template("quote.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Se o método for GET, mostrar formulário de registro
    if request.method == "GET":
        return render_template("register.html")

    # Se for POST, processar o registro
    # Pegar dados do formulário
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # Validar entrada
    if not username:
        return apology("deve fornecer um nome de usuário")
    elif not password:
        return apology("deve fornecer uma senha")
    elif not confirmation:
        return apology("deve confirmar a senha")
    elif password != confirmation:
        return apology("as senhas não coincidem")

    # Verificar se usuário já existe
    rows = db.execute("SELECT * FROM users WHERE username = ?", username)
    if len(rows) > 0:
        return apology("nome de usuário já existe")

    # Hash da senha
    hash = generate_password_hash(password)

    # Inserir novo usuário
    try:
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        return redirect("/login")
    except:
        return apology("erro ao registrar")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Pegar ações que o usuário possui
    stocks = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, session["user_id"])

    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)

    # Validar entrada
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("deve fornecer um símbolo")
    if not shares or not shares.isdigit() or int(shares) <= 0:
        return apology("deve fornecer um número positivo de ações")

    shares = int(shares)

    # Verificar se usuário possui ações suficientes
    owned_shares = 0
    for stock in stocks:
        if stock["symbol"] == symbol:
            owned_shares = stock["total_shares"]
            break

    if owned_shares < shares:
        return apology("ações insuficientes")

    # Pegar preço atual
    quote = lookup(symbol)
    if quote is None:
        return apology("símbolo inválido")

    price = quote["price"]
    total_value = price * shares

    try:
        db.execute("BEGIN TRANSACTION")
        # Atualizar saldo do usuário
        db.execute("""
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
        """, total_value, session["user_id"])

        # Registrar venda (shares negativo indica venda)
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price)
            VALUES (?, ?, ?, ?)
        """, session["user_id"], symbol, -shares, price)

        db.execute("COMMIT")
    except:
        db.execute("ROLLBACK")
        return apology("erro na transação")

    flash(f"Vendido {shares} ações de {symbol} por {usd(total_value)}!")
    return redirect("/")
