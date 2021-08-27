# Copyright (C) 2021 Keyboard Slayer
# 
# This file is part of WM.
# 
# WM is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# WM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with WM.  If not, see <http://www.gnu.org/licenses/>.

CC ?= gcc 
CFLAGS += 					\
	-std=gnu2x				\
	-Werror					\
	-Wall					\
	-Wextra					\
	-ggdb 					\
	-MD						\
    -fsanitize=undefined	\
	-fsanitize=address		\
	-Ilib/					\
	-Isrc/

LDFLAGS += 					\
    -fsanitize=undefined 	\
	-fsanitize=address

DIRECTORY_GUARD=@mkdir -p $(@D)
BUILD_DIRECTORY ?= build

TARGET 		= cc
SRCS   		= $(wildcard src/*.c) $(wildcard lib/*/*.c)
TEST_SRCS	= $(wildcard tests/*.c)
OBJS   		= $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(SRCS))
TEST_OBJS   = $(patsubst %.c, $(BUILD_DIRECTORY)/%.c.o, $(TEST_SRCS)) $(OBJS)
TEST_OBJS  := $(filter-out $(BUILD_DIRECTORY)/src/main.c.o, $(TEST_OBJS))
TESTOBJS 	= $()

test: LDFLAGS	+= -lcmocka --coverage
test: CFLAGS    += --coverage

$(BUILD_DIRECTORY)/%.c.o: %.c
	$(DIRECTORY_GUARD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(DIRECTORY_GUARD)
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -r build
	-rm $(TARGET)

.PHONY: test
test: $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	@./$@
