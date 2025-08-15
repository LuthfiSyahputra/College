import msvcrt

# KONSTANTA
ENTRANCE  = 0
EXIT = 1

FORWARD  = 0
BACKWARD = 1

# STATUS
STATUS_VALID = 0
STATUS_INVALID = -1

STATUS_ERROR = -2 

# Lokasi pintu tol
LOCATION_ABS_DISTANCE = 0
LOCATION_POS_NAME = 1
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


# KONSTANTA DAN PERSYARATAN MINIMUM KENDARAAN per GOLONGAN
vehicle_tariff_km = [500, 1000, 1500, 2000, 2500, 3000]
vehicle_type      = ["mobil", "mobil bak/minivan", "truk mini", "truk", "truk roda 6", "truk gandeng"]
vehicle_maxWeight = [2000, 3000, 5000, 7500, 9000, 12000]
vehicle_maxHeight = [3.5, 3.5, 5, 6, 6, 7]



# card Database
CARD_ID      = 0
CARD_NAME    = 1
CARD_BALANCE = 2
CARD_STATUS  = 3
CARD_HISTORY = 4
CARD_DIST    = 5

CARD_NULL = [0, "", 0.0, 0, "", 0.0]
cardDatabase = [
    # [(0) cardID, (1) nama pengguna, (2) saldo, (3) status_kartu, (4) riwayat, (5) km]

    [int(120), str("Luthfi"), float(225000), int(0), str(""), float(0)],

    [ 231, "Husen", 135000.0, 0, "", 0.0],
    [ 735, "Intan", 152590.0, 0, "", 0.0],
    [2910, "Rafi" ,      0.0, 0, "", 0.0], # End of database
    [2924, "Rafa" ,      0.0, 0, "", 0.0], # End of database
    [4336, "Rafo" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    [1902, "Rafu" ,      0.0, 0, "", 0.0], # End of database
    CARD_NULL # End of database
]

# Natural Number
def natural(val):
    if(val < 0): return 0
    else:        return val

def location_search(location: str):
    for dom in range(len(domisili)):
        for i in range(len[_location[dom]]):
            if(_location[dom][i][1] == location): return ((dom * 100) + i)


    print(f"[ERROR] findLocation(): Lokasi tidak ditemukan, lokasi: \"{location}\"")
    return STATUS_ERROR

def route_verificator(card, locationCode, direction):
    
    # Verifikasi arah vektor
    if((card[CARD_DIST] > 0) != (direction == FORWARD)): return STATUS_INVALID
    
    # Verifikasi hasil dS = S' - S0
    S1 = _location[int(locationCode/100)][locationCode % 100]

    S1 = (-1 * direction) * S1

    return 0

    


def card_search(cardDatabase, cardID: int):
    for i in range(len(cardDatabase)):
        if(cardDatabase[i][CARD_ID] == cardID): return cardDatabase[i]
    
    print(f"[ERROR] card_search(): Kartu E-Toll tidak ditemukan cardID: {cardID}. Silahkan coba lagi")
    return CARD_NULL
     

def card_verificator(card, locationCode: int, jenisPintu: bool):
    if(card == CARD_NULL): return STATUS_INVALID

    print(f"[{card[CARD_ID]}] {card[CARD_NAME]}  saldo: Rp. {card[CARD_BALANCE]}  status: {card[CARD_STATUS]}")
    
    # Validitas kartu
    if(card[CARD_STATUS] == -1):
        print(f"[ERROR] card_verificator(): Kartu tidak berfungsi / expired")
        return STATUS_ERROR
    

    # Jika pintu masuk cek apakah kartu dalam penggunaan
    if((jenisPintu == ENTRANCE) and (card[CARD_HISTORY] != "")):
        print("[INVALID] card_verificator(): Kartu telah digunakan untuk masuk dan belum pernah keluar")
        return STATUS_INVALID
        
    # Jika pintu keluar, cek apakah kartu 
    if(jenisPintu == EXIT):
        if(card[CARD_HISTORY] == ""):
            print("[INVALID] card_verificator(): Kartu tidak ada riwayat masuk")
            return STATUS_INVALID
       
        elif(card[CARD_HISTORY] != domisili[ int(locationCode/100)]):
            print("[INVALID] card_verificator(): domisili rute masuk berbeda dengan keluar")
            return STATUS_INVALID
        
    # Kartu berhasil terverifikasi
    return STATUS_VALID

def basePrice_calculator(gol, weight, height):
    if((weight < 0) and (height < 0)):
        print(f"[ERROR] Berat atau tinggi tidak valid. berat: {weight} kg, tinggi: {height}")
        return STATUS_ERROR

    basePrice = vehicle_tariff_km[gol]

    # denda kelebihan beban senilai denda = tarif_gol/km * (beban_lebih / (10% * beban_max))
    if(weight > vehicle_maxWeight): 
        basePrice = basePrice + (vehicle_tariff_km[gol] * ((weight - vehicle_maxWeight[gol]) / (vehicle_maxWeight[gol] / 10)))

    return basePrice


# if(card_database[.][0] == inp): print(f"ketemu {card_database[.][1]}")
# if(card_database[n][0] == inp): print(f"ketemu {card_database[0][1]}")

matikan_mesin    = False
panggilPetugas   = False
deteksiKendaraan = False

while(matikan_mesin == False):

    if(msvcrt.kbhit() == True):
        state = int.from_bytes(msvcrt.getch())

        match(state):
            case 27: matikan_mesin    = True # ESC Key
            case 13: deteksiKendaraan = True # num "1" Key
            case 49: panggilPetugas   = True # Enter/Return Key
            # case _: print(f"state: {state}")       


    if(panggilPetugas == True):
        print("Petugas dipanggil")
        # kode panggil petugas

    # ALGORITMA UTAMA
    if(deteksiKendaraan == True):
        print("Kendaraan terdeteksi")

        # input kendaraan
        reg_num = str(input("Nomor registrasi kendaraan (OPSIONAL): "))
        gol     = int(input("Golongan Kendaraan (1 ~ 6): ")) - 1
        if(gol > 5 or gol < 0):
            print("Golongan Invalid")
            break

        basePrice = basePrice_calculator(
            gol, 
            float(input("Berat Kendaraan (kg): ")),
            float(input("Tinggi kendaraaan (m): "))
        )

        if (basePrice < 0): break


        # Pintu Tol
        gate      = bool(input("Gerbang pintu tol (0: masuk, 1: keluar): "))
        direction = bool(input("Arah jalan tol (0: backward, 1: forward): "))

        # ALGORITMA PENCARIAN LOKASI
        locationCode = -1
        while(locationCode <= 0):
            location  = str(input(f"Lokasi pintu tol {_location}: "))
            locationCode = location_search(location)
            
        LOCATION DISTANCE NEEDS TO BE APPLIED IN VECTOR


        status = STATUS_INVALID

        # E-Toll
        card = 0
        for i in range(1, 6):
            card   = card_search(cardDatabase, int(input(f"[{i}/6] Tempelkan kartu E-Toll. cardID: ")) )
            status = card_verificator(card, locationCode, gate)

            if(status == STATUS_VALID): break
            


        # pembayaran
        biaya = float(0)
        if(status == STATUS_VALID):

            if(gate == ENTRANCE):
                card[CARD_HISTORY] = domisili[int(locationCode/100)]
                card[CARD_DIST]    = _location [int(locationCode/100)][locationCode % 100][LOCATION_ABS_DISTANCE]
                print("Harap berhati-hati di jalan tol, patuhi segala rambu dan aturan lalu lintas. Selamt datang dan semoga sampai tujuan")

            elif(gate == EXIT):

                status = route_verificator(card, locationCode, direction)

                if(status == STATUS_ERROR): break

                # denda putar balik
                if(status == STATUS_INVALID):
                    biaya = biaya + (_location[int(locationCode/100)][-1][LOCATION_ABS_DISTANCE] * basePrice * 2)

                # biaya
                biaya = biaya + abs((location_km.__abs__() - card_database[card_i][5].__abs__()) * basePrice)


                if(card_database[card_i][2] < biaya):
                    print("Saldo tidak cukup")
                    status = STATUS_INVALID
                else: 
                    card_database[card_i][2] -= biaya
        

        # buka pintu
        if(status == STATUS_VALID):
            print(f"Buka Gerbang Tol. Pembayaran berasil, sisa saldo: Rp {card_database[card_i][2]}")
        else:
            print("Transaksi gagal. Petugas dipanggil")
            panggilPetugas = True


    deteksiKendaraan = False

   

print("Mesin Dimatikan")



