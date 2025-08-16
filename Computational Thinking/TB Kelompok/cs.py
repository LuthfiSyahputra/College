import csv
import random


DEF_DATABASE_SIZE = 10000

# STATUS
STATUS_VALID        = 0
STATUS_VALID_UPDATE = -1

STATUS_INVALID      = -2
STATUS_ERROR        = -3


LOCATION_CODE_NULL = int(0)

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

CARD_NULL = [CARD_ID_DEF, CARD_NAME_DEF, CARD_BALANCE_DEF, CARD_STATUS_DEF, CARD_HISTORY_DEF]


def cardDatabase_read(filename = "cardDatabase.csv", delimiter:str = ","):
    file       = open(filename, "r+", newline = "")
    dataReader = csv.reader(file, delimiter=delimiter, lineterminator="\n")
    database = [
        [
            int  (row[CARD_ID]),
            str  (row[CARD_NAME]), 
            float(row[CARD_BALANCE]), 
            int  (row[CARD_STATUS]), 
            int  (row[CARD_HISTORY])
        ] for row in dataReader
    ]
    file.close()


    return database

def card_search(cardDatabase, cardID: int):
    for i in range(len(cardDatabase)):
        if(cardDatabase[i][CARD_ID] == cardID): return cardDatabase[i]

    return CARD_NULL


def card_info(card):
    if(card == CARD_NULL):
        print(f"[ERROR] card_info(): Kartu tidak terbaca/Tidak ada")
        return STATUS_ERROR
    

    print(f"Nama Pengguna: {card[CARD_NAME]}")
    print(f"Status kartu: {card[CARD_STATUS]}")
    print(f"Histori terakhir: {card[CARD_HISTORY]}")
    print(f"\nSaldo: Rp. {card[CARD_BALANCE]}")

    return STATUS_VALID

def card_reg(cardDatabase, databaseSize):
    name    = str(input("Masukkan nama pengguna"))
    balance = float(input("Maukkan saldo awal: Rp. "))

    cardID = random.randint(1, databaseSize)
    while(card_search(cardDatabase, cardID) != CARD_NULL):
        # print(f"[{i}/{databaseSize}] found ID: {cardID}")
        cardID = random.randint(1, databaseSize)

    return [int(cardID), str(name), float(balance), CARD_STATUS_DEF, CARD_HISTORY_DEF]


def cardDatabase_update(cardDatabase, filename = "cardDatabase.csv", delimiter = ","):
    file       = open(filename, "w+")
    filewriter = csv.writer(file, delimiter = delimiter, lineterminator="\n")

    # Tulis database baru (overwrite)
    for row in range(len(cardDatabase)):
        filewriter.writerow(cardDatabase[row])

    file.close()
    return STATUS_VALID


def card_balance(card, amount: float):
    return card[CARD_BALANCE] + amount

def card_topup(card):
    print(f"Nama pengguna: {card[CARD_NAME]}. Saldo saat ini: Rp. {card[CARD_BALANCE]}")
    amount = float(input("Masukkan jumlah top-up yang ingin dimasukkan: Rp. "))

    if(amount < 0):
        print("Jumlah top-up tidak valid, Transaksi gagal")
        return STATUS_INVALID
    else:
        card[CARD_BALANCE] = card_balance(card, amount)
        return STATUS_VALID_UPDATE

def card_delete(card, cardDatabase: list):
    if  (card == CARD_NULL):               return STATUS_ERROR
    elif(card_info(card) != STATUS_VALID): return STATUS_ERROR

    prompt = str(input("Anda yakin ingin menghapus kartu anda (y/n): "))
    if((prompt == 'y') or (prompt == 'Y')):
        cardDatabase.remove(card)
        return STATUS_VALID_UPDATE
    else:
        return STATUS_INVALID


# Opsi Menu Mesin ATM E-Money
MENU_INFO  = 0
MENU_REG   = 1
MENU_TOPUP = 2
MENU_DEL   = 3
MENU_EXIT  = 4

card_menu = [
    "Info",
    "Registrasi",
    "Top-up Saldo",
    "Delete",
    "Exit"
]

def menuInput(menu, startNum: int) -> int:
    for i in range(len(menu)):
        print(f"\t[{i + startNum}]: {menu[i]}")
    
    menuCode = int(input(f"Pilih opsi yang ada ({startNum}~{startNum + len(menu) - 1}): ")) - startNum
    if((menuCode < 0) or (menuCode >= len(menu))):
        return -1
    else:
        return menuCode

def card_management(cardDatabase: list, databaseFile: str):

    menu = 0
    card = CARD_NULL
    while(menu != MENU_EXIT):
        print("\nSelamat datang di mesin pengelola E-Money.")
        status = STATUS_INVALID
        menu   = menuInput(card_menu, 1)

        if((menu == MENU_INFO) or (menu == MENU_REG) or (menu == MENU_DEL)):
            for i in range(1, 6):
                card = card_search(cardDatabase, int(input(f"[{i}/6] Silahkan tempelkan kartu E-Money anda. cardID: ")))
                if(card != CARD_NULL): break
        

        if(menu == MENU_INFO):
            status = card_info(card)
        
        elif(menu == MENU_TOPUP):
            status = card_topup(card)

        elif(menu == MENU_DEL):
            status = card_delete(card, cardDatabase)
            if(status == STATUS_VALID): print("Kartu berhasil dihapus")
            else: print("Gagal menghapus kartu")

        elif(menu == MENU_REG):
            card = card_reg(cardDatabase, DEF_DATABASE_SIZE)
            if(card == CARD_NULL): print("Registrasi kartu gagal")
            else: 
                cardDatabase.append(card)
                status = STATUS_VALID_UPDATE

        # Post-Processing
        if(status == STATUS_VALID_UPDATE):
            cardDatabase_update(cardDatabase, filename = databaseFile)

        elif((status == STATUS_INVALID) or (status == STATUS_ERROR)): 0



cardDatabaseDefault = [
    # [(0) cardID, (1) nama pengguna, (2) saldo, (3) status_kartu, (4) riwayat (Kode Lokasi)]

    [int(120), str("Luthfi"), float(225000), int(0), LOCATION_CODE_NULL],

    [ 231, "Husen", 135000.0, 0, LOCATION_CODE_NULL],
    [ 735, "Intan", 152590.0, 0, LOCATION_CODE_NULL],
    [2910, "Rafi" ,      0.0, 0, LOCATION_CODE_NULL],
    [2924, "Rafa" ,      0.0, 0, LOCATION_CODE_NULL],
    [4336, "Rafo" ,      0.0, 0, LOCATION_CODE_NULL],
    [1902, "Rafu" ,      0.0, 0, LOCATION_CODE_NULL],
    [1902, "Rafu" ,      0.0, 0, LOCATION_CODE_NULL],
    [1902, "Rafu" ,      0.0, 0, LOCATION_CODE_NULL],
    [1902, "Rafu" ,      0.0, 0, LOCATION_CODE_NULL],
    [1902, "Rafu" ,      0.0, 0, LOCATION_CODE_NULL],
]

cardDatabase_update(cardDatabaseDefault)

