import socket

def receive_string_over_lan(port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('0.0.0.0', port))
    s.listen(1)
    conn, addr = s.accept()
    string = conn.recv(1024).decode()
    conn.close()
    s.close()
    print(string)
    return string


def sender():
    # Step 1: Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Step 2: Connect to the receiver machine's IP address and port
    receiver_ip = input("Enter receiver IP address: ")
    receiver_port = 12345
    
    client_socket.connect((receiver_ip, receiver_port))
    
    # Step 3: Send the message to the receiver
    message ='''
    mp['A' - 'A'] = {-9,-9};
    mp['B' - 'A'] = {-2,-6};
    mp['C' - 'A'] = {7,-8};
    mp['D' - 'A'] = {-5,3};
    mp['E' - 'A'] = {0,-1};
    mp['F' - 'A'] = {8,-1};
    mp['G' - 'A'] = {3,3};
    mp['H' - 'A'] = {9,9};
    '''
    
    client_socket.send(message.encode('utf-8'))  # Encode message to bytes and send
    
    # Step 4: Close the socket connection
    client_socket.close()




sender()

if __name__ == '__main__':
    sender()