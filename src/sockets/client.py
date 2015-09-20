import socket 
  
s = socket.socket()   
s.connect(("localhost", 666))
  
while True:  
      message = raw_input("> ")
      s.send(message)
  
print "adios"  
  
s.close() 