
import socket
def sender():
    # Step 1: Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Step 2: Connect to the receiver machine's IP address and port
    receiver_ip = input("Enter receiver IP address: ")
    receiver_port = 12345
    
    client_socket.connect((receiver_ip, receiver_port))
    
    # Step 3: Send the message to the receiver
    message = input("Enter the message to send: ")
    
    # client_socket.send(message.encode('utf-8'))  # Encode message to bytes and send
    
    # Step 4: Close the socket connection
    client_socket.close()




sender()