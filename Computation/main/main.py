# Definisikan sampel data untuk job list nya
job_listings = [
    {"company_name": "PT Garuda Indonesia", "location": "Jakarta", "field": "Software Development", "max_age": 35},
    {"company_name": "PT Garuda Indonesia", "location": "Bandung", "field": "Banker", "max_age": 35},
    {"company_name": "PT Garuda Indonesia", "location": "Tangerang", "field": "System Maintenance Officer", "max_age": 35},
    {"company_name": "PT Garuda Indonesia", "location": "Tangerang Selatan", "field": "Data Science", "max_age": 35},
    {"company_name": "PT Asahimas Chemical", "location": "Tangerang", "field": "Security Manager", "max_age": 30},
    {"company_name": "PT Asahimas Chemical", "location": "Cilegon", "field": "Chemical Engineer", "max_age": 30},
    {"company_name": "PT Asahimas Chemical", "location": "Merak", "field": "Electrical Maintenance Officer", "max_age": 30},
    {"company_name": "PT Asahimas Chemical", "location": "Anyer", "field": "Electrical Engineer", "max_age": 30},
    {"company_name": "Schneider Electric", "location": "Jakarta", "field": "EV Battery Specialist", "max_age": 30},
    {"company_name": "Schneider Electric", "location": "Bandung", "field": "Power Engineer", "max_age": 30},
    {"company_name": "Schneider Electric", "location": "Surabaya", "field": "Electrical Maintenance Officer", "max_age": 30},
    {"company_name": "Schneider Electric", "location": "Tangerang Selatan", "field": "Electrical Engineer", "max_age": 30},
    {"company_name": "Schneider Electric", "location": "Jakarta", "field": "Finance Advisor", "max_age": 40},
    {"company_name": "Schneider Electric", "location": "Bandung", "field": "Law Advisor", "max_age": 40},
    {"company_name": "Schneider Electric", "location": "Surabaya", "field": "Human Capital", "max_age": 50},
    {"company_name": "PT PLN Indonesia", "location": "Tangerang", "field": "Electrical Maintenance Officer", "max_age": 30},
    {"company_name": "PT PLN Indonesia", "location": "Anyer", "field": "Electrical Engineer", "max_age": 35},
    {"company_name": "PT PLN Indonesia", "location": "Jakarta", "field": "Power Engineer", "max_age": 35},
    {"company_name": "PT PLN Indonesia", "location": "Sumedang", "field": "Power System Manager", "max_age": 30},
    {"company_name": "PT PLN Indonesia", "location": "Depok", "field": "Data Science", "max_age": 30},
    {"company_name": "PT PLN Indonesia", "location": "Solo", "field": "Data Science", "max_age": 35}
]

# Input preferensi user (yang dipilih)
user_preferences = {
    "location": input("Masukkan lokasi Anda (kosongkan bila ingin dimana saja): "),
    "company_name": input("Masukkan preferensi nama perusahaan (kosongkan bila tidak ada): "),
    "field": input("Masukkan preferensi jenis pekerjaan (kosongkan bila tidak ada: "),
    "max_age": int(input("Masukkan umur Anda: "))
}

# INISIASI JOB YANG MEMENUHI KRITERIA
matching_jobs = []

# Iterasi untuk menemukan job yang sesuai
for job in job_listings:
    if (job["location"] == user_preferences["location"] or user_preferences["location"] == "") and \
       (job["company_name"] == user_preferences["company_name"] or user_preferences["company_name"] == "") and \
       (job["field"] == user_preferences["field"] or user_preferences["field"] == "") and \
       (job["max_age"] >= user_preferences["max_age"]):
        matching_jobs.append(job)

# Iterasi Print job yang sesuai
if len(matching_jobs) > 0:
    print("Matching Jobs:")
    for job in matching_jobs:
        print(f"Company: {job['company_name']}, Location: {job['location']}, Field: {job['field']}, Max Age: {job['max_age']}")
else:
    print("Tidak ada pekerjaan yang sesuai.")
