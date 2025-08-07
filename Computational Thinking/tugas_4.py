# Soal 1 - Ranking 3 Bilangan
# Menerima input 3 bilangan dan mengeluarkan output dari urutan terbesar hingga terkecil

# KAMUS
# A, B, C : int

# ALGORITMA
A = int(input("A: "))
B = int(input("B: "))
C = int(input("C: "))

# Swap between A and B
if(B > A):
    temp = A
    A = B
    B = temp

# Karena A dan B sebelumnya telah disortir. Jika (C < B) maka C is guaranteed to be less than A (C < A), 
# Hence the inner conditional (B > A)
if(C > B):
    temp = B
    B = C
    C = temp
    if(B > A):
        temp = A
        A = B
        B = temp

print(f"{A} {B} {C}")







# Soal 2 - Jumlah mahasiswa lulus/tidak lulus
# Menerima input jumlah mahasiswa serta masing-masing nilainya
# dan menghitung jumlah mhs. yang lulus dan tidak lulus

# KAMUS
# N, tidak_lulus : int
# nilai : char

# ALGORITMA
N = int(input("N: "))
tidak_lulus = 0

for i in range(N):
    nilai = input(f"Nilai mahasiswa ke-{i+1}: ")

    if((nilai == 'E') or (nilai == 'F')):
        tidak_lulus += 1

print(f"lulus: {N - tidak_lulus}")
print(f"tidak_lulus: {tidak_lulus}")



# Soal 3 - Lagu Anak Ayam
# Menerima input jumlah anak ayam dan mengeluarkan output lagu anak ayam

# KAMUS
# N, i : int

# ALGORITMA
ayam = int(input("Anak ayam turunlah: "))

# ALGORITMA 1 - menggunakan for loop "decrement", melakukan iterasi dari ayam-1 hingga 1 dan menampilkan i sebagai output
for i in range(ayam-1, 0, -1):
    print(f"mati satu tinggallah {i}")

# ALGORITMA 2 - menggunakan for loop "increment", sisa ayam adalah (ayam - i), dengan i = jumlah ayam yang mati
for i in range(1, ayam):
    print(f"mati satu tinggallah {ayam-i}")

# ALGORITMA 3 - dengan menggunakan wile loop dan memodifikasi variabel [ayam] secara langsung
while(ayam > 1):
    ayam -= 1
    print(f"mati satu tinggallah {ayam}")

print("mati satu tinggal induknya")
