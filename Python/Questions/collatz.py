c0=int(input())
if(c0>0):
    counter=0
    while(c0!=1):
        if(c0%2==0):
            c0//=2
        else:
            c0=c0*3+1
        print(c0)
        counter+=1
    print("Steps =", counter)