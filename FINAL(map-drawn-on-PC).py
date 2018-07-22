import cv2                                                                      # OPENCV IMPORTED
import numpy as np                                                              # NUMPY IMPORTED

# LINE DETECTION 
img = cv2.imread('F:/line.png')                                                 # FILE CONTAING PATH
blk = cv2.imread('F:/blank.png')          #
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)                                     # MAKING THE IMAGE GRAYSCALE 
edges = cv2.Canny(gray,50,100,apertureSize = 3)                                 # CANNY EDGE DETECTION
minLineLength = 10                                                              # MAXIMUM LINE LENGTH FOR EDGE DETECTION
maxLineGap = 5                                                                  # MAXIMUM GAP B/W THE LINES (RANDOM VALUE 'COZ VAR OF NO USE HERE)
edges = cv2.GaussianBlur(edges, (3,3), 0)                                       # GAUSSIAN FILTER (IMG SMOOTHING)
lines = cv2.HoughLinesP(edges,1,np.pi/180,180,minLineLength,maxLineGap)         # PROBILISTIC HOUGH-LINE TRANSFORM
for line in lines:
    for x1,y1,x2,y2 in line:                                                    # DRAWING THE DETECTED LINES (ASTHETICS)
        cv2.line(img,(x1,y1),(x2,y2),(0,255,0),2)
        
# lines VARIABLE CONTAINS THE LIST OF DATA RETUNED BY HOUGH-LINE TRANSFORM
         
cv2.imshow('image',img)                                                         # DISPLAY THE DETECTED LINE IN GREEN  
cv2.waitKey(0)
cv2.destroyAllWindows()


# SORTING THE VECTORS(RETURNED BY HoughLinesP()) FOR VERTICAL AND HORIZONTAL LINES SEPARATELY

vertical = []                                                                   # LIST FOR VERTICAL LINES
horizontal = []                                                                 # LIST FOR HORIZONTAL LINES
slanting = []                                                                   # LIST FOR SLANTING LINES

# FOR VERTICAL LINES x1=x2
# FOR HORIZONTAL LINES y1=y2 
# ELSE SLANTING
for i in lines:
    if(i[0][0] == i[0][2]):
        vertical.append(i)
    elif(i[0][1] == i[0][3]):                                                    # THUS SORTING THE LINES                                                                                                                                              
        horizontal.append(i)
    else:
        slanting.append(i)

horizontal2 = []                                                                # THE DRAWN LINES IS CERTAIN PIXELS THICK, THIS VAR STORES ONLY THE MEAN LINE

size = len(horizontal)
c = 0
x = 0
count = 0

while(c<size):
    while(count<c+6):
        try:
            x += horizontal[count][0]                                           # TAKING THE MEAN EVERY SIX VECTORS AND APPENDING IN horizontal2
        except:                                                                 # "try:/except:pass" IS USED TO PREVENT ERROR WHEN CODE TRIES TO TAKE MEAN OF VECTORS MORE THAN THE INDEXING 
            pass
        count += 1
    x /= 6
    horizontal2.append(x)
    x = 0
    c += 6        

# LIST IS SORTED USING VALUES OF x1 WHICH WILL INCREASE WITH EVERY SUCCEDING HORIZONTAL LINE
size = lambda vector: vector[0]                                                 # LAMBDA FUNC. FOR SORTING
horizontal2.sort(key=size)                                                      # KEY IS DATA WITH 0th INDEXING IN THE LIST i-e x1 

slanting2 = []
for i in slanting:
    for j in i:                                                                 # CHANGING THE SHAPE OF SLANTING VARIABLE, FROM A list of lists TO A list
        slanting2.append(j)

# SORT SLANTING LINES ON BASIS OF THEIR SLOPE

srt = lambda slant : ((slant[3]-slant[1])/(slant[2]-slant[0]))
slanting2.sort(key = srt)

# STORE SLOPES OF ALL SLANT LINES OF SORTED IN m FOR FURTHER USE

m = []
for i in slanting2:
        m.append((i[3]-i[1])/(i[2]-i[0]))

count = 0


# SLANTING LINES ARE PRESENT IN SETS OF SAME SLOPE, SO APPEND IN slanting3[]    # INSTEAD OF TAKING MEAN TO ELIMINATE DUPLICATES(as done in horizontal/vertical) USING THIS PROPERTY OF THE DATA
# ONLY ONCE WHEN SLOPE CHANGES

slanting3 = []
try:
    slanting3.append(slanting2[0])                                              # PREVENT THE COMAPARISION OF indexing 0 and "-1"                    
except:
    pass

for i in slanting2:
    try:
        if(m[count] <> m[count-1]):                                             # APPENDING THE VECTOR TO slanting3 WHEN SLOPE CHANGES
            slanting3.append(i)
        count += 1
    except:
        pass
             

# APPLYING SAME SET OF FILTERS AND SORTING FOR VERTICAL LINES AS DONE FOR HORIZONTAL LINES

vertical2 = []
size = len(vertical)
c = 0
x = 0
count = 0

while(c<size):
    while(count<c+6):
        try:
            x += vertical[count][0]
        except:
            pass
        count += 1
    x /= 6
    vertical2.append(x)
    x = 0
    c += 6

size = lambda vector: vector[1]
vertical2.sort(key=size, reverse=True)

horizontal3 = []
horizontal3 = horizontal2                                                       # COPYING THE LIST  horizontal2 IN horizonatl3 FOR MAKING THE OOK ASTHETICALY NICE

vertical3 = []
vertical3 = vertical2
    
# STORING ALL TYPES OF LINES IN A SINGLE VAR tog1

tog1 = []

for i in horizontal3:                                                           
    tog1.append(i)
    
for i in vertical3: 
    tog1.append(i)

for i in slanting3:
    tog1.append(i)
    

# FOR THE STARTING POINT OF THE FIRST LINE DIFFERENCE BETWEEN y CO-ORDINATE
    # AND x CO-ORDINATE IS MAXIMUM AS AT THAT Pt. y IS MAX. AND x IS MIN.
    # WE DETECT THE FIRST LINE USING THIS CONCEPT
    
# NOW WE TAKE DIFFERENCE BETWEEN x2 OF LAST APPENDED LINE AND x1 OF ALL LEFT-
    # OVERS AND SAME FOR y
    # THE LINE FOR WHICH SUMMATION OF THESE TWO DIFFERENCES WILL BE MIN. WILL
    # BE THE NEXT LINE AS THERE CO-ORDINATES (x2,y2) OF THE COMPLETED LINE AND
    # (x1,y1) OF THE COMING ONE WILL BE MINIMUM
    # USING THIS CONCEPT WE SORT THE LINES IN ORDER
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
        tog1[count] = np.append(tog1[count],abs(((x-tog1[count][0])+
            (y-tog1[count][1]))*1.0))
    count += 1

size = lambda vector : vector[4]
tog1.sort(key=size)

def dist(a):
    return np.sqrt((a[0]-a[2])**2 + (a[1]-a[3])**2)
    


# inst[] IS LIST CONTAING INFO ABOUT EACH LINE IN ORDER 
    # THIS SET OF INSTRUCTIONS WILL BE USED TO SEND TO AURDINO
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
    

