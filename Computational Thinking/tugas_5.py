# Soal 1 - Nilai dan Kelulusan 50 Mahasiswwa
# Menyimpan input data nilai 50 mahasiswa, dan menghitung banyaknya mahasiswa yang lulus

# KAMUS
# nilai : array [0 ... 49] of char
# tidak_lulus, lulus, i : int

# ALGORITMA
nilai = [input(f"masukkan nilai mahasiswa ke-{i+1}: ") for i in range(50)]

tidak_lulus = 0
for i in range(50):
    if((nilai[i] == 'D') or (nilai[i] == 'E')):
        tidak_lulus += 1

lulus = 50 - tidak_lulus
print(f"mahasiswa lulus: {lulus}")
print(f"mahasiswa tidak lulus: {tidak_lulus}")















# Soal 2 - Nilai Terkecil Elemen Array
# Mencari nilai terkecil dari elemen suatu array dan menuliskannya ke layar

# KAMUS
# T : array [0 ... N-1] of float 
# T_min : float
# N, i : int

# ALGORITMA
N = int(input("jumlah elemen array: "))
T = [float(input(f"elemen T_{i+1}: ")) for i in range(N)]

T_min = T[0]
for i in range(N):
    if(T[i] < T_min):
        T_min = T[i]

print(f"nilai terkecil elemen array T: {T_min}")

















# Soal 3 - Penjumlahan 2 Buah Vektor
# Menjumlahkan 2 buah vector integer dengan 5 buah elemen dan menuliskan hasilnya ke layar

# KAMUS
# U, V, W : array [0 ... 4] of int
# i : int

# ALGORITMA
V = [int(input(f"masukkan vektor V_{i}: ")) for i in range(5)]
U = [int(input(f"masukkan vektor U_{i}: ")) for i in range(5)]

W = [(V[i] + U[i]) for i in range(5)]

print(f"hasil penjumlahan vektor W = (V + U) = {W}")