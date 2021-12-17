from queue import PriorityQueue


def neighbours(point, data):
    points = []
    for p in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        (x1, y1) = (point[0] + p[0], point[1] + p[1])
        if 0 <= y1 < len(data) and 0 <= x1 < len(data[y1]):
            points.append((x1, y1))
    return points


def solve(start, end, data):
    pqueue = PriorityQueue()
    pqueue.put((0, start))
    visited = set()
    costs = {start: 0}

    while not pqueue.empty():
        (dist, currentPoint) = pqueue.get()
        visited.add(currentPoint)
        for n in neighbours(currentPoint, data):
            if n not in visited:
                current_cost = costs[currentPoint] + data[n[1]][n[0]]
                if n in costs:
                    old_cost = costs[n]
                    if old_cost > current_cost:
                        costs[n] = current_cost
                        pqueue.put((current_cost, n))
                else:
                    costs[n] = current_cost
                    pqueue.put((current_cost, n))

    return costs[end]


def generate_p2_map(data):
    new_map = []

    for row in data:
        new_row = row[:]
        for i in range(4):
            for x in row:
                new_val = x + i + 1
                if new_val > 9:
                    new_val -= 9
                new_row.append(new_val)
        new_map.append(new_row)

    new_new_map = []
    for r in new_map:
        new_new_map.append(r[:])
    for i in range(4):
        for row in new_map:
            new_row = []
            for x in row:
                new_val = x + i + 1
                if new_val > 9:
                    new_val -= 9
                new_row.append(new_val)
            new_new_map.append(new_row)
    return new_new_map


def main():
    file = "input.txt"
    data = []
    with open(file) as f:
        for line in f:
            data.append([int(x) for x in line.strip()])

    # P1
    print("P1 : {}".format(solve((0, 0), (len(data[0]) - 1, len(data) - 1), data)))

    # P2
    data_p2 = generate_p2_map(data)
    print("P2 : {}".format(solve((0, 0), (len(data_p2[0]) - 1, len(data_p2) - 1), data_p2)))


if __name__ == '__main__':
    main()
