import msvcrt
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

# Membaca file csv dan mengeluarkan matrix database kartu
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

    if(len(database) == 0): database = CARD_NULL
    return database

# Update file csv dari database kartu
def cardDatabase_update(cardDatabase, filename = "cardDatabase.csv", delimiter = ","):
    file       = open(filename, "w+")
    filewriter = csv.writer(file, delimiter = delimiter, lineterminator="\n")

    # Tulis database baru (overwrite)
    for row in range(len(cardDatabase)):
        filewriter.writerow(cardDatabase[row])

    file.close()
    return STATUS_VALID

# Mencari akun/kartu pengguna berdasarkan cardID, mengeluarkan data kartu (array)
def card_search(cardDatabase, cardID: int):
    for i in range(len(cardDatabase)):
        if(cardDatabase[i][CARD_ID] == cardID): return cardDatabase[i]

    return CARD_NULL

# Print info dari kartu
def card_info(card):
    if(card == CARD_NULL):
        print(f"[ERROR] card_info(): Kartu tidak terbaca/Tidak ada")
        return STATUS_ERROR
    

    print(f"Nama Pengguna: {card[CARD_NAME]}")
    print(f"Status kartu: {card[CARD_STATUS]}")
    print(f"Histori terakhir: {card[CARD_HISTORY]}")
    print(f"\nSaldo: Rp. {card[CARD_BALANCE]}")

    return STATUS_VALID


MIN_REG_BALANCE = float(20000)
MIN_NAME_LEN    = 3
# Prosedur Registrasi kartu kedalam database, mengeluarkan data kartu jika valid 
def card_reg(cardDatabase, databaseSize):
    name    = str  (input("Masukkan nama pengguna (min 3 karakter): "))
    balance = float(input("Maukkan saldo awal (min Rp. 20000,-): Rp. "))

    if((balance < MIN_REG_BALANCE) or (len(name) < MIN_NAME_LEN)):
        print(f"[ERROR] card_reg(): Nama tidak boleh kurang dari {MIN_NAME_LEN} huruf dan saldo awal minimum Rp. {MIN_REG_BALANCE} ")
        return CARD_NULL
    
    cardID = random.randint(1, databaseSize)
    while(card_search(cardDatabase, cardID) != CARD_NULL):
        # print(f"[{i}/{databaseSize}] found ID: {cardID}")
        cardID = random.randint(1, databaseSize)

    return [int(cardID), str(name), float(balance), CARD_STATUS_DEF, CARD_HISTORY_DEF]



# Modifikasi saldo
def card_balance(card, amount: float):
    return card[CARD_BALANCE] + amount

# Top-up Kartu
def card_topup(card):
    print(f"Nama pengguna: {card[CARD_NAME]}. Saldo saat ini: Rp. {card[CARD_BALANCE]}")
    amount = float(input("Masukkan jumlah top-up yang ingin dimasukkan: Rp. "))

    if(amount < 10000):
        print("[INVALID] card_topup(): Min top-up Rp. 20000,-")
        return STATUS_INVALID
    else:
        card[CARD_BALANCE] = card_balance(card, amount)
        return STATUS_VALID_UPDATE

# Menghapus kartu dari database
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
MENU_HELP  = 0
MENU_INFO  = 1
MENU_REG   = 2
MENU_TOPUP = 3
MENU_DEL   = 4
MENU_EXIT  = 5
MENU_PRINT_DATABASE = 6969

card_menu = [
    "Panggil petugas",
    "Info",
    "Registrasi",
    "Top-up Saldo",
    "Delete",
    "Exit"
]

# Print menu-menu dari string array dan meminta input angka dari opsi yang ada
def menuInput(menu) -> int:
    for i in range(len(menu)):
        print(f"\t[{i}]: {menu[i]}")
    
    menuCode = int(input(f"Pilih opsi yang ada ({0}~{len(menu) - 1}): "))
    return menuCode

# Simulasi mesin ATM E-Money
def card_management(cardDatabase: list, databaseFile: str = "cardDatabase.csv"):
    menu = 0
    card = CARD_NULL
    while(True):
        print("\033[2J\033[HSelamat datang di mesin pengelola E-Money.")
        status = STATUS_INVALID
        menu   = menuInput(card_menu)

        # Safety check input menu
        if((menu < 0) or (menu >= len(card_menu))): status = STATUS_INVALID

        # Keperluan untuk prosedur dengan kartu spesifik
        if((menu == MENU_INFO) or (menu == MENU_TOPUP) or (menu == MENU_DEL)):
            for i in range(1, 6):
                card = card_search(cardDatabase, int(input(f"[{i}/6] Silahkan tempelkan kartu E-Money anda. cardID: ")))
                if(card != CARD_NULL): break
        

        # Menjalankan prosedur sesuai pilihan
        if(menu == MENU_INFO):
            status = card_info(card)
        
        elif(menu == MENU_TOPUP):
            status = card_topup(card)

        elif(menu == MENU_DEL):
            status = card_delete(card, cardDatabase)
            if(status == STATUS_VALID_UPDATE): print("Kartu berhasil dihapus")
            else: print("Gagal menghapus kartu")

        elif(menu == MENU_REG):
            card = card_reg(cardDatabase, DEF_DATABASE_SIZE)
            if(card == CARD_NULL): 
                status = STATUS_ERROR
            else: 
                cardDatabase.append(card)
                status = STATUS_VALID_UPDATE

        # Secret Code
        elif(menu == MENU_PRINT_DATABASE):
            status = STATUS_VALID
            for i in range(len(cardDatabase)):
                print(f"{i}:\t{cardDatabase[i]}")

        elif(menu == MENU_EXIT): return STATUS_VALID
        elif(menu == MENU_HELP): return STATUS_ERROR
        
        else:
            status = STATUS_ERROR


        # Post-Processing
        if(status == STATUS_VALID_UPDATE):
            cardDatabase_update(cardDatabase, filename = databaseFile)

        elif((status == STATUS_INVALID) or (status == STATUS_ERROR)): 
            print("Transaksi gagal.")

        print("Tekan tombol apapun untuk melanjutkan...\n")
        msvcrt.getch()

    


cardDatabaseDefault = [
    # [(0) cardID, (1) nama pengguna, (2) saldo, (3) status_kartu, (4) riwayat (Kode Lokasi)]

    [int(120), str("Luthfi"), float(225000), int(0), LOCATION_CODE_NULL],

    [ 231, "Husen", 135000.0, 0, LOCATION_CODE_NULL],
    [ 735, "Intan", 152590.0, 0, LOCATION_CODE_NULL],
    [2910, "Rafi" ,      0.0, 0, LOCATION_CODE_NULL],
    [2924, "Rafa" ,      0.0, 0, LOCATION_CODE_NULL],
    [4336, "Rafo" ,      0.0, 0, LOCATION_CODE_NULL],
    [1902, "Rafu" ,      0.0, 0, LOCATION_CODE_NULL],
]

# cardDatabase_update(cardDatabaseDefault)

if(__name__ == "__main__"):
    cardDatabase = cardDatabase_read()
    card_management(cardDatabase)

