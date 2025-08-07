

# Jarak pintu tol
_lokasi = [
    # [Jarak Absolut, Nama Lokasi]
    [  0.0, "Merak"],
    [ 65.0, "Jakarta"],
    [110.0, "Bekasi"],
    [145.0, "Purwakarta"],
    [210.0, "Bandung"],
    [420.0, "Semarang"]
]


# Persyaratan minimum
p_harga_km = [500.0, 1000.0, 1500.0, 2000.0, 2500.0, 3000.0]
p_tipe     = ["mobil", "mobil bak/minivan", "truk mini", "truk", "truk roda 6", "truk gandeng"]
p_berat    = [2000, 3000, 5000, 7500, 9000, 12000]
p_tinggi   = [3.5, 3.5, 5, 6, 6, 7]

# card Database
card_database = [
    # [cardID, nama pengguna, saldo, status_kartu , riwayat, km]

    [int(120), str("Luthfi"), float(225000), int(0), str(""), float(0)],

    [ 231, "Husen", 135000.0, 0, "", 0.0],
    [ 735, "Intan", 152590.0, 0, "", -900.0],
    [2910, "Rafi" ,      0.0, 0, "", -10.0], # End of database
    [2924, "Rafa" ,      0.0, 0, "", 0.0], # End of database
    [4336, "Rafo" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [0   , ""     ,      0.0, 0, "", 0.0] # End of database
]

lokasi_km = -100
card_i = 2
basePrice = p_harga_km[2]

biaya = 0.0
biaya = biaya + abs((lokasi_km.__abs__() - card_database[card_i][5].__abs__()) * basePrice)

print(f"km: {lokasi_km} lok_awal: {card_database[card_i][5]}  biaya: {biaya}")