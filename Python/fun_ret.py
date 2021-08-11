"""## return with expression
def add(a,b):
	return a+b

x=add(2,4)
print(x)
"""
## return with not expression

def simple_ret(a,b):
	print("in function", a+b)
	return
simple_ret(2,4)
print("Outside the function")