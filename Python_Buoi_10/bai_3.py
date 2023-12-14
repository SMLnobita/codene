import cv2
import numpy as np

image = cv2.imread('chainuoc.png')

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

blurred = cv2.GaussianBlur(gray, (9, 9), 0)
circles = cv2.HoughCircles(blurred, cv2.HOUGH_GRADIENT, dp=1.2, minDist=70,
                            param1=100, param2=30, minRadius=15, maxRadius=33)


circles = np.round(circles[0, :]).astype("int")

 
for (x, y, r) in circles:
    cv2.circle(image, (x, y), r, (0, 255, 255), 6)

    # Draw the count of bottle caps on the image
cv2.putText(image, f'So nap chai: {len(circles)}', (10, 30),
            cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

cv2.imwrite('KetQua.png', image)

# Display the output image
cv2.imshow('Output', image)
cv2.waitKey(0)
