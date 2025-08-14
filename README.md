
# JetServer

`JetServer` is a lightweight, high-performance HTTP server implemented in C++98. Designed with modularity and extensibility in mind, JetServer supports virtual hosting, customizable routing, CGI execution, and efficient connection handling using `poll()`. It aims to provide a solid foundation for learning server internals or building custom web services.

## 🚀 Key Features

- **HTTP/1.1 Support with Keep-Alive** – Maintain persistent client connections for efficiency.
- **Event-Driven Architecture** – Uses `poll()` for scalable, multiplexed I/O handling.
- **Chunked Response Sending** – Prevents blocking when sending data to slow clients.
- **Isolated Client Request Handling** – Each client has separate parsing and response generation.
- **CGI Script Support** – Execute server-side scripts through configurable CGI programs.
- **Configurable CGI Extensions** – Define which file extensions trigger CGI execution (e.g., `.php`).
- **Flexible Routing & Virtual Hosts** – Support multiple servers, domains, and routes with custom behaviors.
- **Custom Error Pages & Redirections** – Easily define error pages and HTTP redirects.
- **HTTP Method Filtering** – Support for GET, POST, and DELETE with route-specific restrictions.
- **Autoindex Support** – Enable directory browsing when no index file is found.
- **Request Body Size Limit** – Enforce maximum allowed upload size (default 50MB).
- **Developer Mode Toggle** – Enable or disable directory listing globally for development convenience.
- **Customizable Log File Path** – Output logs to a specified file or stdout.
- **Request Logging** – Captures key request details, including client IP, for auditing purposes.
- **Easy Configuration File** – Simple syntax to configure servers, routes, CGI, and more.


## ⚠️ Limitations

- **No HTTPS Support** – Only HTTP is supported; no SSL/TLS encryption.
- **Limited HTTP Methods** – Supports only GET, POST, and DELETE methods.
- **HTTP/1.1 Only** – Does not support HTTP/2 or newer versions.
- **No Cookie Handling** – Does not manage or process HTTP cookies.

## 🛠️ Getting Started

Follow these steps to install, build, and run `JetServer` on a Linux system.

- ### 📦 Prerequisites

    Make sure the following packages are installed:

    - **Debian-based (Ubuntu, Linux Mint, etc.)**:

        ```sh
        sudo apt update && sudo apt install build-essential
        ```
    - **Arch-based (Arch, Manjaro, etc.)**:

        ```sh
        sudo pacman -S base-devel
        ```

- ### ✅ Installation

    - **Build Instructions**:

        - **1- Clone the Repository**:

            ```sh
            git clone https://github.com/oussamakami/jetserver
            cd jetserver
            ```

        - **2- Build the Project**:

            ```sh
            make jetserver
            ```

    - **Run the Web Server**:

        Once built, you can start the Web Server with:

        ```sh
        ./jetserver [config_file_path]
        ```
        > If no configuration file is provided, it defaults to `./jetserver.conf`.

- ### 🐳 Docker:

    If you prefer not to run `JetServer` directly on your machine, you can use Docker:

    - **Build and Run the Server**:

        ```sh
        make docker_run
        ```

        This will:
        - Build and run `jetserver` inside a Docker container.
        - Mount your local `www/` folder into the container.
        - Use the host network to expose the ports directly.
        - Write logs to `stdout`, which you can monitor with:

        ```sh
        docker logs -f jetserver
        ```

    - **Other Docker Commands**:

        - **Stop and remove the container**:

            ```sh
            make docker_kill
            ```

        - **Remove the Docker image**:

            ```sh
            make docker_rmi
            ```

        - **Build the Docker image**:

            ```sh
            make docker_build
            ```

## ⚙️ Configuration File

JetServer is fully configurable using a structured configuration file. It supports **system-wide settings**, **server settings**, and **routes**. Blocks are defined as:

- `START_SYSTEM` … `END_SYSTEM`
- `START_SERVER` … `END_SERVER`
- `START_ROUTE` … `END_ROUTE` (must be inside a SERVER block)

---

### 🖥️ SYSTEM Block

Set global behavior for the server:

| Option           | Description                                                                 | Default       |
|-----------------|-----------------------------------------------------------------------------|---------------|
| `LOG`           | Path to log file                                                             | `stdout`      |
| `CGI`           | Path to CGI program for server-side scripts                                  | Optional      |
| `CGI_EXTENSION` | File extension for CGI scripts (`.py` or `py`)                               | Optional      |
| `BODYSIZE`      | Maximum request body size in bytes                                           | 50MB          |
| `DEVMODE`       | Default `BROWSEDIR` for all routes (`True`/`False`). Disable in production | `True`        |

---

### 🌐 SERVER Block

Configure each server instance:

| Option       | Description                                                                 | Default        |
|-------------|-----------------------------------------------------------------------------|----------------|
| `HOST`      | IP address to bind                                                           | `0.0.0.0`      |
| `PORT`      | Port to listen on                                                           | `8080`         |
| `DOMAIN`    | Domain(s) associated with this server (`\|` separated)                        | Optional       |
| `ERROR_XXX` | Custom path for HTTP error pages (e.g., `ERROR_404`)                        | Auto-generated |

---

### 🛣️ ROUTE Block

Define paths and behavior for each route (inside SERVER block):

| Option          | Description                                                                 | Default                  |
|-----------------|-----------------------------------------------------------------------------|--------------------------|
| `REQ_PATH`      | Path for this route                                                         | Required                 |
| `ROOT`          | Root directory for this route                                               | Required                 |
| `INDEX`         | Default file to serve                                                      | Required                 |
| `METHODS`       | Allowed HTTP methods (`GET\|POST\|DELETE`)                                    | None allowed             |
| `BROWSEDIR`     | Enable directory listing (`True`/`False`)                                   | System `DEVMODE`         |
| `REDIRECT`      | URL to redirect requests                                                   | Optional                 |
| `REDIRECT_TYPE` | `"HARD"` for permanent, `"SOFT"` for temporary redirect                     | `HARD`                   |

---

**💡 Notes:**

- You can define multiple server blocks. Subsequent servers inherit `HOST` and `PORT` from the first server if not specified.
- Always save the configuration file after changes.
- Keep `DEVMODE` disabled in production for security.


## 🗑️ Uninstall

- **To Remove all build object files**:

    ```sh
    make clean
    ```

- **To Remove all build objects including the executable binary**:

    ```sh
    make fclean
    ```

- **To Remove the Docker container and image**:

    ```sh
    make docker_rmi
    ```

- **To Completely remove everything (build objects, executable, Docker container, and image)**:

    ```sh
    make fclean docker_rmi
    ```


## 🤝 Authors

- Oussama Kamili [@oussamakami](https://github.com/oussamakami)

## 📝 License

This Project Is Licensed Under &copy; [**MIT License**](https://github.com/oussamakami/jetserver/blob/master/LICENSE)