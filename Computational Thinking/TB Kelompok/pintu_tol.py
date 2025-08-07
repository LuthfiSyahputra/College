from enum import Enum

class state(Enum):
    idle = 0
    emergency = 1
    detected = 2
    petugas = 3
    exit = 9


class EMoney:
    cardID = int(0)
    balance = float(0)

    flag    = int(0)

    def __init__(self):
        
        pass

    def searchID(self, cardID):
        return 0
    

def panggil_petugas():
    print("Petugas dipanggil")
    return state.idle

def emergency():
    print("[EMERGENCY]")
    return state.idle


def card_scan(arah, gol_kendaraan, berat):
    cardID = int(input("Tempelkan Kartu E-Money. card ID Number: "))


    return 0

def toll_start():
    arah          = input("arah tol [0: timur, 1: barat]: ")
    gol_kendaraan = int(input("GOL Kendaraan: "))
    berat         = float(input("Berat Kendaraan: "))

    card_scan(arah, gol_kendaraan, berat)

    return state.idle

flag = 0

while(flag != state.exit):
    
    match(flag):
        case state.petugas:
            flag = panggil_petugas()
            break

        case state.emergency:
            flag = emergency()
            break

        case state.detected:
            flag = toll_start()


    