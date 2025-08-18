import msvcrt
import cs
import dataLokasi

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
MAX_LOCAL          = 100    # Konstanta besaran kode domisili
LOCATION_CODE_NULL = int(0)

LOCATION_ABS_DISTANCE = 0
LOCATION_POS_NAME = 1

domisili  = dataLokasi.domisili
_location = dataLokasi.location


# KONSTANTA DAN PERSYARATAN MINIMUM KENDARAAN per GOLONGAN
vehicle_tariff_km = [500, 1000, 1500, 2000, 2500, 3000]
vehicle_type      = ["mobil", "mobil bak/minivan", "truk mini", "truk", "truk roda 6", "truk gandeng"]
vehicle_maxWeight = [2000, 3000, 5000, 7500, 9000, 12000]
vehicle_maxHeight = [3.5, 3.5, 5, 6, 6, 7]

# Konstanta default kartu
CARD_ID_DEF      = int(0)
CARD_NAME_DEF    = str("")
CARD_BALANCE_DEF = float(0)
CARD_STATUS_DEF  = int(0)
CARD_HISTORY_DEF = LOCATION_CODE_NULL

# card Database
CARD_ID      = 0
CARD_NAME    = 1
CARD_BALANCE = 2
CARD_STATUS  = 3
CARD_HISTORY = 4

cardDatabase_field = ["CardID", "Nama Pengguna", "Saldo (Rp)", "Status Kartu", "Riwayat (Kode Lokasi)"]
CARD_NULL = [CARD_ID_DEF, CARD_NAME_DEF, CARD_BALANCE_DEF, CARD_STATUS_DEF, CARD_HISTORY_DEF]


def location_search(location: str):
    for dom in range(1, len(domisili)):
        for i in range(len(_location[dom])):
            if(_location[dom][i][1] == location): return ((dom * MAX_LOCAL) + i)


    print(f"[ERROR] findLocation(): Lokasi tidak ditemukan, lokasi: \"{location}\"")
    return LOCATION_CODE_NULL

def route_verificator(card, locationCode):
    if((card[CARD_HISTORY] == LOCATION_CODE_NULL) or (locationCode == LOCATION_CODE_NULL)):
        return STATUS_ERROR

    dS = locationCode - card[CARD_HISTORY]
    
    # Verifikasi arah vektor
    if(((card[CARD_HISTORY] > 0) == (locationCode > 0)) and (dS > 0)): 
        return STATUS_VALID
    else:
        return STATUS_INVALID

    

def card_verificator(card, locationCode: int, jenisPintu: bool):
    if(card == CARD_NULL): 
        print(f"[ERROR] card_search(): Kartu E-Toll tidak ditemukan")
        return STATUS_INVALID

    print(f"[{card[CARD_ID]}] {card[CARD_NAME]}  saldo: Rp. {card[CARD_BALANCE]}  status: {card[CARD_STATUS]}")
    
    # Validitas kartu
    if(card[CARD_STATUS] == -1):
        print(f"[ERROR] card_verificator(): Kartu tidak berfungsi / expired")
        return STATUS_ERROR
    

    # Jika pintu masuk cek apakah kartu dalam penggunaan
    if((jenisPintu == ENTRANCE) and (card[CARD_HISTORY] != LOCATION_CODE_NULL)):
        print("[INVALID] card_verificator(): Kartu telah digunakan untuk masuk dan belum pernah keluar")
        return STATUS_INVALID


    if(jenisPintu == EXIT):
        # Cek apakah kartu pernah tap-in
        if(card[CARD_HISTORY] == LOCATION_CODE_NULL):
            print("[INVALID] card_verificator(): Kartu tidak ada riwayat masuk")
            return STATUS_INVALID
       
        # Cek kesesuaian domisili
        elif(int(card[CARD_HISTORY] / MAX_LOCAL) != int(locationCode / MAX_LOCAL)):
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
    if(weight > vehicle_maxWeight[gol]): 
        basePrice = basePrice + (vehicle_tariff_km[gol] * ((weight - vehicle_maxWeight[gol]) / (vehicle_maxWeight[gol] / 10)))

    return basePrice


DATABASE_DIR = "cardDatabase.csv"

# =========================== PROGRAM UTAMA ==================================
matikanMesin    = False
panggilPetugas   = False
deteksiKendaraan = False
ATM_EMoney       = False

# Inisialisasi database kartu dari file csv
cardDatabase = CARD_NULL
databaseFile = ""
while(cardDatabase == CARD_NULL):
    databaseFile = str(input("Masukkan referensi file untuk database kartu: "))
    if(databaseFile == ""): databaseFile = DATABASE_DIR
    cardDatabase = cs.cardDatabase_read(databaseFile)


while(matikanMesin == False):

    if(msvcrt.kbhit() == True):
        state = int.from_bytes(msvcrt.getch())

        match(state):
            case 27: matikan_mesin    = True # ESC Key
            case 13: deteksiKendaraan = True # Enter/Return Key
            case 49: panggilPetugas   = True # "1" Key
            case 50: ATM_EMoney       = True # "2 Key"
            # case _: print(f"state: {state}")       

    # Pemanggilan Petugas
    if(panggilPetugas == True):
        print("Petugas dipanggil")
        panggilPetugas = False
        # kode panggil petugas

    # E-Money Management
    if(ATM_EMoney == True):
        status = cs.card_management(cardDatabase, databaseFile)
        if(status != STATUS_VALID): panggilPetugas = True

        ATM_EMoney = False



    # ALGORITMA UTAMA
    if(deteksiKendaraan == True):
        print("Kendaraan terdeteksi")

        # ==================== INPUT KENDARAAN ============================
        reg_num = str(input("Nomor registrasi kendaraan (OPSIONAL): "))

        gol     = int(input("Golongan Kendaraan (1 ~ 6): ")) - 1
        if(gol > 5 or gol < 0):
            print("Golongan Invalid")
            panggilPetugas = True
            break

        basePrice = -1
        while(basePrice < 0):
            basePrice = basePrice_calculator(
                gol, 
                float(input("Berat Kendaraan (kg): ")),
                float(input("Tinggi kendaraaan (m): "))
            )


        # ========================== PINTU TOL =================================
        gate      = bool(input("Gerbang pintu tol (0: masuk, 1: keluar): "))
        direction = bool(input("Arah jalan tol (0: forward, 1: backward): "))

        # ALGORITMA PENCARIAN LOKASI
        locationCode = LOCATION_CODE_NULL
        while(locationCode == LOCATION_CODE_NULL):
            location     = str(input(f"Lokasi pintu tol {_location}: "))
            locationCode = (-1 ** direction) * location_search(location)


        print(f"loc: {locationCode}")
        status = STATUS_INVALID


        # =============================== E - MONEY =======================================
        card = CARD_NULL
        for i in range(1, 6):
            card   = cs.card_search(cardDatabase, int(input(f"[{i}/6] Tempelkan kartu E-Toll. cardID: ")) )
            status = card_verificator(card, locationCode, gate)

            if(status == STATUS_VALID): break
            


        # ============================= PEMBAYARAN =========================================
        totalFee = float(0)
        distance = float(0)
        if(status == STATUS_VALID):

            if(gate == ENTRANCE):
                card[CARD_HISTORY] = locationCode
                print("Harap berhati-hati di jalan tol, patuhi segala rambu dan aturan lalu lintas. Selamt datang dan semoga sampai tujuan")

            elif(gate == EXIT):
                status = route_verificator(card, locationCode)

                locationCode       = abs(locationCode)
                card[CARD_HISTORY] = abs(card[CARD_HISTORY])

                # denda putar balik (jarak += 2 * jarak terjauh dalam domisili)
                if(status == STATUS_INVALID):
                    distance += (2 * _location[int(locationCode / MAX_LOCAL)][-1][LOCATION_ABS_DISTANCE])
                    panggilPetugas = True

                # biaya
                S0 = _location[int(card[CARD_HISTORY]/MAX_LOCAL)][card[CARD_HISTORY] % MAX_LOCAL][LOCATION_ABS_DISTANCE]
                S1 = _location[int(locationCode/MAX_LOCAL)][locationCode % MAX_LOCAL][LOCATION_ABS_DISTANCE]

                distance += abs(S1 - S0)
                totalFee += float(distance * basePrice)


                if(card[CARD_BALANCE] >= totalFee):
                    card[CARD_BALANCE] -= totalFee
                    status = STATUS_VALID
                else: 
                    print("Saldo tidak cukup")
                    status = STATUS_INVALID

                card[CARD_HISTORY] = CARD_HISTORY_DEF
        

        # ================================== BUKA PINTU & POST-PROCESSING ===========================
        cs.cardDatabase_update(cardDatabase, databaseFile)
        if(status == STATUS_VALID):
            print(f"Buka Gerbang Tol. Pembayaran berasil, sisa saldo: Rp {card[CARD_BALANCE]}")
        else:
            print("Transaksi gagal. Petugas dipanggil")
            panggilPetugas = True
        
        
        deteksiKendaraan = False

   

if(matikanMesin == True): print("Mesin Dimatikan")



