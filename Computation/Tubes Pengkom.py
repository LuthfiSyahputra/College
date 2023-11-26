# Define a list of job postings
job_postings = [
    {"title": "Software Engineer"                   , "location": "Bandung"     , "type": "Full-time"},
    {"title": "Data Analyst"                        , "location": "Jakarta"     , "type": "Part-time"},
    {"title": "Project Engineer"                    , "location": "Surabaya"    , "type": "Full-time"},
    {"title": "Sector Manufactur"                   , "location": "Solo"        , "type": "Contract"},
    {"title": "Electrical Design Engineer"          , "location": "Serang"      , "type": "Contract"},
    {"title": "Telecommunication Engineer"          , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Power Systems Engineer"              , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Quality Assurance & Quality Control" , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Consultant"                          , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Machine Learning Engineer"           , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Robotics Engineer"                   , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Research and Development"            , "location": "Jatinangor"  , "type": "Contract"},
    {"title": "Telecommunication Engineer"          , "location": "Jatinangor"  , "type": "Contract"},
    ]

# Function to display job postings based on user's preferences
# Updated function to display job postings with partial matches
def display_jobs(location, job_type):
    matching_jobs = []

    for posting in job_postings:
        if location.lower() in posting["location"].lower() and job_type.lower() in posting["type"].lower():
            matching_jobs.append(posting)

    if matching_jobs:
        print("Matching job postings:")
        for job in matching_jobs:
            print(f"Title: {job['title']}, Location: {job['location']}, Type: {job['type']}")
    else:
        print("No matching job postings found.")


# Main program
while True:
    print("\nJob Seeker Program")
    print("1. Search for jobs")
    print("2. Exit")

    choice = input("Enter your choice (1/2): ")

    if choice == "1":
        location = input("Enter the desired location: ")
        job_type = input("Enter the desired job type (Full-time, Part-time, Contract): ")

        display_jobs(location, job_type)
    elif choice == "2":
        print("Goodbye!")
        break
    else:
        print("Invalid choice. Please select 1 or 2.")