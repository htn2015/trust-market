import socket 
  
s = socket.socket()   
s.connect(("192.168.106.132", 666))
  
while True:  
      message = raw_input("> ")
      s.send(message)
  
print "adios"  
  
s.close() 