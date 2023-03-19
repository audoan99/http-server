# http_server

## Sections in this file describe:
- Purpose and requirements
- How to build, run, clean
- Example applications
- How to test performance

### Purpose and requirements
====================================
1. Purpose
    + Implement a basic HTTP server that supports HTTP/1.1 in C++
2. Requiements
    + Run on Linux
    + Do not use any third party networking library, i.e. use only Linux system API
    + Handle at least 10,000 concurrent connections
    + Serve at least 100,000 requests per second on a modern personal computer
    + Serve a simple one or two pages website for demonstration

### How to build on different platforms
====================================
1.  To build: run command line "make build"
    + One file execute created
2.  To run: run command line "make run"
    + server running, wait for request
3.  To clean: run command line "make clean"
    + remove file execute

### Example applications
====================================
1. Get data
    + HTML file (Home page):        curl -D - http://localhost:8080/
    + HTML file (404 not found):    curl -D - http://localhost:8080/abc
    ==> Also run the above URLs in browser!
    + Some data need run in browser: 
        image(jpg, gif) http://localhost:8080/test2.gif
                        http://localhost:8080/test1.jpg
2. Post data
    + Send text:
    curl -D - -X POST -H 'Content-Type: text/plain' -d 'Data test ...' http://localhost:8080/save

### How to test performance
====================================
1. Install
    + apache2 (sudo apt-get install apache2-utils)
3. Requires
    + Performance of server dependencies to the computer (CPU, Disk, RAM) and Network(not necessary with localhost)
    + My personal computer configuration:
        Ubuntu 20.04
        Intel(R) Core(TM) i7-7820HQ CPU @ 2.90GHz
        Disk: 500GB SSD
        RAM: 8GB
2. Run test
    + Running server
    + Run tool apache: (Syntax: ab [options] [http[s]://]hostname[:port]/path)
    + Example:  make run
                ab -c 5000 -n 1000 http://localhost:8080/
