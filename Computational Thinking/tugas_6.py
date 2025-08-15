# Soal 1 - Mencari maksimum 3 bilangan

# KAMUS
# A, B, C: float

# Fungsi max3
def max3(A:float, B:float, C:float) -> float:
    # Mencari dan mengeluarkan nilai maksimum dari 3 bilangan

    # KAMUS LOKAL
    # A, B, C : float

    # ALGORITMA
    if  ((A >= B) and (A >= C)): return A 
    elif((B >= A) and (B >= C)): return B
    else                       : return C

# ALGORITMA UTAMA
A = float(input("Maukkan nilai A:"))
B = float(input("Maukkan nilai B:"))
C = float(input("Maukkan nilai C:"))
print(f"Maksimum: {max3(A, B, C)}")






# Soal 2 - Mencari maksimum 3 bilangan
# Mencari maksimum 3 bilangan menggunakan fungsi max2() didalam fungsi max3()

# KAMUS
# A, B, C: float

# Fungsi max2
def max2(A:float, B:float) -> float:
    # Mencari dan mengeluarkan nilai maksimum 2 bilangan

    # KAMUS LOKAL
    # A, B : float

    # ALGORITMA
    if(A >= B): return A
    else      : return B

# Fungsi max3_2
def max3_2(A: float, B: float, C: float) -> float:
    # Mencari dan mengeluarkan nilai maksimum dari 3 bilangan menggunakan fungsi max2

    # KAMUS LOKAL
    # A, B, C : float

    # ALGORITMA
    return max2(A, max2(B, C))

# ALGORITMA UTAMA
A = float(input("Maukkan nilai A:"))
B = float(input("Maukkan nilai B:"))
C = float(input("Maukkan nilai C:"))
print(f"Maksimum: {max3_2(A, B, C)}")



# Soal 3 -  Jarak Tempuh
# Menghitung jarak tempuh berdasarkan input kecepatan(v) dan waktu tempuh(t)

# Fungsi Hitung Jarak
def hitungJarak(v:float, t:float) -> float:
    # Menghitung jarak tempuh dari v, t

    # KAMUS LOKAL
    # v, t : float

    # ALGORITMA
    return v * t

# ALGORITMA UTAMA
v = float(input("Masukkan kecepatan(m/s): "))
t = float(input("Masukkan waktu tempuh(s): "))
print(f"Jarak tempuh: {hitungJarak(v, t)} m")





# Soal 4 - Maksimum Elemen Array
# Mencari dan mengeluarkan nilai elemen maksimum dari suatu array

# KAMUS
# T : array [0 ... N] of int

# Fungsi max array
def maxArray(T:int, N:int) -> int:
    # Mencari nilai elemen maksimum dari suatu array

    # KAMUS LOKAL
    # max, N : int
    # T : array [0 ... N] of int

    # ALGORITMA
    max = T[0]
    for i in range(1, N):
        if(T[i] > max): max = T[i]
    
    return max

# ALGORITMA UTAMA
T = [5, 4, 3, 2, 1]
print(f"Maksimum: {maxArray(T, len(T))}")









# Soal 5 - Mencetak Array
# Mencetak seluruh elemen-elemen dari suatu Array

# KAMUS
# T : array [0 ... N] of int

# Fungsi cetak array
def cetakArray(T:int, N:int) -> None:
    # Mencetak isi elemen-elemen dari suatu array

    # KAMUS LOKAL
    # T : array [0 ... N] of int
    # N : int

    # ALGORITMA
    if(N == 0):
        print("Array kosong")
        return
        
    for i in range(N):
        print(f"[{i}]: {T[i]}")

# ALGORITMA UTAMA
T = [5, 4, 3, 2, 1]
cetakArray(T, len(T))

