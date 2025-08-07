import msvcrt

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
p_tarif_km = [500, 1000, 1500, 2000, 2500, 3000]
p_tipe     = ["mobil", "mobil bak/minivan", "truk mini", "truk", "truk roda 6", "truk gandeng"]
p_berat    = [2000, 3000, 5000, 7500, 9000, 12000]
p_tinggi   = [3.5, 3.5, 5, 6, 6, 7]


kks = 0

# card Database
card_database = [
    # [cardID, nama pengguna, saldo, status_kartu , riwayat, km]

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
    [0   , ""     ,      0.0, 0, "", 0.0] # End of database
]


# if(card_database[.][0] == inp): print(f"ketemu {card_database[.][1]}")
# if(card_database[n][0] == inp): print(f"ketemu {card_database[0][1]}")

matikan_mesin    = False
panggilPetugas   = False
deteksiKendaraan = False

while(matikan_mesin == False):

    if(msvcrt.kbhit() == True):
        state = int.from_bytes(msvcrt.getch())

        match(state):
            case 27: matikan_mesin    = True
            case 13: deteksiKendaraan = True
            case 49: panggilPetugas   = True
            # case _: print(f"state: {state}")       


    if(panggilPetugas == True):
        print("Petugas dipanggil")
        # kode panggil petugas

    # ALGORITMA UTAMA
    if(deteksiKendaraan == True):
        print("Kendaraan terdeteksi")

        # input kendaraan
        gol     = int(input("Golongan Kendaraan (1 ~ 6): ")) - 1
        if(gol > 5 or gol < 0):
            print("Golongan Invalid")
            break

        berat   = float(input("Berat Kendaraan (kg): "))
        tinggi  = float(input("Tinggi kendaraaan (m): "))
        reg_num = str(input("Nomor registrasi kendaraan (OPSIONAL): "))
        
        # BASE PRICE
        basePrice = p_tarif_km[gol]

        # denda kelebihan beban senilai denda = tarif_gol/km * (beban_lebih / (10% * beban_max))
        if(berat > p_berat[gol]): basePrice = basePrice + (p_tarif_km[gol] * ((berat - p_berat[gol]) / (p_berat[gol] / 10)))

        # Pintu Tol
        lokasi  = str(input(f"Lokasi pintu tol {_lokasi}: "))
        pintu   = bool(input("Gerbang pintu tol (0: masuk, 1: keluar): "))
        arah    = bool(input("Arah jalan tol (0: backward, 1: forward): "))


        # ALGORITMA PENCARIAN LOKASI
        k = 0
        is_found = False
        while(_lokasi[k][1] != ""):
            if(_lokasi[k][1] == lokasi): 
                is_found = True
                break
            else: k += 1
        
        if (is_found == True): lokasi_km = float(_lokasi[k][0] if (arah == True) else - _lokasi[k][1])
        else: 
            print("Lokasi tidak ditemukan")
            break

        # Sub-Program E-Toll
        is_valid = False
        card_i = 0
        for i in range(1, 6):
            cardID  = int(input(f"[{i}/6] Tempelkan kartu E-Toll. cardID: "))
        
            # Algoritma pencarian cardID
            is_found = False
            card_i = 0
            while((card_database[card_i][0] != 0) and (is_found == False)):
                if (card_database[card_i][0] == cardID): is_found = True
                else: card_i += 1
                print(f"{card_database[card_i][0]}: {cardID}")
            
            

            if(is_found == False):
                print(f"[ERROR] Kartu E-Toll tidak ditemukan cardID: {cardID}. Silahkan coba lagi")

            else: # jika cardID ditemukan
                print(f"[{cardID}] {card_database[card_i][1]}  saldo: Rp. {card_database[card_i][2]}  status: {card_database[card_i][4]} km")
                
                if((card_database[card_i][4] == "") and (pintu == 1)):
                    print(f"Tidak ada riwayat masuk kartu [{card_database[card_i][0]}]: {card_database[card_i][1]}")

                elif(card_database[card_i][3] == -1):
                    print(f"Kartu tidak berfungsi / expired")

                else:
                    is_valid = True

            # jika kartu valid
            if(is_valid == True): break

        # pembayaran
        biaya = float(0)
        if(is_valid == True):
            # Pintu Masuk tol
            if(pintu == False):
                card_database[card_i][4] = lokasi
                card_database[card_i][5] = lokasi_km

            # Pintu keluar tol
            else:

                # denda putar balik
                if(arah != (card_database[card_i][5] > 0)):
                    biaya = biaya + (_lokasi[_lokasi.__len__() - 1] * basePrice * 2)

                # biaya
                biaya = biaya + abs((lokasi_km.__abs__() - card_database[card_i][5].__abs__()) * basePrice)


                if(card_database[card_i][2] < biaya):
                    print("Saldo tidak cukup")
                    is_valid = False
                else: 
                    card_database[card_i][2] -= biaya
        

        # buka pintu
        if(is_valid == True):
            print(f"Buka Gerbang Tol. Pembayaran berasil, sisa saldo: Rp {card_database[card_i][2]}")
        else:
            print("Transaksi gagal. Petugas dipanggil")
            panggilPetugas = True


    deteksiKendaraan = False

   

print("Mesin Dimatikan")



