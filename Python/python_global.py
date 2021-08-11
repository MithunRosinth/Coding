def my_function():
    global var
    var = 2
    print("Inside", var)


var = 1
my_function()
print("Outside", var)