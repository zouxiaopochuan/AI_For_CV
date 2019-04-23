# Finish 2D convolution/filtering by your self.
# What you are supposed to do can be described as "median blur", which means by using a sliding window
# on an image, your task is not going to do a normal convolution, but to find the median value within
# that crop.
#
# You can assume your input has only one channel. (a.k.a a normal 2D list/vector)
# And you do need to consider the padding method and size. There are 2 padding ways: REPLICA & ZERO. When
# "REPLICA" are given to you, the padded pixels are the same with the border pixels. E.g is [1 2 3] is your
# image, the padded version will be [(...1 1) 1 2 3 (3 3...)] where how many 1 & 3 in the parenthesis
# depends on your padding size. When "ZERO", the padded version will be [(...0 0) 1 2 3 (0 0...)]
#
# Assume your input's size of the image is W x H, kernel size's m x n. You may first complete a version
# with O(W·H·m·n log(m·n)) to O(W·H·m·n·m·n)).
# Follow up 1: Can it be completed in a shorter time complexity?
# Follow up 2: Can it be completed in O(W·H·m·n)?
#
# Python version:
# def medianBlur(img, kernel, padding_way):
#     img & kernel is List of List; padding_way a string
#     Please finish your code under this blank
#
import numpy as np
import cv2

def medianBlur(img, kernel, padding_way,padding_size=2):
    img_padded = []
    h,w = img.shape
    kh,kw = kernel.shape
    if padding_way == 'REPLICA':
        img_padded=np.pad(img,padding_size,'edge')
    elif padding_way == 'ZERO':
        img_padded = np.pad(img,padding_size,'constant')

    out_h,out_w = (h+2*padding_size+1-kh),(w+2*padding_size+1-kw)
    img_pooling=np.zeros((out_h,out_w))
    for i in range(out_h):
        for j in range(out_w):
            img_pooling[i][j]=np.median(img_padded[i:i+kh,j:j+kw])

    return img_pooling

if __name__=='__main__':
    img_gray=cv2.imread('lena.jpg',0)

    kernel = cv2.getGaussianKernel(5,1);
    kernel2D = kernel*kernel.T

    print(img_gray.shape)
    print(kernel2D.shape)
    img_padding_REPLICA = medianBlur(img_gray, kernel2D, 'REPLICA')
    img_padding_ZERO = medianBlur(img_gray, kernel2D, 'ZERO')
    img_padding_ZERO = img_padding_ZERO.astype(np.uint8)
    img_padding_REPLICA = img_padding_REPLICA.astype(np.uint8)

    cv2.imshow('img_padding_REPLICA',img_padding_REPLICA)
    cv2.imshow('img_padding_ZERO',img_padding_ZERO)
    key=cv2.waitKey()
    if key==27:
        cv2.destroyAllWindows()




