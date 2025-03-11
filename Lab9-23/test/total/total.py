i0, j0, l0 = map(int, input().split())
check = False

for k in range(0, 51):

    if i0 <= 0 and j0 >= -10:
        if j0 <= 20 and j0 >= 0:
            if j0 > 10:
                if j0 <= -i0 + 10:
                    K = k
                    check = True
                    break
            else:
                if j0 >= i0 + 10:
                    K = k
                    check = True
                    break
    
    i = min(max(min(i0 - j0, i0 - l0), j0 - l0), i0 - k) % 30
    j = max(min(max(i0 - j0, i0 - l0), j0 - l0), i0 - k) % 30
    l = i0 % 30 - j0 % 30 + l0 % 30 - k % 30

    i0, j0, l0 = i, j, l

    print(f'k = {k}, i = {i0}, j = {j0}, l = {l0}')


if check:
    print(f'Hit. k = {K}, i = {i0}, j = {j0}, l = {l0}')
else:
    print(f'Miss. i = {i0}, j = {j0}, l = {l0}')
