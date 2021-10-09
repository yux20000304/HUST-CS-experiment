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
    offset = 0
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


def classify(inX, dataset, labels, k):
    datasetsize = dataset.shape[0]
    ###以下距离计算公式
    diffMat = np.tile(inX, (datasetsize, 1)) - dataset
    sqDiffMat = diffMat ** 2
    sqDistances = sqDiffMat.sum(axis=1)
    distances = sqDistances ** 0.5
    ###以上是距离计算公式
    # 距离从大到小排序，返回距离的序号
    sortedDistIndicies = distances.argsort()
    # 字典
    classCount = {}
    # 前K个距离最小的
    for i in range(k):
        # sortedDistIndicies[0]返回的是距离最小的数据样本的序号
        # labels[sortedDistIndicies[0]]距离最小的数据样本的标签
        voteIlabel = labels[sortedDistIndicies[i]]
        # 以标签为key,支持该标签+1
        classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1
    # 排序
    sortedClassCount = sorted(classCount.items(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]


if __name__ == '__main__':
    train_images = decode_idx3_ubyte(train_images_idx3_ubyte_file)
    train_labels = decode_idx1_ubyte(train_labels_idx1_ubyte_file)
    test_images = decode_idx3_ubyte(test_images_idx3_ubyte_file)
    test_labels = decode_idx1_ubyte(test_labels_idx1_ubyte_file)

    m = 60000  # 创建一个读入数据的数组，进行图片信息的记录
    trainingMat = np.zeros((m, 784))  # 置为零

    # 文件名下划线_左边的数字是标签
    for i in range(m):
        for j in range(28):
            for k in range(28):
                trainingMat[i, 28 * j + k] = train_images[i][j][k]
    errorCount = 0.0
    mTest = 10000

    for i in range(mTest):
        classNumStr = test_labels[i]
        vectorUnderTest = np.zeros(784)
        for j in range(28):
            for k in range(28):
                vectorUnderTest[28 * j + k] = test_images[i][j][k]  # 第i幅测试图

        Result = classify(vectorUnderTest, trainingMat, train_labels, 3)
        print("识别结果：%d 正确答案：%d" % (Result, classNumStr))
        if (Result != classNumStr):
            errorCount += 1.0
            print("错误")
    print("\n错误数： %d" % errorCount)
    print("\n错误率： %f" % (errorCount / float(mTest)))
    print('数据处理结束')