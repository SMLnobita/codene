import secrets
import string
import tkinter as tk
from tkinter import messagebox
from datetime import datetime

def generate_password(length=12):
    characters = string.ascii_letters + string.digits + string.punctuation
    return ''.join(secrets.choice(characters) for _ in range(length))

def on_generate():
    try:
        length = int(entry.get())
        if not 8 <= length <= 32:
            raise ValueError
        password = generate_password(length)
        password_label.config(text=password)
    except ValueError:
        messagebox.showerror("Đầu vào không hợp lệ", "Vui lòng nhập một số từ 8 đến 32")

def copy_to_clipboard():
    root.clipboard_clear()
    root.clipboard_append(password_label.cget("text"))
    messagebox.showinfo("Đã sao chép", "Mật khẩu đã được sao chép vào clipboard")

def save_password():
    password = password_label.cget("text")
    if password:
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        with open("output.txt", "a") as file:
            file.write(f"{current_time} - {password}\n")
        messagebox.showinfo("Đã lưu", "Mật khẩu đã được lưu vào output.txt")
    else:
        messagebox.showerror("Lỗi", "Không có mật khẩu để lưu")

root = tk.Tk()
root.title("Trình tạo mật khẩu")
root.geometry("500x400")

frame = tk.Frame(root)
frame.pack(expand=True)

tk.Label(frame, text="Nhập độ dài mật khẩu:", font=("Arial", 18)).pack(pady=10)
entry = tk.Entry(frame, font=("Arial", 18))
entry.insert(0, "12")
entry.pack(pady=10)

generate_button = tk.Button(frame, text="Tạo mật khẩu", command=on_generate, font=("Arial", 18))
generate_button.pack(pady=10)

password_label = tk.Label(frame, text="", font=("Arial", 18))
password_label.pack(pady=10)

copy_button = tk.Button(frame, text="Sao chép mật khẩu", command=copy_to_clipboard, font=("Arial", 18))
copy_button.pack(pady=10)

save_button = tk.Button(frame, text="Lưu mật khẩu", command=save_password, font=("Arial", 18))
save_button.pack(pady=10)

root.mainloop()
