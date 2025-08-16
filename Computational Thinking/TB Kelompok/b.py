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
],
[
    [6.0, "bandung"],
    [7.0, "sumedang"]
]
]

kode = 201

print(_location[int(kode/100)][kode % 100])