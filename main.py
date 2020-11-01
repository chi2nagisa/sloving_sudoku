import numpy as np
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow

import sudoku_ui

origen = np.zeros((9, 9), int)


def recursive(x: int, y: int):
    flag = True
    if origen[x][y] == 0:
        # Recircly try one to nine
        for k in range(1, 10):
            flag = True

            # check for row
            for i in range(0, 9):
                if origen[x][i] == k:
                    flag = False

            # check for line
            for i in range(0, 9):
                if origen[i][y] == k:
                    flag = False

            # check for 3 by 3
            x_s = x - x % 3
            y_s = y - y % 3
            for i in range(x_s, x_s + 3):
                for j in range(y_s, y_s + 3):
                    if origen[i][j] == k:
                        flag = False
            if not flag:
                if k != 9:
                    continue
                else:
                    return False
            origen[x][y] = k
            if y + 1 < 9:
                flag = recursive(x, y+1)
            elif x + 1 < 9:
                flag = recursive(x+1, 0)
            else:
                return True
            if not flag:
                origen[x][y] = 0  # 如果尝试失败，复原空位
                continue
            return flag
        return flag
    else:
        if y + 1 < 9:
            flag = recursive(x, y+1)
        elif x + 1 < 9:
            flag = recursive(x+1, 0)
        else:
            return True
        return flag


def main():
    flag = True # Indicator for overlap
    print("请输入一个只由0~9构成的矩阵，并以0代替空白区域")
    for i in range(0, 9):
        numbers = input().split(' ')
        j = 0
        for number in numbers:
            origen[i][j] = int(number)
            j += 1

    # 递归求解
    flag = recursive(0, 0)
    if not flag:
        print("\n\nNo Answer!")
        return

    # output formation
    print("-----------------------")
    for i in range(0, 9):
        for j in range(0, 9):
            print(origen[i][j], end=" ")
            if j % 3 == 2:
                print("|", end="")
        print()
        if i % 3 == 2:
            print("-----------------------")


if __name__ == '__main__':
    # main()
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    ui = sudoku_ui.Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec())
