import itertools

list_1 = [1,2,3,4]
list_2 = [3,8,9,10]
list_3 = [list_1, list_2]
for element in itertools.product([list_1,list_2]):
    print(element)

cart_prod = [(a,b) for a in list_1 for b in list_2]
print(cart_prod)