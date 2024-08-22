# Window Workspace Manager

This project provides a command-line utility for managing window placement across virtual desktops (workspaces) on X11-based systems. Specifically, it allows you to move the window currently under the mouse cursor to the next or previous workspace.

## Overview

The utility utilizes X11's Extended Window Manager Hints (EWMH) to interact with the X Window System. It supports the following functionalities:

- Moving the window under the cursor to the next workspace.
- Moving the window under the cursor to the previous workspace.

## Features

- **Move Window to Next Workspace:** Moves the window currently under the cursor to the next workspace.
- **Move Window to Previous Workspace:** Moves the window currently under the cursor to the previous workspace.

## Installation

You can install the app in apt based distros by using the ppa:

```bash
sudo add-apt-repository ppa:porfanid/workspaces
sudo apt update
sudo apt install workspace-window
```

## Requirements

- **CMake**: A build system generator.
- **X11 Development Libraries**: Required for building the project. Install them using:

    - On Debian-based systems:

      ```sh
      sudo apt-get install libx11-dev libxmu-dev
      ```

    - On Red Hat-based systems:

      ```sh
      sudo yum install libX11-devel libXmu-devel
      ```

## Building

To build the project, follow these steps:

1. **Clone the repository:**

   ```sh
   git clone https://github.com/porfanid/workspace-window.git
   cd workspace-window
   ```

2. **Create a build directory and navigate into it:**

   ```sh
   mkdir build
   cd build
   ```

3. **Run CMake to configure the project:**

   ```sh
   cmake ..
   ```

4. **Build the project:**

   ```sh
   make
   ```

   After the build process completes, an executable named `window_workspace_manager` will be created in the `build` directory.

## Usage

The utility expects one argument specifying the direction in which to move the window. The two possible values are `next` and `prev`.

### Syntax

```sh
./window_workspace_manager <direction>
```

### Arguments

- `<direction>`: Specifies the direction to move the window:
    - `next` - Move the window under the cursor to the next workspace.
    - `prev` - Move the window under the cursor to the previous workspace.

### Example

To move the window under the cursor to the next workspace:

```sh
./window_workspace_manager next
```

To move the window under the cursor to the previous workspace:

```sh
./window_workspace_manager prev
```

## Code Explanation

### `move_window_to_workspace`

```cpp
void move_window_to_workspace(Display* display, Window window, int workspace);
```

Sends a client message to move a specific window to the given workspace using the `_NET_WM_DESKTOP` property.

### `get_current_workspace`

```cpp
int get_current_workspace(Display* display);
```

Retrieves the current workspace index by querying the `_NET_CURRENT_DESKTOP` property.

### `get_number_of_workspaces`

```cpp
int get_number_of_workspaces(Display* display);
```

Fetches the total number of workspaces by querying the `_NET_NUMBER_OF_DESKTOPS` property.

### `move_window_to_workspace(Display* display, Window window, bool next)`

Calculates the target workspace based on the current workspace and the direction (`next` or `prev`).

### `get_window_under_cursor`

```cpp
Window get_window_under_cursor(Display* display);
```

Identifies the window currently under the cursor to perform operations on it.

## Troubleshooting

- **Cannot open display**: Ensure that you are running the program in an environment where X11 is accessible.
- **No window under cursor**: Ensure the mouse cursor is over an open window.

## Contribution

Feel free to contribute by submitting issues or pull requests. Enhancements, bug fixes, and documentation improvements are always welcome.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

For any questions or further assistance, please open an issue on the GitHub repository or contact the maintainer.