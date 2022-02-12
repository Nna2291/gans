import math


def get_intercetions(x0, y0, r0, x1, y1, r1):
    d = math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
    if d > r0 + r1:
        return None
    if d < abs(r0 - r1):
        return None
    if d == 0 and r0 == r1:
        return None
    else:
        a = (r0 ** 2 - r1 ** 2 + d ** 2) / (2 * d)
        h = math.sqrt(r0 ** 2 - a ** 2)
        x2 = x0 + a * (x1 - x0) / d
        y2 = y0 + a * (y1 - y0) / d
        x3 = x2 + h * (y1 - y0) / d
        y3 = y2 - h * (x1 - x0) / d
        x4 = x2 - h * (y1 - y0) / d
        y4 = y2 + h * (x1 - x0) / d
        return x3, y3, x4, y4


def get_coord(x0, y0, x1, y1, x2, y2, r0, r1, r2, dopusk=2):
    data = [x0, y0, r0, x1, y1, r1]
    x3, y3, x4, y4 = get_intercetions(*data)
    a3, b3, r3 = x2, y2, r2
    if abs((x3 - a3) ** 2 + (y3 - b3) ** 2 - r3 ** 2) <= dopusk:
        return x3, y3
    if ((x4 - a3) ** 2 + (y4 - b3) ** 2 - r3 ** 2) <= dopusk:
        return x4, y4
