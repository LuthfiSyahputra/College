# Latihan 1 - Memasukkan 20 elemen array T dan mengalikannya dengan x 

# KAMUS
# T, x, i : int

# ALGORITMA
T = [int(input(f"masukkan elemen ke-{i}: ")) for i in range (20)]
x = int(input("Masukkan bilangan pengali x: "))

for i in range(20):
    T[i] *= x

print(f"Array T: {T}")