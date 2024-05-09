import math

class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        vec = Vector2D(self.x, self.y)
        if isinstance(other, Vector2D):
            vec.x += other.x
            vec.y += other.y
        else:
            vec.x += other
            vec.x -= other
        return vec

    def __sub__(self, other):
        return self.__add__(-other)

    def __neg__(self):
        return Vector2D(-self.x, -self.y)

    def __mul__(self, other):
        vec = Vector2D(self.x, self.y)
        if isinstance(other, Vector2D):
            vec.x *= other.x
            vec.y *= other.y
        else:
            vec.x *= other
            vec.y *= other
        return vec

    def __abs__(self):
        return Vector2D(abs(self.x), abs(self.y))

    def __len__(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

    def __getitem__(self, inx):
        if inx == 0:
            return self.x
        elif inx == 1:
            return self.y
        else:
            raise IndexError()
