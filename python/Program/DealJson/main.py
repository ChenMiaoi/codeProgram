import os
import json

PATH_S = r'./save.txt'
PATH_D = r'./data.json'
MAX_LEN = 100

def run_code(code):
    save_path = PATH_S
    data_path = PATH_D
    with open(save_path,'a+',encoding="utf-8") as fw:
        with open(data_path, 'r', encoding="utf-8") as file:
            for line in file:
                line = json.loads(line) # 将json转化为字典
                # print(line)
                for key, value in line.items():
                    if len(value) > MAX_LEN or len(key) > MAX_LEN:
                        print("{ " + key + ", \n" + value + " }")
                        # fw.write(r"{ " + key + ", \n" + value + " }\n")
                    else:
                        print("{ " + key + ", " + value + " }")
                        # fw.write(r"{ " + key + ", " + value + " }\n")
                # fw.write(r"\n-----------------------------------------\n")
                print("\n-----------------------------------------\n")

if __name__ == "__main__":
    run_code(r'')