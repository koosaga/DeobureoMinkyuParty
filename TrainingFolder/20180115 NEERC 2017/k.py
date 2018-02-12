print (45)
#b = 1
b = 4894569496159
for i in range(45):
    a = (2**(i+18))%(2**64)
    if i==0: a -= 1
    a *= b
    a %= (2**64)
    print(a, end = " ")
print ( "")
print ((b*((2**43))%(2**64)))

