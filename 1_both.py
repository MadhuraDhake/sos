size = 10
linear_client_list = [None] * size
quadratic_client_list = [None] * size

def add_client_linear():
    client_id = int(input("Client ID: "))
    name = input("Client Name: ")
    telephone = int(input("Client Telephone Number: "))
    client_details = [client_id, name, telephone]

    index = client_id % size
    for i in range(size):
        if linear_client_list[index] is None:
            linear_client_list[index] = client_details
            print(f"Client added using Linear Probing at index {index} {client_details}")
            break
        else:
            index = (index + 1) % size

    print("Linear Client List:", linear_client_list)


def add_client_quadratic():
    client_id = int(input("Client ID: "))
    name = input("Client Name: ")
    telephone = input("Client Telephone Number: ")
    client_details = [client_id, name, telephone]

    index = client_id % size
    if quadratic_client_list[index] is None:
        quadratic_client_list[index] = client_details
        print(f"Client added using Quadratic Probing at index {index} {client_details}")
    else:
        for j in range(1, size):
            t = (index + j * j) % size
            if quadratic_client_list[t] is None:
                quadratic_client_list[t] = client_details
                print(f"Client added using Quadratic Probing at index {t} {client_details}")
                break

    print("Quadratic Client List:", quadratic_client_list)


def search_client(client_list, method_name):
    client_id = int(input("Enter Client ID to search: "))
    index = client_id % size

    for i in range(size):
        if client_list[index] is not None:
            if client_list[index][0] == client_id:
                print(f"Client found at index {index}: {client_list[index]}")
                break
        index = (index + 1) % size
    else:
        print("Client not found.")


def delete_client(client_list, method_name):
    client_id = int(input("Enter Client ID to delete: "))
    index = client_id % size

    for i in range(size):
        if client_list[index] is not None:
            if client_list[index][0] == client_id:
                client_list[index] = None
                print(f"Client deleted at index {index} ({method_name})")
                break
        index = (index + 1) % size
    else:
        print("Client not found.")


def main():
    while True:
        print("\n--- MENU ---")
        print("1: Add Client (Linear Probing)")
        print("2: Add Client (Quadratic Probing)")
        print("3: Search Client (Linear)")
        print("4: Search Client (Quadratic)")
        print("5: Delete Client (Linear)")
        print("6: Delete Client (Quadratic)")
        print("7: Exit")
        ch = int(input("Enter your choice: "))

        if ch == 1:
            add_client_linear()
        elif ch == 2:
            add_client_quadratic()
        elif ch == 3:
            search_client(linear_client_list, "Linear Probing")
        elif ch == 4:
            search_client(quadratic_client_list, "Quadratic Probing")
        elif ch == 5:
            delete_client(linear_client_list, "Linear Probing")
        elif ch == 6:
            delete_client(quadratic_client_list, "Quadratic Probing")
        elif ch == 7:
            print("Exiting...")
            break
        else:
            print("Invalid choice! Please try again.")


main()

'''add_client_linear() Time: O(n), Space: O(1)
add_client_quadratic() Time: O(n), Space: O(1)
search_client() Time: O(n), Space: O(1)
delete_client() Time: O(n), Space: O(1)
Best case for all functions Time: O(1)
Overall space used by linear_client_list and quadratic_client_list: O(n)'''

