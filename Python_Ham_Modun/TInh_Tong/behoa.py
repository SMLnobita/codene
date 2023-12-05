from tkinter import*

cuasone = Tk()
cuasone.title("Chương trình Code tính tổng")
cuasone.geometry("460x260")
cuasone.iconbitmap("favicon.ico")
# sử lý nút vào nhập
giaodienA = Label(cuasone,text="A=", font=("Arial", 20, "bold"))
giaodienA.place(x=20, y=30)

nhapA= Entry(cuasone, bg="white", fg="black",font=("Arial", 15, "bold"))
nhapA.place(x=70, y=32)


giaodienB = Label(cuasone, text="B=", font=("Arial", 20, "bold"))
giaodienB.place(x=20, y=70)

nhapB = Entry(cuasone, bg="White", fg="black", font=("Arial", 15, "bold"))
nhapB.place(x=70, y=72)

ketQua = Label(cuasone,font=("Arial", 20, "bold"), text="Kết Quả: ")
ketQua.place(x=20, y= 160)

traKetQua = Entry(cuasone, bg="white",fg="black", font=("Arial", 15, "bold"))
traKetQua.place(x=150, y=164)

#Hàm tính tổng
def tinhTong():
    try:
        sum = int(nhapA.get())+int(nhapB.get())
        traKetQua.delete(0, "end")
        traKetQua.insert(0, str(sum))
    except:
        traKetQua.delete(0, "end")
        traKetQua.insert(0, "Không có đáp án")

# Button
btn = Button(bg="green", fg="yellow", font=("Arial", 10, "bold"),
             text="Click", command=tinhTong)
btn.place(x=150, y=120)

cuasone.mainloop()