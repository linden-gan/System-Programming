## Computer Network
- Layout
  - Physical layer: cable
  - Data link layer: computers communicate via ethernet. Use media access control (MAC)
  to specify how those computers cooperate.
  - Network layer: the network that span numerous individual unit. Each unit has a router. 
  Each computer has an internet protocol (IP) for receiving packages.
  - Transport layer: an abstract interface to treat network as data stream
    - TCP: stable transportation
    - UDP: unstable transportation
    - Each IP can have multiple ports to receive data
  - Session
  - Presentation
  - Application
- Client-side programming
  - Figure out IP addresses and port
    - addresses in IPv4 (4-byte) or IPv6 (16-byte)
    - addresses are big endian
    - IPv4:
      - `struct sockaddr_in` includes address family, port number,
        `struct in_addr` (host address), and padding.        
      - Address family: `AF_INET`
    - IPv6:
      - `struct sockaddr_in6` includes includes address family, port number,
        `struct in6_addr` (host address), and padding.
      - Address family: `AF_INET6`
    - port number and address numbers are in network order
    - We want a generic structure:
      - `struct sockaddr_storage` includes `struct sockaddr`
      - usually create a sockaddr_storage, then cast it to sockaddr
    - `htonl()` and `ntohl()`: convert between host and network
      byte order
    - `inet_pton()`; `inet_ntop()`; convert between human readable number string to
    internet addresses. p: presentation (human-readable), n: internet address
    - Domain Name System (DNS)
      - use `getaddrinfo()` to get internet address from DNS name: take in domain name,
        service (port number), and a hint to get `struct addrinfo`.
      - set service to `nullptr` if not sure about the service.
  - Create a socket
    - use function `int socket(int domain, int type, int protocol)`
    - e.g. `int fd = socket(AF_INET, SOCK_STREAM, 0);`
  - Connect to server
    - use function `int connect(int sockfd, const struct sockaddr* addr,
      socklen_t addrlen);` return 0 on success, -1 on failure.
    - input our socket fd, `sockaddr` found by `getaddrinfo()`, and
    `sockaddr`'s length.
  - Read
    - -1 for both recoverable and fatal errors
    - 0 for connection closed
    - if there's any amount of data in server, `read()` will read and return
    immediately, possibly with fewer bytes than we asked.
    - if there's no any data, `read()` will block and wait.
  - Write
    - 0 for connection closed.
    - -1 for both recoverable and fatal errors
    - if in our buffer there's no data to write, `write()` will block and wait.
- Server-side Programming
  - Figure out MY OWN server's address
    - `getaddrinfo()` may return a list of address. Need to loop through them until
    finding a suitable one.
  - Create a socket of SERVER: same
  - Bind (similar to connect):
    - use function `int bind(int sockfd, const struct sockaddr* addr,
      socklen_t addrlen);` return 0 on success, -1 on failure.
    - input our socket fd, `sockaddr` found by `getaddrinfo()`, and
      `sockaddr`'s length.
  - Listen: `int listen(int sockfd, int backlog);`
    - tell OS to keep this socket listening for clients' connections
    - backlog: maximum length of connection queue (the queue of clients waiting for
      connection)
    - return 0 on success, -1 on error
  - Accept: `int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);`
    - input a listening sockfd, return parameters are address and addrlen of clients'
      address. Return a file descriptor.
- Miscellenious
  - Network is big endian; while most of local hosts are little endian
  
### Concurrency
- Main sources of tasks: CPU, disk I/O, Network
- Process
  - completely independent, don't share any resources, produced by `fork()` (clone parent
    to child).
- Thread
  - independent stack, but have shared heap and other resources
- Event Driven Programming
  - when one event is happening/finished, what to do next
