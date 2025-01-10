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
