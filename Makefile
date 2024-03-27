#
#	Controller Area Network - Lawicel SLCAN Protocol (Serial-Line CAN)
#
#	Copyright (C) 2016-2024  Uwe Vogt, UV Software, Berlin (info@uv-software.com)
#	All rights reserved.
#
#	This file is part of SLCAN.
#
#	SLCAN is dual-licensed under the BSD 2-Clause "Simplified" License
#	and under the GNU General Public License v3.0 (or any later version). You can
#	choose between one of them if you use SLCAN in whole or in part.
#
#	BSD 2-Clause "Simplified" License:
#	Redistribution and use in source and binary forms, with or without
#	modification, are permitted provided that the following conditions are met:
#	1. Redistributions of source code must retain the above copyright notice, this
#	   list of conditions and the following disclaimer.
#	2. Redistributions in binary form must reproduce the above copyright notice,
#	   this list of conditions and the following disclaimer in the documentation
#	   and/or other materials provided with the distribution.
#
#	SLCAN IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#	OF SLCAN, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#	GNU General Public License v3.0 or later:
#	SLCAN is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	SLCAN is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with SLCAN.  If not, see <https://www.gnu.org/licenses/>.
#
all:
	@./build_no.sh
	@echo "\033[1mBuilding SLCAN...\033[0m"
	$(MAKE) -C Trial $@
	$(MAKE) -C Library $@

clean:
	$(MAKE) -C Trial $@
	$(MAKE) -C Library $@

pristine:
	$(MAKE) -C Trial $@
	$(MAKE) -C Library $@

install:
#	$(MAKE) -C Trial $@
	$(MAKE) -C Library $@

test:
	$(MAKE) -C Trial $@

check:
	$(MAKE) -C Trial $@ 2> checker.txt

build_no:
	@./build_no.sh
	@cat Sources/build_no.h
