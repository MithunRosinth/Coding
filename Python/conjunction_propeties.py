
flag=0b0110
mask=0b0010
#check value of a bit
x=flag&mask
if(x==0b0010):
    print("set")
else:
    print("reset")

#reset a bit
x=flag&~mask
print(bin(x))

#set a bit
x=flag|mask
print(bin(x))

#negate a bit
x=flag^mask
print(bin(x))