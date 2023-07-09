# How to Build

To build this project you will need the following dependencies: 

- `libcurl`
- `nlohmann-json` 

On Ubuntu you can install these dependencies as the following: 

```bash
$ sudo apt-get install nlohmann-json3-dev libcurl4-openssl-dev
```


To build we are using `CMake` which can be built using the following commands: 

```bash
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./exchange_rates
```