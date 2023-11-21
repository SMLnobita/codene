n = int(input("Nhập n: "))
while n >= 100:
    n+=1
    if n >200:
        break
    if n%3==0 and n%5==0:
        print(n)
print("ket thuc")
