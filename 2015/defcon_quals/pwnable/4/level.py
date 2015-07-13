def parse_level(data):
    """
    >>> with open('sample.txt') as fp:
    >>>     data = fp.read()
    >>> parse_level(data)
    """
    lines = data.split('\n')
    found = False
    level = []
    for line in lines:
        if found:
            level.append(line)

            if line.startswith('19'):
                found = False

        if '012345678901234567890' in line:
            found = True

    map = [[] * 10] * len(level)
    for y, row in enumerate(level):
        row = row[3:]  # strip row num

        for x, cell in enumerate(row):
            if cell != '':
                map[y][x] = cell
    return map
