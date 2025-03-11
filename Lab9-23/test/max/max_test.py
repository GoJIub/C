py = open('test/max/max_py.txt').read()
c = open('test/max/max_c.txt').read()

if py == c:
    print('Success')
else:
    print()
    print('Failure')
    print(py)
    print(c)
    print()