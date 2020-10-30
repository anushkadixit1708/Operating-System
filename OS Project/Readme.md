INTRODUCTION 

The file transfer system created is a server-client based model that allows server to access and process data stored on the client. When a user accesses a file on the client, the client sends the server a copy of the file, which is cached on the server’s computer while the data is being processed and is then returned to the server. 
Server usually passively waits for and responds to clients. Hence it is the passive socket. The client on the other hand, initiates the communication and hence must know the address and the port of the server. It is the active socket. File transferring systems typically use file or database replication (distributing copies of data on multiple servers) to protect against data access failures. This is mainly due to the fact that UDP is not very reliable.

APPROACH

Here, the model uses one client and server implemented using the UDP protocol. The User Datagram Protocol, or UDP, is a communication protocol used across the Internet for especially time-sensitive transmissions such as video playback or DNS lookups. It speeds up communications by not formally establishing a connection before data is transferred. This allows data to be transferred very quickly.
In UDP, the client does not form a connection with the server like in TCP and instead just sends a datagram. Similarly, the server need not accept a connection and just waits for datagrams to arrive. Datagrams upon arrival contain the address of sender which the server uses to send data to the correct client. For establishing connection between the two ends, socket is used. Sockets allow communication between two different processes on the same or different machines and is used in the UNIX client-server application framework.
 

