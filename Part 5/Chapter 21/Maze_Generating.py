import random

def find_adjacent_rooms(wall, rooms, m, n):
    row = wall // (2 * m - 1)
    col = wall % (2 * m - 1)

    if col < m - 1:
        return (rooms[row * m + col], rooms[row * m + col + 1])
    else: # col > m - 1
        col -= (m - 1)
        return (rooms[row * m + col], rooms[(row + 1) * m + col])

def find(room):
    global root

    if root[room] == room:
        return room
    else:
        return find(root[room])

def set_union(room1, room2):
    global root

    a = find(room1)
    b = find(room2)

    if a != b:
        root[a] = b

# number of rooms in one line
m = 5
# number of rooms in one column 
n = 4

number_of_rooms = m * n
rooms = [i for i in range(number_of_rooms)]
root = rooms.copy()
# wall is between the room
number_of_walls = 2 * number_of_rooms - m - n
is_wall = [True for _ in range(number_of_walls)]
untested_walls = [i for i in range(number_of_walls)]

connectedRooms = 1
while connectedRooms < number_of_rooms:
    wall = untested_walls[random.randrange(0, number_of_walls)]
    room = find_adjacent_rooms(wall, rooms, m, n)
    if find(room[0]) != find(room[1]):
        connectedRooms += 1
        is_wall[wall] = False
        set_union(room[0], room[1])

brokenWall = []
for i in range(number_of_walls):
    if is_wall[i] == False:
        brokenWall.append(i)
print(brokenWall)