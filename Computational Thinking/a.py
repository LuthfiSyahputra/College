# Latihan 1 - Maksimum 2 Bilangan

# KAMUS
# A, B : int

# ALGORITMA
# A = int(input("Masukkan Bil. A: "))
# B = int(input("Masukkan Bil. B: "))

# if(A >= B):
#     print(f"Bilangan Terbesar adalah A: {A}")
# else:
#     print(f"Bilangan Terbesar adalah B: {B}")


# Latihan 1 loop - Algoritma menghitung jumlah kelipatan 5

# KAMUS 
# N, sum : int

# N = int(input("Masukkan input N: "))
# sum = int(0)

# for i in range(0, N+1, 5):
#     sum += i

# print(f"Jumlah bilangan: {sum}")




# Latihan 2 - Total Hambatan Seri

# KAMUS:
# R1, R2, R3, RT : float

# ALGORITMA
R1 = float(input("Masukkan Hambatan R1: "))
R2 = float(input("Masukkan Hambatan R2: "))
R3 = float(input("Masukkan Hambatan R3: "))

if((R1 < 0) or (R2 < 0) or (R3 < 0)):
    print("Hambatan total tidak bisa dihitung")
else:
    RT = float(R1 + R2 + R3)
    print(f"Hambatan Total :{RT}")















