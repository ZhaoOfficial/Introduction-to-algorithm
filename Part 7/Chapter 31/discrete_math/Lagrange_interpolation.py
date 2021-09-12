# -*- coding:utf-8 -*-
data = [0, 150550125355646, 944474507418938, 110040335185999, 676042268761809, 193274108888331, 904128547609081, 354197665334455, 416432161112962, 283942097426448]

z = 1125899906900597
import itertools

def f(num):
    global z
    b = z
    fenmu = 1
    for person in people:
        if num != person:
            fenmu *= (num - person)

    while fenmu < 0:
        fenmu += z
    [s0, t0] = [1, 0]
    [s1, t1] = [0, 1]
    [x, y] = [0, 0]

    c = 1
    while c != 0:
        [x, y] = [s0 - (b//fenmu) * s1, t0- (b//fenmu) * t1]
        c = b % fenmu
        b = fenmu
        fenmu = c
        [s0, t0] = [s1, t1]
        [s1, t1] = [x, y]

    while t0 < 0:
        t0 += z

    fenzi = 1
    for person in people:
        if num != person:
            fenzi *= person

    return t0 * fenzi


for people in itertools.combinations('123456789', 5):
    people = list(people)
    for i in range(5):
        people[i] = int(people[i])

    result = 0
    for person in people:
        result += data[person] * f(person)
    print(people, result % z)
