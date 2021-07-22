blocks = int(input("Enter the number of blocks: "))
i=1
if(blocks):
    height=1
while(i<blocks):
    if(((i*(i+1))/2)==blocks):
        height=i
    if(((i*(i+1))/2)>blocks):
        height=i-1
        break
    i+=1
print("The height of the pyramid:", height)

"""
total no of blocks = sum of first "height" numbers = (h*(h+1))/2
sum of first n natural numbers = (n*(n+1))/2

"""