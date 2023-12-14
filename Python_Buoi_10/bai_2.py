import cv2
import os

behoane_path = r'D:\\Code\\Python\\behoane.png'
finalne_path = r'D:\\Code\\Python\\finalne.png'

img = cv2.imread(behoane_path)
img_test = cv2.imread(finalne_path)

img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img_gray_bgr = cv2.cvtColor(img_gray, cv2.COLOR_GRAY2BGR)

resized_image = cv2.resize(img_test, (150, 150))
img_gray_bgr[100:250, 100:250] = resized_image
cv2.imshow('Anh ne', img_gray_bgr)
cv2.waitKey(0)

cv2.destroyAllWindows()
