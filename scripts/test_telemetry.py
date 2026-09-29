import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.219.100", 5555))
print("connected", flush=True)

with open("debug.log", "a", buffering=1) as f:
    f.write("connected\n")
    while True:
        data = s.recv(4096)
        if not data:
            print("closed", flush=True)
            f.write("closed\n")
            break
        print(repr(data), flush=True)
        f.write(repr(data) + "\n")
