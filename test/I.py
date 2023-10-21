data = input().split()
x = int(data[0])
y = int(data[1])
z = data[2]
code = {}
decode = {}
v = -1
for i in range(ord('0'), ord('9') + 1, 1):
    v += 1
    code[i] = v

for i in range(ord('A'), ord('Z') + 1, 1):
    v += 1
    code[i] = v

for i in range(ord('a'), ord('z') + 1, 1):
    v += 1
    code[i] = v

for i in code.items():
    decode[i[1]] = chr(i[0])

num = 0
v = 1
for i in z[::-1]:
    num += code[ord(i)] * v
    v *= x
ans = ""

while num > 0:
    ans += decode[(num % y)]
    num //= y
if z == '0':
    print('0')
else:
    print(ans[::-1])
