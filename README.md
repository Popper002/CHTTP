# CHTTP

A simple multithreaded HTTP server written in C.  
It serves static files (HTML, CSS, JS, images, etc.) from the `www/` directory and logs all requests in a thread-safe way.

## Features

- Handles HTTP `GET` requests for static files
- Supports multiple file types: `.html`, `.css`, `.js`, `.jpg`, `.png`, etc.
- Multithreaded: each client connection is handled in a separate thread
- Thread-safe access logging with timestamps
- Returns `404 Not Found` for missing files and `400 Bad Request` for unsupported methods

## Project Structure

```
CHTTP/
├── www/               # Static files (index.html, images, css, js, ...)
├── src/
│   ├── server.c       # Server source code
│   └── lib/
│       └── common.h   # Common header
├── access.log         # Access log file
├── Makefile           # Build and run instructions
```

## Build

From the `CHTTP/CHTTP` directory, run:

```sh
make
```

This will compile the server and run it on port 8085 with logging to `access.log`.

## Run Manually

You can also run the server manually:

```sh
gcc -pthread -o server src/server.c
./server 8085 access.log
```

- `8085` is the port number.
- `access.log` is the log file.

## Usage

Put your static files (e.g., `index.html`, images, css, js) in the `www/` directory.

Example requests:

- In your browser:  
  [http://localhost:8085/index.html](http://localhost:8085/index.html)
- From the terminal:
  ```sh
  curl http://localhost:8085/index.html
  curl http://localhost:8085/sonic.jpg
  ```

## Access Log

Each request is logged in `access.log` with a readable timestamp, port, and the full HTTP request.

Example log entry:
```
[TIMESTAMP : 2025-07-01 17:34:33 ] PORT 8085: GET /index.html HTTP/1.1
Host: localhost:8085
...
```

## Notes

- The server looks for files in the `www/` directory relative to where you launch the server.
- If a file does not exist, a 404 error is returned.
- For security, do not use this code in production without further path and input validation.

---

**Author:**  
Riccardo Oro
