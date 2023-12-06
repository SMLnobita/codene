from tkinter import *


cuasone = Tk()
cuasone.title("Máy tính của Nguyễn Hoà")
cuasone.geometry("385x480")
cuasone.iconbitmap("favicon.ico")


def them_so(so):
    hientai = nhapkhung.get()
    nhapkhung.delete(0, END)
    nhapkhung.insert(END, hientai + so)


def xoa_trang():
    nhapkhung.delete(0, END)


def tinh_toan():
    try:
        ketqua = eval(nhapkhung.get())
        nhapkhung.delete(0, END)
        nhapkhung.insert(END, str(ketqua))
    except Exception as e:
        nhapkhung.delete(0, END)
        nhapkhung.insert(END, "Không có đáp án")


def xoa_kytu_cuoi():
    hientai = nhapkhung.get()
    nhapkhung.delete(len(hientai)-1, END)


anhne = PhotoImage(file="khtn.png") 
label_anh = Label(cuasone, image=anhne)
label_anh.pack(side=TOP, pady=(10, 0))  

# Trường nhập
nhapkhung = Entry(cuasone, bg="white", fg="black", font=("JetBrains Mono", 15, "bold"), width=21)
nhapkhung.pack(pady=(10, 20))  

# Khung nút bấm
khung_nut = Frame(cuasone)
khung_nut.pack()


nut = [
    ('7', 0, 0), ('8', 1, 0), ('9', 2, 0), ('/', 3, 0),
    ('4', 0, 1), ('5', 1, 1), ('6', 2, 1), ('*', 3, 1),
    ('1', 0, 2), ('2', 1, 2), ('3', 2, 2), ('-', 3, 2),
    ('DEL', 0, 3), ('.', 1, 3), ('0', 2, 3), ('+', 3, 3),
    ('C', 0, 4), ('(', 1, 4), (')', 2, 4), ('=', 3, 4)
]

for text, cot, hang in nut:
    if text not in ['=', 'C', 'DEL', '.']:
        hanhdong = lambda t=text: them_so(t)
    elif text == '=':
        hanhdong = tinh_toan
    elif text == 'C':
        hanhdong = xoa_trang
    elif text == 'DEL':
        hanhdong = xoa_kytu_cuoi
    elif text == '.':
        hanhdong = lambda: them_so('.')
    Button(khung_nut, text=text, width=5, height=2, command=hanhdong).grid(row=hang, column=cot, padx=5, pady=5)


cuasone.mainloop()
