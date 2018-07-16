# PROBILISTIC HOUGH LINE TRANSFORM  cv2.HoughLinesP()

import cv2
import numpy as np

img = cv2.imread('F:/Bhisma.jpg')
blk = cv2.imread('F:/blank.png')
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

blur = cv2.GaussianBlur(gray,(9,9),0)
retval, thresh = cv2.threshold(blur,70,255,cv2.THRESH_BINARY_INV)
kernel = np.ones((5,5),np.uint8)
closing = cv2.morphologyEx(thresh,cv2.MORPH_CLOSE,kernel)

kernel = np.ones((6,6),np.uint8)
dilate = cv2.dilate(closing,kernel,iterations = 5)
kernel = np.ones((8,8),np.uint8)
dilate2 = cv2.dilate(dilate,kernel,iterations = 3)     

kernel = np.ones((4,4),np.uint8)

minLineLength = 10
maxLineGap = 5

kernel = np.ones((9,9),np.uint8)
final = cv2.erode(dilate2,kernel,iterations=5)
lines = cv2.HoughLinesP(final,1,np.pi/180,180,minLineLength,maxLineGap)
'''for line in lines:
    for x1,y1,x2,y2 in line:
        cv2.line(blk,(x1,y1),(x2,y2),(0,255,0),2)
 '''  

cv2.waitKey(0)
cv2.destroyAllWindows()

# STORE THE VECTORS FOR VERTICAL AND HORIZONTAL LINES SEPARATELY
vertical = []
horizontal = []
slanting = []

for i in lines:  # FOR VERTICAL LINE y1 = y2
    if(i[0][0] == i[0][2]):
        vertical.append(i)
    elif(i[0][1] == i[0][3]):
        horizontal.append(i)
    else:
        slanting.append(i)
        
horizontal2 = []
size = len(horizontal)
c = 0
x = 0
count = 0
temp = 0

while(c<size):
    while(count<c+10):
        if(abs(horizontal[count][0][0]-horizontal[temp][0][0])>5):
            try:
                x += horizontal[temp][0]
            except:
                pass
        else:
            try:
                x += horizontal[count][0]
            except:
                pass
        temp = count
        count += 1
    temp=0
    x /= 10
    horizontal2.append(x)
    x = 0
    c += 10        

size = lambda vector: vector[0]
horizontal2.sort(key=size)

slanting2 = []
for i in slanting:
    for j in i:
        slanting2.append(j)

srt = lambda slant : ((slant[3]-slant[1])/(slant[2]-slant[0]))
slanting2.sort(key = srt)

m = []
for i in slanting2:
        m.append((i[3]-i[1])/(i[2]-i[0]))

count = 0

slanting3 = []
try:
    slanting3.append(slanting2[0])
except:
    pass

for i in slanting2:
    try:
        #if(count==0):
        #    pass     # m[-1] pe bhi O/P deta hai !!!
        if(m[count] <> m[count-1]):
            slanting3.append(i)
        count += 1
    except:
        pass
             

vertical2 = []
size = len(vertical)
c = 0
x = 0
count = 0
temp = 0

# !!!!!!!  VALUES CORRESPONDING TO COUNTER NEEDS TO BE CHANGED WITH CHANGE 
                                                                  #IN PEN !!!!!

while(c<size):
    while(count<c+10):
        if(abs(vertical[count][0][0] - vertical[temp][0][0]) > 5):
            try:
                x += vertical[temp][0]
            except:
                pass
        else:
            try:
                x += vertical[count][0]
            except:
                pass
        count += 1
    temp = 0
    x /= 10
    vertical2.append(x)
    x = 0
    c += 10

size = lambda vector: vector[1]
vertical2.sort(key=size, reverse=True)

horizontal3 = []
horizontal3 = horizontal2

vertical3 = []
vertical3 = vertical2


##### YAHAN SE CHALU HUA EK SATH KRKE INSTRUCTION DENE KA #####


#SEE FOR FAULT HERE
'''try:
    if(horizontal3[0][0] < vertical3[0][0]):
        AA = 0
    else:
        AA = 1
except:
    if(len(vertical3) == 0):
        AA = 0
    else:
        AA = 1'''
    
    
    
count = 0
tog = []
ln = len(lines)
while(count<ln/2):
    try:
        if(AA == 1):
            tog.append(vertical3[count])
        else:
            tog.append(horizontal3[count])
            
    except:
        pass
    try:
        if(AA == 1):
            tog.append(horizontal3[count])
        else:
            tog.append(vertical3[count])
    except:
        pass
    count += 1
    
tog1 = []

for i in horizontal3:
    tog1.append(i)
    
for i in vertical3: 
    tog1.append(i)

for i in slanting3:
    tog1.append(i)
    

diff = []    
count = 0    

for i in tog1:
    diff.append(tog1[count][1] - tog1[count][0])
    count += 1
    
idx = diff.index(max(diff))

x = tog1[idx][2]
y = tog1[idx][3]

count = 0
while(count < len(tog1)):
    if(count == idx):
        tog1[count] = np.append(tog1[count],-1)
    else:
        tog1[count] = np.append(tog1[count],abs((x-tog1[count][0])+
            (y-tog1[count][1])))
    count += 1

size = lambda vector : vector[4]
tog1.sort(key=size)

def dist(a):
    return np.sqrt((a[0]-a[2])**2 + (a[1]-a[3])**2)
    
count = 0  
inst = []
while(count<len(tog1)):
    try:
        if(tog1[count][0] == tog1[count][2]):
            inst.append([1,dist(tog1[count]),0])
        elif(tog1[count][1] == tog1[count][3]):
            inst.append([0,dist(tog1[count]),0.90])
        else:
            inst.append([2,dist(tog1[count]),
                         abs((tog1[count][3]-tog1[count][1])/
                             (tog1[count][2]-tog1[count][0]))])
    except:
        pass
    count += 1
    
    
for x1,y1,x2,y2 in horizontal2:
    cv2.line(blk,(x1,y1),(x2,y2),(0,255,0),2)
        

for x1,y1,x2,y2 in vertical2:
    cv2.line(blk,(x1,y1),(x2,y2),(0,255,0),2)
        
cv2.imshow('blk',blk)
cv2.waitKey(0)
cv2.destroyAllWindows()
