### Lawicel SLCAN Protocol (Serial-Line CAN)

_Copyright &copy; 2016,2020-2024 Uwe Vogt, UV Software, Berlin (info@uv-software.com)_ \
_All rights reserved._

# SLCAN

Implementation of Lawicel SLCAN protocol.

## SLCAN API

```C
slcan_port_t slcan_create(size_t queueSize);
int slcan_destroy(slcan_port_t port);
int slcan_connect(slcan_port_t port, const char *device, const sio_attr_t *attr);
int slcan_disconnect(slcan_port_t port);
int slcan_get_attr(slcan_port_t port, slcan_attr_t *attr);
int slcan_setup_bitrate(slcan_port_t port, uint8_t index);
int slcan_setup_btr(slcan_port_t port, uint16_t btr);
int slcan_open_channel(slcan_port_t port);
int slcan_close_channel(slcan_port_t port);
int slcan_write_message(slcan_port_t port, const slcan_message_t *message, uint16_t timeout);
int slcan_read_message(slcan_port_t port, slcan_message_t *message, uint16_t timeout);
int slcan_status_flags(slcan_port_t port, slcan_flags_t *flags);
int slcan_acceptance_code(slcan_port_t port, uint32_t code);
int slcan_acceptance_mask(slcan_port_t port, uint32_t mask);
int slcan_version_number(slcan_port_t port, uint8_t *hardware, uint8_t *software);
int slcan_serial_number(slcan_port_t port, uint32_t *number);
int slcan_signal(slcan_port_t port);
char *slcan_api_version(uint16_t *version_no, uint8_t *patch_no, uint32_t *build_no);
```

### Build Targets

_Important note_: To build any of the following build targets run the `build_no.sh` script to generate a pseudo build number.
```
gonggomg@uv-pc015deb:~$ cd ~/Projects/CAN/SLCAN
gonggomg@uv-pc015deb:~/Projects/CAN/SLCAN$ ./build_no.sh
```
Repeat this step after each `git commit`, `git pull`, `git clone`, etc.

Then you can build the whole _bleep_ by typing the usual commands:
```
gonggomg@uv-pc015deb:~$ cd ~/Projects/CAN/SLCAN
gonggomg@uv-pc015deb:~/Projects/CAN/SLCAN$ make clean
gonggomg@uv-pc015deb:~/Projects/CAN/SLCAN$ make all
gonggomg@uv-pc015deb:~/Projects/CAN/SLCAN$ sudo make install
```
_(The version number of the libraries can be adapted by editing the `Makefile`s in the subfolders and changing the variable `VERSION` accordingly.  Don´t forget to set the version number also in the source files.)_

#### libSLCAN

___libSLCAN___ is a dynamic library with a basic SLCAN application programming interface for use in __C__ applications.
See header file `slcan.h` for a description of all API functions.

### Target Platforms

POSIX&reg; compatible operating systems:

1. macOS&reg;
1. Linux&reg;
1. Cygwin&reg;

Windows&reg; (x64 operating system):

1. Windows 10 Pro
1. Windows 11 Pro

### Development Environments

#### macOS Sonoma

- macOS Sonoma (14.4) on a Mac mini (M1, 2020)
- Apple clang version 15.0.0 (clang-1500.3.9.4)
- Xcode Version 15.3 (15E204a)

#### macOS Monterey

- macOS Monterey (12.7.4) on a MacBook Pro (2019)
- Apple clang version 13.0.0 (clang-1300.0.29.30)
- Xcode Version 13.2.1 (13C100)

#### macOS High Sierra

- macOS High Sierra (10.13.6) on a MacBook Pro (late 2011)
- Apple LLVM version 10.0.0 (clang-1000.11.45.5)
- Xcode Version 10.1 (10B61)

#### Debian Bullseye (11.2)

- Debian 4.19.160-2 (2020-11-18) x86_64 GNU/Linux
- gcc (Debian 10.2.1-6) 10.2.1 20210110

#### Cygwin (64-bit)

- Cygwin  3.5.1-1.x86_64 under Windows 10 Pro
- GNU C/C++ Compiler (GCC) 11.4.0

#### Windows 10 & 11

- Microsoft Visual Studio Community 2022 (Version 17.9.4)

### CAN Hardware

- Lawicel CANUSB (Hardware 1.0, Firmware 1.1)

## Known Bugs and Caveats

1. Transmitting messages over the TTY is extremely slow; approx. 16ms per frame.
   I guess this is because the transmission is acknowledged by the CAN device.

2. Time-stamps are currently not supported.

## This and That

The documentation of the SLCAN protocol can be found on [Lawicel CANUSB product page](https://www.canusb.com/products/canusb).

### Dual-License

This work is dual-licensed under the terms of the BSD 2-Clause "Simplified" License and under the terms of the GNU General Public License v3.0 (or any later version).
You can choose between one of them if you use this work in whole or in part.

`SPDX-License-Identifier: BSD-2-Clause OR GPL-3.0-or-later`

### Trademarks

Mac and macOS are trademarks of Apple Inc., registered in the U.S. and other countries. \
Windows is a registered trademarks of Microsoft Corporation in the United States and/or other countries. \
POSIX is a registered of the Institute of Electrical and Electronic Engineers, Inc. \
Linux is a registered trademark of Linus Torvalds. \
All other company, product and service names mentioned herein may be trademarks, registered trademarks, or service marks of their respective owners.

### Hazard Note

_If you connect your CAN device to a real CAN network when using this library, you might damage your application._

### Contact

E-Mail: mailto://info@uv-software.com \
Internet: https://www.uv-software.com
