import jieba
import os
import math

word_text = {}
word_texts = []
PATH = r"D:\GitWork\GitHub\Python\Program\TF-IDF\data"

def AccessNumber(path) :
    files = os.listdir(path)
    for file in files:
        if os.path.isfile(path + "\\" + file):
            text = open(path + "\\" + file, 'r', encoding = "utf-8").read()
            # print(text)
            words = jieba.lcut_for_search(text)
            for i in range(0, len(words) - 1):
                if words[i] == '，' or words[i] == ',' or words[i] == '“' or \
                        words[i] == '”' or words[i] == '、' or words[i] == '\n' \
                        or words[i] == ' ' or words[i] == '\t' or words[i] == '（' or words[i] == '）':
                    words[i] = '空'
            for key in words:
                if key == "空":
                    words.remove(key)
            temp_dict = {}
            for word in words:
                if word not in word_text:
                    word_text[word] = 1
                else:
                    word_text[word] = word_text[word] + 1
                if word not in temp_dict:
                    temp_dict[word] = 1
                else:
                    temp_dict[word] = temp_dict[word] + 1
            word_texts.append(temp_dict)
        # print(word_text)
    # print(word_texts)
    return word_texts, word_text

def ShowFileWord(path, single_file_word_dict):
    '''
        TODO:
            获取PATH路径下的文件名作为行首，依次对single_file_word_dict进行展示
    '''
    files = os.listdir(path)
    for file, word_dict in zip(files, single_file_word_dict):
        print(file + ": ")
        for key, value in word_dict.items():
            print("{0} ==> {1}".format(key, value))
        # print(word_dict)
        print()

def GetTF(path, word, single_file_word_dict):
    '''
        TODO:
            TF计算公式：
                TF = word_count / file_word_count
    '''
    TF = []
    files = os.listdir(path)
    for file, word_dict in zip(files, single_file_word_dict):
        file_word_count = 0
        for value in word_dict.values():
            file_word_count = file_word_count + value
        if word in word_dict:
            print("{0} in the 《{1}》 has {2} times".format(word, file, word_dict[word]))
            print(" ==> the TF is {:.2f}%".format(word_dict[word] / file_word_count * 100))
            TF.append(word_dict[word] / file_word_count)
            print()
        else:
            TF.append(0.0)
    return TF

def GetIDF(path, word, single_file_word_dict):
    '''
        TODO:
            IDF计算公式：
                IDF = log(file_count / (word_file_count + 1))
    '''
    files = os.listdir(path)
    file_count = 0
    word_file_count = 0
    for file, word_dict in zip(files, single_file_word_dict):
        file_count = file_count + 1
        if word in word_dict:
            word_file_count = word_file_count + 1
    return math.log10(file_count / (word_file_count + 1))

def GetTF_IDF(path, TF, IDF):
    TF_IDF = {}
    files = os.listdir(path)
    for file, singleTF in zip(files, TF):
        if singleTF != 0:
            print("the 《{0}》's TF-IDF is: {1}".format(file, singleTF * IDF))
            TF_IDF[file] = singleTF * IDF
    return TF_IDF

def SortTF_IDF(TF_IDF):
    '''
        TODO:
            对所有的TF-IDF进行排序，取出前五个作为相关性最高的文档
    '''
    sort_list = sorted(TF_IDF.items(), key = lambda x : x[1], reverse = True)
    for i in range(0, 5):
        print("《{0}》's TF-IDF is ==> {1}".format(sort_list[i][0], sort_list[i][1]))

if __name__ == "__main__":
    single_file_word_dict, all_file_word_dict = AccessNumber(PATH)
    # print(len(single_file_word_dict))
    # print(len(all_file_word_dict))

    # ShowFileWord(PATH, single_file_word_dict)
    word = input("请输入您要查询的单词: ")
    TF = GetTF(PATH, word, single_file_word_dict)
    # print(TF)
    IDF = GetIDF(PATH, word, single_file_word_dict)
    # print(IDF)
    TF_IDF = GetTF_IDF(PATH, TF, IDF)
    SortTF_IDF(TF_IDF)