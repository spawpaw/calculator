import sys

if __name__ == '__main__':
    # 如果传入了参数
    if len(sys.argv)>0:
        eval(sys.argv[0])
    else:
        str = raw_input("please input your expression: ")
        eval(str)
