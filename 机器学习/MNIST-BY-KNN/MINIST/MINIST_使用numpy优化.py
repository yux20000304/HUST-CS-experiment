# -*- coding:utf-8 -*-

import operator
import struct
import numpy as np

# 训练集
train_images_idx3_ubyte_file = 'train-images.idx3-ubyte'
# 训练集标签
train_labels_idx1_ubyte_file = 'train-labels.idx1-ubyte'
# 测试集
test_images_idx3_ubyte_file = 't10k-images.idx3-ubyte'
# 测试集标签
test_labels_idx1_ubyte_file = 't10k-labels.idx1-ubyte'


def decode_idx3_ubyte(idx3_ubyte_file):
    bin_data = open(idx3_ubyte_file, 'rb').read()

    # 解析文件头信息，依次为魔数、图片数量、每张图片高、每张图片宽
    offset = 0          #序号
    fmt_header = '>iiii'
    magic_number, num_images, num_rows, num_cols = struct.unpack_from(fmt_header, bin_data, offset)
    print
    '魔数:%d, 图片数量: %d张, 图片大小: %d*%d' % (magic_number, num_images, num_rows, num_cols)

    # 解析数据集
    image_size = num_rows * num_cols
    offset += struct.calcsize(fmt_header)
    fmt_image = '>' + str(image_size) + 'B'
    images = np.empty((num_images, num_rows, num_cols))
    for i in range(num_images):
        if (i + 1) % 10000 == 0:
            print
            '已解析 %d' % (i + 1) + '张'
        images[i] = np.array(struct.unpack_from(fmt_image, bin_data, offset)).reshape((num_rows, num_cols))
        offset += struct.calcsize(fmt_image)
    return images


def decode_idx1_ubyte(idx1_ubyte_file):
    bin_data = open(idx1_ubyte_file, 'rb').read()

    # 解析文件头信息，依次为魔数和标签数
    offset = 0
    fmt_header = '>ii'
    magic_number, num_images = struct.unpack_from(fmt_header, bin_data, offset)
    print
    '魔数:%d, 图片数量: %d张' % (magic_number, num_images)

    # 解析数据集
    offset += struct.calcsize(fmt_header)
    fmt_image = '>B'
    labels = np.empty(num_images)
    for i in range(num_images):
        if (i + 1) % 10000 == 0:
            print
            '已解析 %d' % (i + 1) + '张'
        labels[i] = struct.unpack_from(fmt_image, bin_data, offset)[0]
        offset += struct.calcsize(fmt_image)
    return labels


def classify(point, dataSet, labels, k=3):

    if isinstance(point, (list, tuple)):  # 类型转换
        point = np.array(point)
    if isinstance(dataSet, (list, tuple)) :
        dataSet = np.array(dataSet)
    if isinstance(labels, (list, tuple)) :
        labels = np.array(labels)


    dataSize = dataSet.shape[0] # 数组行数 （行，列）
    pointArray = np.tile(point, (dataSize, 1))   # 扩充数组  tile(原数组, (行重复次数, 列重复次数))
    subArray = pointArray - dataSet   # 矩阵减法
    sqrtArray = subArray ** 2   # 每个元素平方

    """
    sum
    当axis为1时,是压缩列,即将每一行的元素相加,将矩阵压缩为一列
    当axis为0时,是压缩行,即将每一列的元素相加,将矩阵压缩为一行
    None时 所有元素相加
    """
    sumArray = sqrtArray.sum(axis=1)
    lenArray = sumArray ** 0.5  # 每个元素开方
    sortArray = lenArray.argsort() # 按从小到大排序后返回 排序前的下标 ，eg:[300,0,400] 返回  [1, 0, 2]


    """
        unique      统计重复次数  返回值类似 ("X","Y"), (3, 1)
        zip         同步遍历多个可迭代对象  返回 ("X", 3) , ("Y", 1)
        max         求最大值，key 传一个函数，dict 传 dict.get, 多层列表可转lambda x: x[n] 返回 ("X", 3)
        [labels[index] for index in sortArray[:4]
                    求最小k个距离的样本的分类
        距离最小k个点中的分类的频率最高的
    """
    return max(zip(*np.unique([labels[index] for index in sortArray[:k]], return_counts=True)), key=lambda x: x[1])[0]


if __name__ == '__main__':
    #解译图片信息
    train_images = decode_idx3_ubyte(train_images_idx3_ubyte_file)
    train_labels = decode_idx1_ubyte(train_labels_idx1_ubyte_file)
    test_images = decode_idx3_ubyte(test_images_idx3_ubyte_file)
    test_labels = decode_idx1_ubyte(test_labels_idx1_ubyte_file)

    m = 60000  # 创建一个读入数据的数组，进行所有图片信息的记录
    trainingMat = np.zeros((m, 784))  # 所有图片信息数组置为零，784=28*28

    # 文件名下划线_左边的数字是标签
    for i in range(m):
        for j in range(28):
            for k in range(28):
                trainingMat[i, 28 * j + k] = train_images[i][j][k]  #读取第i幅训练图信息
    errorCount = 0.0       #错误数计数器
    mTest = 100           #测试数据量

    for i in range(mTest):
        classNumStr = test_labels[i]
        vectorUnderTest = np.zeros(784)         #测试图读取器清0
        for j in range(28):
            for k in range(28):
                vectorUnderTest[28 * j + k] = test_images[i][j][k]  # 读取第i幅测试图

        Result = classify(vectorUnderTest, trainingMat, train_labels, 3)
        print("识别结果：%d 正确答案：%d" % (Result, classNumStr))
        if (Result != classNumStr):
            errorCount += 1.0
            print("错误")
    print("\n错误数： %d" % errorCount)
    print("\n错误率： %f" % (errorCount / float(mTest)))
    print('数据处理结束')