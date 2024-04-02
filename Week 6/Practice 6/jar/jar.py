class Jar:
    def __init__(self, capacity=12):
        if capacity < 1:
            raise ValueError("Capacity can't be less than 1!")
        self._capacity = capacity
        self._n = 0

    def __str__(self):
        return "🍪" * self._n

    def deposit(self, n):
        if self._n + n > self.capacity:
            raise ValueError("Not enough space in the jar!")
        self._n += n

    def withdraw(self, n):
        if self._n < n:
            raise ValueError("Not enough cookies to withdraw!")
        self._n -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._n


def main():
    cap = int(input("What will the maximum capacity of your cookie jar be? "))
    cookie_jar = Jar(cap)
    answer = input(
        "There's currently 0 cookies inside the jar. \nWould you like to add more?(Y/N) "
    )
    if answer.lower() == "y":
        add = int(input("How many cookies would you like to add to the jar? "))
        cookie_jar.deposit(add)
        print(cookie_jar)
        remove = input(
            f"We now have {add} cookies inside the jar! Would you like to remove a few?(Y/N) "
        )
        if remove.lower() == "y":
            withdraw = int(input("How many cookies would you like to remove? "))
            cookie_jar.withdraw(withdraw)
            print(cookie_jar)
    elif answer.lower() == "n":
        print("Cookie jar will remain empty forever :(")


main()
