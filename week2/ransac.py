import cv2
import numpy as np
import random

def calculatehomography(cor_p):
    alist = []
    for corr in cor_p:
        p1 = np.mat([corr.item(0),corr.item(1),1])
        p2 = np.mat([corr.item(2),corr.item(3),1])
        a1 = [-p2.item(2) * p1.item(0), -p2.item(2) * p1.item(1), -p2.item(2) * p1.item(2), 0, 0, 0,p2.item(0) * p1.item(0), p2.item(0) * p1.item(1), p2.item(0) * p1.item(2)]
        a2 = [0, 0, 0, -p2.item(2) * p1.item(0), -p2.item(2) * p1.item(1), -p2.item(2) * p1.item(2),
             p2.item(1) * p1.item(0), p2.item(1) * p1.item(1), p2.item(1) * p1.item(2)]
        alist.append(a1)
        alist.append(a2)
    matrix_a = np.mat(alist)#变成矩阵形式 matrix_a是系数矩阵
    u,s,v = np.linalg.svd(matrix_a)#奇异值分解
    h = np.reshape(v[8],(3,3))#选取最小的右奇异值，将其变成3*3矩阵
    h = (1/h.item(8))*h #使单应性矩阵最后一个值为1
    return h

#calculate the distance betweeen point and h
def geometricDistance(corresponse,h):
    p1 = np.transpose(np.mat([corresponse[0].item(0),corresponse[0].item(1),1]))
    p2 = np.transpose(np.mat([corresponse[0].item(2),corresponse[0].item(3),1]))
    diff = p2 - np.dot(h,p1)
    return np.linalg.norm(diff)

def ransacMatching(A,B):
    matcher = cv2.BFMatcher(cv2.NORM_L2, True)
    matches = matcher.match(A[1], B[1])
    cor_p = []
    for match in matches:
        (x1,y1)=A[0][match.queryIdx].pt
        (x2,y2)=B[0][match.trainIdx].pt
        cor_p.append([x1,y1,x2,y2])
    cor_p = np.mat(cor_p)
    maxInliers = []
    finalH = None
    inliers = []

    for j in range(4):
        tem = random.randrange(0,len(cor_p))
        inliers.append(cor_p[tem])

    outliers = cor_p

    for i in range(100):
        print(i)
        h = calculatehomography(inliers)
        for k in range(len(outliers)):
            d = geometricDistance(outliers[k],h)
            if d<100:
                inliers.append(outliers[k])
        if len(inliers)>len(maxInliers):
            maxInliers = inliers
            finalH = h
        #if len(inliers) == len(maxInliers):#当局内点数量不再增加，跳出循环
         #   break
    return finalH, maxInliers, matches

#draw the line between img1 and img2
def drawMatches(img1, img2, kp1, kp2, matches, inliers):
    rows1 = img1.shape[0]
    cols1 = img1.shape[1]
    rows2 = img2.shape[0]
    cols2 = img2.shape[1]

    out = np.zeros((max(rows1, rows2),cols1+cols2,3), dtype='uint8')
    out[0:rows1, 0:cols1, :] = img1
    out[0:rows2, cols1:, :] =img2

    '''
    for i in matches:
        img1_idx = i.queryIdx
        img2_idx = i.trainIdx
        (x1,y1) = kp1[img1_idx].pt
        (x2,y2) = kp2[img2_idx].pt

        if inliers is not None:
            cv2.line(out, (int(x1),int(y1)),(int(x2)+cols1,int(y2)),(0,255,0),1)

        if inliers is None:
            cv2.line(out,(int(x1),int(y1)),(int(x2)+cols1,int(y2)),(255,0,0),1)
    '''
    for i in inliers:
        cv2.line(out, (int(i.item(0)), int(i.item(1))), ((int(i.item(2))) + cols1, int(i.item(3))), (0, 255, 0), 1)
    return out

def run():
    img1 = cv2.imread("image1.jpg")
    img2 = cv2.imread("image2.jpg")

    sift1 = cv2.xfeatures2d.SIFT_create()
    kp1 = sift1.detect(img1,None)
    kp1, des1 = sift1.compute(img1,kp1)

    #find key point and descriptors of img2
    sift2 = cv2.xfeatures2d.SIFT_create()
    kp2 = sift2.detect(img2,None)
    kp2, des2 = sift2.compute(img2, kp2)

    A = []
    B = []
    A.append(kp1)
    A.append(des1)
    B.append(kp2)
    B.append(des2)
    finalH, MaxInliers, matches = ransacMatching(A,B)
    imgout = drawMatches(img1, img2, kp1, kp2, matches, MaxInliers)

    print('final homography', finalH)
    print('final inliers count', len(MaxInliers))
    cv2.imwrite('matchimg.jpg',imgout)
    cv2.imshow('imout', imgout)
    cv2.waitKey()

if __name__ == '__main__':
    run()