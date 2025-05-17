# Setting up the software repository

> [!NOTE]
> This section is still work in progress. Not everything will be accurate or complete.

### Deciding where to get the software from

You can either use the precompiled binaries found in
the [releases](https://github.com/deppenpfostierung/bicycle-led-software/releases) or
compile the software yourself.

If you choose to compile the software yourself, continue reading.

### Compiling the software yourself

First, you need to clone the repository:

```bash
$ git clone --recurse-submodules https://github.com/deppenpfostierung/bicycle-led-software.git

$ cd bicycle-led-software
```

You might also need to install the icon converter script. If you are under archlinux, you can do so by running this:

```bash
$ yay -S python-rgb565-converter
```

If not, you can install it using pip:

```bash
$ pip install rgb565-converter
```

Then, you need to install the required dependencies for the ESP-IDF framework.

```bash
$ ./esp-idf/install.sh
```

Now, use `switchconf.sh` to select a configuration:

```bash
$ ./switchconf.sh --list # List all configurations

$ ./switchconf.sh <configuration> # Select a configuration
```

If everything looks good, you can activate the ESP-IDF environment and build the software:

```bash
$ . export.sh

$ idf.py build
```

### Flashing the software

For convenience, you can use the scripts found in the `tools/` directory to flash the software.