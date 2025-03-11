py = open('test/total/total_py.txt').read()
c = open('test/total/total_c.txt').read()

if py == c:
    print('Success')
else:
    print()
    print('Failure')
    print(py)
    print(c)
    print()