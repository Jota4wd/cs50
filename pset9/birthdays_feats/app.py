import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

app = Flask(__name__)
app.config["TEMPLATES_AUTO_RELOAD"] = True
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        try:
            month = int(request.form.get("month"))
            day = int(request.form.get("day"))

            if not name or month < 1 or month > 12 or day < 1 or day > 31:
                return redirect("/")

            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        except ValueError:
            return redirect("/")

        return redirect("/")

    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route("/delete/<int:id>")
def delete(id):
    db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")

@app.route("/edit/<int:id>", methods=["GET", "POST"])
def edit(id):
    if request.method == "POST":
        name = request.form.get("name")
        try:
            month = int(request.form.get("month"))
            day = int(request.form.get("day"))

            if not name or month < 1 or month > 12 or day < 1 or day > 31:
                return redirect("/")

            db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
                      name, month, day, id)
        except ValueError:
            return redirect("/")

        return redirect("/")
    else:
        birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", id)[0]
        return render_template("edit.html", birthday=birthday)
