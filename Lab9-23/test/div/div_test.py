py = open('test/div/div_py.txt').read()
c = open('test/div/div_c.txt').read()

if py == c:
    print('Success')
else:
    print()
    print('Failure')
    print(py)
    print(c)
    print()