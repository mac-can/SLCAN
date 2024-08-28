### Library for Lawicel SLCAN Protocol (Serial-Line CAN)

_Copyright &copy; 2016,2020-2024 Uwe Vogt, UV Software, Berlin (info@uv-software.com)_

![macOS Build](https://github.com/mac-can/SLCAN/actions/workflows/macOS-Build.yml/badge.svg)
![MSBuild x64](https://github.com/mac-can/SLCAN/actions/workflows/msbuild-x64.yml/badge.svg)

# SLCAN

Implementation of Lawicel SLCAN protocol.

## Lawicel SLCAN Protocol

### Supported commands

- `O[CR]` - Open the CAN channel
- `C[CR]` - Close the CAN channel
- `Sn[CR]` - Setup with standard CAN bit-rates (`0` = 10kbps, `1` = 20kbps, ..., `8` = 1000kbps)
- `sxxyy[CR]` -  Setup with BTR0/BTR1 CAN bit-rates (`xx` = BTR0, `yy` = BTR1)
- `tiiildd...[CR]` - Transmit a standard (11bit) CAN frame (`iii` = Id., `l` = DLC, `dd` = Data)
- `Tiiiiiiiildd...[CR]` - Transmit an extended (29bit) CAN frame  (`iiiiiiii` = Id., `l` = DLC, `dd` = Data)
- `riiil[CR]` - Transmit an standard RTR (11bit) CAN frame (`iii` = Id., `l` = DLC)
- `Riiiiiiiil[CR]` - Transmit an extended RTR (29bit) CAN frame (`iiiiiiii` = Id., `l` = DLC)
- `F[CR]` - Read Status Flags (returns 8-bit status register; see below)
- `Mxxxxxxxx[CR]` - Sets Acceptance Code Register (AC0, AC1, AC2 & AC3; LSB first)
- `mxxxxxxxx[CR]` - Sets Acceptance Mask Register (AM0, AM1, AM2 & AM3; LSB first)
- `V[CR]` - Get Version number of both CANUSB hardware and software (returns `Vhhss[CR]` - `hh` = Hw, `ss` = Sw)
- `N[CR]` - Get Serial number of the CANUSB (returns `Naaaa[CR]` - `aaaa` = S/N; alpha-numerical)

Note: Channel configuration commands must be sent before opening the channel. The channel must be opened before transmitting frames.

### CANable SLCAN Protocol (Option 1)

Supported commands

- `O` - Open channel
- `C` - Close channel
- `S0` - Set bitrate to 10k
- `S1` - Set bitrate to 20k
- `S2` - Set bitrate to 50k
- `S3` - Set bitrate to 100k
- `S4` - Set bitrate to 125k
- `S5` - Set bitrate to 250k
- `S6` - Set bitrate to 500k
- `S7` - Set bitrate to 750k
- `S8` - Set bitrate to 1M
- `M0` - Set mode to normal mode (default) *(not supported)*
- `M1` - Set mode to silent mode *(not supported)*
- `A0` - Disable automatic retransmission *(not supported)*
- `A1` - Enable automatic retransmission (default) *(not supported)*
- `TIIIIIIIILDD...` - Transmit data frame (Extended ID) [ID, length, data]
- `tIIILDD...` - Transmit data frame (Standard ID) [ID, length, data]
- `RIIIIIIIIL` - Transmit remote frame (Extended ID) [ID, length]
- `rIIIL` - Transmit remote frame (Standard ID) [ID, length]
- `V` - Returns firmware version and remote path as a string

Note: Channel configuration commands must be sent before opening the channel. The channel must be opened before transmitting frames.

**Note: The firmware currently does not provide any ACK/NACK feedback for serial commands.**

Note: The implementation currently does not support CAN FD commands and frame format.

## SLCAN API

```C
slcan_port_t slcan_create(size_t queueSize);
int slcan_destroy(slcan_port_t port);
int slcan_connect(slcan_port_t port, const char *device, const sio_attr_t *attr);
int slcan_disconnect(slcan_port_t port);
int slcan_get_attr(slcan_port_t port, slcan_attr_t *attr);
int slcan_set_ack(slcan_port_t port, bool on);
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

- macOS Sonoma (14.6.1) on a Mac mini (M1, 2020)
- Apple clang version 15.0.0 (clang-1500.3.9.4)
- Xcode Version 15.4 (15F31d)

#### macOS Monterey

- macOS Monterey (12.7.6) on a MacBook Pro (2019)
- Apple clang version 13.0.0 (clang-1300.0.29.30)
- Xcode Version 13.2.1 (13C100)

#### macOS High Sierra

- macOS High Sierra (10.13.6) on a MacBook Pro (late 2011)
- Apple LLVM version 10.0.0 (clang-1000.11.45.5)
- Xcode Version 10.1 (10B61)

#### Debian "bookworm" (12.5)

- Debian 6.1.99-1 (2024-07-15) x86_64 GNU/Linux
- gcc (Debian 12.2.0-14) 12.2.0

#### Cygwin (64-bit)

- Cygwin 3.5.4-1.x86_64 2024-08-25 16:52 UTC x86_64 Cygwin
- GNU C/C++ Compiler (GCC) 12.4.0

#### Windows 10 & 11

- Microsoft Visual Studio Community 2022 (Version 17.11.1)

### CAN Hardware

- Lawicel CANUSB (Hardware 1.0, Firmware 1.1)
- DSD TECH SH-C31A (CANable 2.0 open hardware)

## Known Bugs and Caveats

1. Transmitting messages over the TTY is extremely slow; approx. 16ms per frame.
   I guess this is because the transmission is acknowledged by the CAN device.

2. Time-stamps are currently not supported.

## This and That

The documentation of the SLCAN protocol can be found on [Lawicel CANUSB](https://www.canusb.com/products/canusb) product page.
For the CANable 2.0 adaptation, see the [CANable Firmware](https://github.com/normaldotcom/canable-fw) documentation on GitHub. 

### Dual-License

Except where otherwise noted, this work is dual-licensed under the terms of the BSD 2-Clause "Simplified" License
and under the terms of the GNU General Public License v3.0 (or any later version).
You can choose between one of them if you use these portions of this work in whole or in part.

### Trademarks

Mac and macOS are trademarks of Apple Inc., registered in the U.S. and other countries. \
Windows is a registered trademarks of Microsoft Corporation in the United States and/or other countries. \
POSIX is a registered of the Institute of Electrical and Electronic Engineers, Inc. \
Linux is a registered trademark of Linus Torvalds. \
Cygwin is a registered trademark of Red Hat, Inc. \
All other company, product and service names mentioned herein may be trademarks, registered trademarks, or service marks of their respective owners.

### Hazard Note

_If you connect your CAN device to a real CAN network when using this library, you might damage your application._

### Contact

E-Mail: mailto://info@mac.can.com \
Internet: https://www.mac-can.net
