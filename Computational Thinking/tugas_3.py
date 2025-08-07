# Soal 1 - Beli Kelereng
# Menghitung total biaya yang harus dibayar dalam setiap pembelian kelereng

# KAMUS
# kel_merah, kel_hijau, kel_kuning : int
# harga : int

# ALGORITMA
kel_merah = int(input("Masukkan jumlah kelereng merah: "))
kel_hijau = int(input("Masukkan jumlah kelereng hijau: "))
kel_kuning = int(input("Masukkan jumlah kelereng kuning: "))

harga = int(100 * ((kel_merah * 10) + (kel_hijau * 15) + (kel_kuning * 20)))

print(f"Total harga yang harus dibayar: Rp. {harga}")



# Soal 2 - Tagihan Listrik
# Menghitung total tagihan listrik Pak Dani dalam Sebulan

# KAMUS
# kWh : float
# tagihan : float

kWh = float(input("Masukkan jumlah kWh per bulan: "))

tagihan = kWh * 1444.70

print(f"Total tagihan listrik Pak Dani dalam sebulan: Rp. {tagihan}")



# Soal 3 - Konversi Waktu
# Mengkonversi total durasi waktu ke dalam satuan detik

# KAMUS
# jam, menit, detik : int

# ALGORITMA
jam = int(input("Masukkan durasi dalam satuan jam: "))
menit = int(input("Masukkan durasi dalam satuan menit: "))
detik = int(input("Masukkan durasi dalam satuan detik: "))

detik += (menit * 60) + (jam * 3600)

print(f"Total durasi: {detik} detik")



# Soal 4 - Kasir Sederhana
# Menghitung total harga pesanan dan kembaliannya berdasarkan jumlah pembayaran dari pembeli

# KAMUS
# nasiGoreng, mieGoreng, esTehManis : int
# harga, pembayaran, kembali : float

# ALGORITMA
nasiGoreng = int(input("jumlah pesanan Nasi Goreng: "))
mieGoreng = int(input("jumlah pesanan Mie Goreng: "))
esTehManis = int(input("jumlah pesanan Es Teh Manis: "))

harga = float((nasiGoreng * 18000) + (mieGoreng * 15000) + (esTehManis * 5000))
print(f"Total harga yang harus dibayar: Rp. {harga}")

pembayaran = float(input("Masukkan jumlah uang pembayaran dari pembeli: Rp. "))
kembali = float(pembayaran - harga)

if(kembali >= 0):
    print(f"Jumlah Kembalian: Rp. {kembali}")     # Uang pembayaran cukup
else:
    print(f"Jumlah kekurangan: Rp. {-kembali}")   # Uang pembayaran kurang