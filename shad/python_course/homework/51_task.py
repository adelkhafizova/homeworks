def to_int(array):
    updated_array = []
    for i in xrange(0, len(array)):
        try:
            updated_array.append(int(array[i]))
        except ValueError as v:
            print v
    return updated_array

a = [1, 2, '3', 'test', 'dgdfg', 'lkfgh']
print to_int(a)
