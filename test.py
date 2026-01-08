import numpy as np 

if __name__ == "__main__":
    # x = []
    # for i in range(9):
    #     for j in range(3):
    #         x.append(0)
    x = np.array([0 for i in range(9) for j in range(3)])
    x = np.reshape(x, (9, 3))
    x[:, 0] = 100
    print(x)
    print("\n")

    x = np.reshape(x, (3, 9))
    print(x)
    print("\n")

