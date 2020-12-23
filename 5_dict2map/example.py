import example

class c:
    def __init__(self):
        self.a = 10

# a = [('a', 'apple'), ('a', 'adam'), ('b', 'banana')]
a = [('a', c()), ('a', 'adam'), ('b', 'banana')]

b = example.group_by(a)
print(b)