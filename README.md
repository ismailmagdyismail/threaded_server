# Brief

- A simple POC using Sockets over TCP to create a multi threaded server
- Multiple Sockets exisit for Accepting connections and acking them back to the client , or sending continoues updates to the connected clients about server status

# How to build and Run

## Building all sub projects

- source enviroment to make sure all enviroment variables and utility functions are defined `source env.bash`
- buildAll : `build`

## Building a specifc project

- buildLib (common files used by both client and server) : `build_lib`
- buildClient (common files used by both client and server) : `build_client`
- buildServer (common files used by both client and server) : `build_server`

## running projet

- NOTE: only one server can be running at any time
- `run` , will display which process to run 1-Client , 2- Server
- `build_run` to compile and run after it

# Main Components

- PassiveSocket : used by server to listen for and accept connections
- ActiveSocket : used to handle sending and recieving of messages
- ReceptionThread(s) : A thread running , listening for connections over a certain socket and accepts connections , offload it to thread pool for processing
- ThreadPool : A pool of threads processing accepted connections in an async way to avoid blocking main thread from accepting connections
- AckReceptionThread : one of the Reception threads used by server , listens for connections on a port specified in env file

# Ports used

- Specified in env.bash file
- used by both client and server to connect to coressponding ports
