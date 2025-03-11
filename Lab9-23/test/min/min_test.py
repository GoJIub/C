py = open('test/min/min_py.txt').read()
c = open('test/min/min_c.txt').read()

if py == c:
    print('Success')
else:
    print()
    print('Failure')
    print(py)
    print(c)
    print()