py = open('test/mod/mod_py.txt').read()
c = open('test/mod/mod_c.txt').read()

if py == c:
    print('Success')
else:
    print()
    print('Failure')
    print(py)
    print(c)
    print()