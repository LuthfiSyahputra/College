

# Jarak pintu tol
_lokasi = [
    # [Jarak Absolut, Nama Lokasi]
    [  0.0, "Merak", 355],
    [ 65.0, "Jakarta", 32, 33],
    [110.0, "Bekasi"],
    [145.0, "Purwakarta"],
    [210.0, "Bandung"],
    [420.0, "Semarang"]
]

domisili = ["Jawa", "Sumatra"]
_location = [
[
    # [Jarak Absolut, Nama Lokasi]
    [  0.0, "Merak"],
    [ 65.0, "Jakarta"],
    [110.0, "Bekasi"],
    [145.0, "Purwakarta"],
    [210.0, "Bandung"],
    [420.0, "Semarang"]
],
[
    [0.0, "Aceh"],
    [43.0, "Medan"],
    [128.0, "Sumatra tengah"]
]
]
print(_location[1])


# Persyaratan minimum
p_harga_km = [500.0, 1000.0, 1500.0, 2000.0, 2500.0, 3000.0]
p_tipe     = ["mobil", "mobil bak/minivan", "truk mini", "truk", "truk roda 6", "truk gandeng"]
p_berat    = [2000, 3000, 5000, 7500, 9000, 12000]
p_tinggi   = [3.5, 3.5, 5, 6, 6, 7]

# card Database
cardDatabase = [
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

# lokasi_km = -100
# card_i = 2
# basePrice = p_harga_km[2]

# biaya = 0.0
# biaya = biaya + abs((lokasi_km.__abs__() - card_database[card_i][5].__abs__()) * basePrice)

# print(f"km: {lokasi_km} lok_awal: {card_database[card_i][5]}  biaya: {biaya}")
# print(f"len: {len(_lokasi[0])} {len(_lokasi[1])} {len(_lokasi[2])}")

def arrmod(array):
    return array[1]


array = [[0, 1, 2, 4], [6, 8, 0, 100], [1, 4, 6, 8]]
LOCATION_ABS_DISTANCE = 0

locationCode = 167
# biaya = (_location[int(locationCode/100)][-1][LOCATION_ABS_DISTANCE] * basePrice * 2)

def card_search(cardDatabase, cardID: int):
    for i in range(len(cardDatabase)):
        if(cardDatabase[i][0] == cardID): return cardDatabase[i]
    
    print(f"[ERROR] card_search(): Kartu E-Toll tidak ditemukan cardID: {cardID}. Silahkan coba lagi")
    return 0

for i in range(len(cardDatabase)):
    print(cardDatabase[i])


card = card_search(cardDatabase, 735)
card[2] = 100

print("\n\n")
print(card)
print("\n\n")

for i in range(len(cardDatabase)):
    print(cardDatabase[i])

# print(arrmod(array[1]) != [6, 8, 0, 3])
# print(array[int(189/100)][len(array[int(189/100)]) - 1])
# print(array[-1][2])
# print(_location[int(locationCode/100)][-1][LOCATION_ABS_DISTANCE])