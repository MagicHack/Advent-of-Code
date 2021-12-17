def is_in_area(x, y, x0, x1, y0, y1):
    return min(x0, x1) <= x <= max(x0, x1) and min(y0, y1) <= y <= max(y0, y1)


def simulate(start_x, start_y, x0, x1, y0, y1):
    max_y = 0
    x = 0
    y = 0
    vx = start_x
    vy = start_y
    while True:
        x, y, vx, vy = step(x, y, vx, vy)
        max_y = max(max_y, y)
        if is_in_area(x, y, x0, x1, y0, y1):
            # print((start_x, start_y))
            return True, max_y
        if vy < 0 and y < min(y0, y1):
            return False, max_y


def step(x, y, vx, vy):
    x += vx
    y += vy
    if vx < 0:
        vx += 1
    elif vx > 0:
        vx -= 1
    vy -= 1
    return x, y, vx, vy


def main():
    input_path = "input.txt"
    # input_path = "ex.txt"
    with open(input_path) as f:
        data = f.read().strip()

    x0, x1 = [int(x) for x in data.split(",")[0].split("x=")[1].split('..')]
    y0, y1 = [int(y) for y in data.split(",")[1].split("y=")[1].split('..')]

    maxes_y = []
    for x in range(max(x0, x1) + 1):
        for y in range(min(y0, y1), 500):
            result, max_y = simulate(x, y, x0, x1, y0, y1)
            if result:
                maxes_y.append(max_y)

    print(max(maxes_y), len(maxes_y))


if __name__ == '__main__':
    main()

