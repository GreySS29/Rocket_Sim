import socket, sys
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.219.100", 5555))
print("connected", flush=True)
while True:
    data = s.recv(4096)
    if not data:
        print("closed", flush=True)
        break
    sys.stdout.write(repr(data) + "\n")
    sys.stdout.flush()
