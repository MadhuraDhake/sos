size = 3
client_list = [None] * size


def add_client():
    client_id = int(input("client id"))
    name = input("client name")
    telephone = input("client telephone")
    client_details = [client_id, name, telephone]
    index = client_id % size
    for i in range(size):
        if client_list[index] == None:
            client_list[index] = client_details
            print("adding data", index, client_details)
            break
        else:
            index = (index + 1) % size


def search_client():
    client_id = int(input("client id"))
    index = client_id % size
    for i in range(size):
        if client_list[index] != None:
            if client_list[index][0] == client_id:
                print("client is a found at index ", index, client_list[index])
                break
        index = (index + 1) % size
    else:
        print("element is not found")


def delete_client():
    client_id = int(input("client id"))
    index = client_id % size
    for i in range(size):
        if client_list[index] != None:
            if client_list[index][0] == client_id:
                client_list[index] = None
                print("cliet delted")
                break
        index = (index + 1) % size
    else:
        print("element is not found")


def display_clients():
    for i in range(size):
        print(client_list[i])


while True:
    print("\n====== Client Management Menu ======")
    print("1. Add Client")
    print("2. Search Client")
    print("3. Delete Client")
    print("4. Display All Clients")
    print("5. Exit")

    choice = input("Enter your choice (1-5): ")

    if choice == '1':
        add_client()
    elif choice == '2':
        print("search client")
        search_client()
    elif choice == '3':
        print("deleted client")
        delete_client()
    elif choice == '4':
        print("display clients")
        display_clients()
    elif choice == '5':
        print("Exiting program.")
        break
    else:
        print("Invalid choice. Please try again.")
