from turtle import *

speed(0)
delay(0)
kt = 10

goto((-30 * kt, 0))
goto((30 * kt, 0))

goto((0, 0))

goto((0, -30 * kt))
goto((0, 30 * kt))

penup()

goto((-10 * kt, 0))
pendown()
goto((0, 10 * kt))

goto((-10 * kt, 20 * kt))
goto((-10 * kt, 0))
penup()



i0, j0, l0 = 29, -6, 1
check = False

for k in range(0, 51):

    if i0 <= 0 and j0 >= -10:
        if j0 <= 20 and j0 >= 0:
            if j0 > 10:
                if j0 <= -i0 + 10:
                    check = True
            else:
                if j0 >= i0 + 10:
                    check = True
    if check:
        K = k
        goto((i0 * kt, j0 * kt))
        dot(3, 'red')
        break
    
    i = min(max(min(i0 - j0, i0 - l0), j0 - l0), i0 - k) % 30
    j = max(min(max(i0 - j0, i0 - l0), j0 - l0), i0 - k) % 30
    l = i0 % 30 - j0 % 30 + l0 % 30 - k % 30

    i0, j0, l0 = i, j, l

    goto((i0 * kt, j0 * kt))
    dot(3, 'red')


if check:
    print(f'Hit. k = {K}, i = {i0}, j = {j0}, l = {l0}')
else:
    print(f'Miss. i = {i0}, j = {j0}, l = {l0}')


mainloop()