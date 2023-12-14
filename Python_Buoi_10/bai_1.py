import cv2

vid = cv2.VideoCapture(0)

while True:
    ret, frame = vid.read()
    videone = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    latlai = cv2.flip(videone,1)
    cv2.imshow('Video', latlai)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break

vid.release()
cv2.destroyAllWindows()