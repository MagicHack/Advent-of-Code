from collections import Counter


def part1(polymer, rules):
    # naive solution
    for x in range(10):
        new_polymer = ""
        for i in range(len(polymer)):
            # print(polymer[i: i+2])
            rule = rules.get(polymer[i: i+2])
            # print(polymer[i:i+1])
            new_polymer += polymer[i:i+1]
            if rule is not None:
                new_polymer += rule
        polymer = new_polymer
    counts = Counter(polymer)
    return max(counts.values()) - min(counts.values())


def part2(polymer, rules):
    pairs_count = {}
    letter_count = Counter(polymer)

    for i in range(len(polymer) - 1):
        pair = polymer[i:i + 2]
        # print(pair)
        p = pairs_count.get(pair)
        if p is not None:
            pairs_count[pair] += 1
        else:
            pairs_count[pair] = 1

    for _ in range(40):
        for (a, b), count in pairs_count.copy().items():
            rule = rules.get(a + b)
            if rule is not None:
                p1 = a + rule
                p2 = rule + b
                pairs_count[a+b] -= count

                if letter_count.get(rule) is not None:
                    letter_count[rule] += count
                else:
                    letter_count[rule] = count

                if pairs_count.get(p1) is not None:
                    pairs_count[p1] += count
                else:
                    pairs_count[p1] = count

                if pairs_count.get(p2) is not None:
                    pairs_count[p2] += count
                else:
                    pairs_count[p2] = count

    return max(letter_count.values()) - min(letter_count.values())


def main():
    # input_path = "ex.txt"
    input_path = "input.txt"
    polymer = ""
    rules = {}
    with open(input_path) as f:
        for line in f:
            if line.count("->"):
                temp = line.strip().split(" -> ")
                rules[temp[0]] = temp[1]
            else:
                if len(line.strip()):
                    polymer = line.strip()

    print("P1: {}".format(part1(polymer, rules)))
    print("P2: {}".format(part2(polymer, rules)))


if __name__ == '__main__':
    main()
