import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

MONTHS = [
    {'name':"January", 'value':"1"},
    {'name':"February", 'value':"2"},
    {'name':"March", 'value':"3"},
    {'name':"April", 'value':"4"},
    {'name':"May", 'value':"5"},
    {'name':"June", 'value':"6"},
    {'name':"July", 'value':"7"},
    {'name':"August", 'value':"8"},
    {'name':"September", 'value':"9"},
    {'name':"October", 'value':"10"},
    {'name':"November", 'value':"11"},
    {'name':"December", 'value':"12"}
]

DAYS = []
for i in range(1,32):
    DAYS.append(i)


@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month_date")
        day = request.form.get("day_date")
        db.execute("INSERT INTO birthdays(name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        BIRTHDAYS = db.execute("SELECT * FROM birthdays;")
        return render_template("index.html", birthdays=BIRTHDAYS, months=MONTHS, days=DAYS)



