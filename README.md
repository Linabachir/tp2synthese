# tp2synthese
# LAB - TFTP Client
## Objective
The main objective of this practical work is to create a client program capable of exchanging files using the Trivial File Transfer Protocol (TFTP) using the UDP protocole.

## Step 1 - Using command-line arguments for the gettftp programs to obtain request information

We begin by checking that the entered command lines are in the correct format :

We verify that the number of arguments is the expected value.
We check if the file exists and create one if it wasn't the case

## Step 2 - Calling getaddrinfo to obtain the server’s address.

getaddrinfo: Resolves symbolic addresses into usable addresses for network communication.
Use getnameinfo to extract and display the resolved IP and port to verify the connection is correctly set up.

# Step 3 - Reserve a connection socket to the server.

Creating the socket: To connect to the server, we create a socket using the resolved address information:

```  sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);  ```

## Step 4 - Sending the RRQ Packet

The program generates a TFTP Read Request (RRQ) to ask the server for the specified file.

The RRQ packet includes:
	The opcode (00 01 for a read request),
	The filename (ASCII representation),
	A null byte separator (00),
	The transfer mode (octet, followed by a null terminator).

Sending the RRQ:
	The RRQ packet is sent to the server using the sendto function with the socketDescriptor:

```. sendto(sd, rrq, strlen(argv[3]) + 9, 0, result->ai_addr, result->ai_addrlen);  ```

The socketDescriptor is used to manage communication with the server.

After sending the RRQ, the server responds with the first DAT packet containing part of the file.
The program:
		Receives the packet using recvfrom.
	  Writes the file data (excluding the 4-byte header) to the local file:

```. write(fd, buffer + 4, bytes - 4);  ‘‘‘

If the file is larger than 512 bytes, the server sends multiple DAT packets
