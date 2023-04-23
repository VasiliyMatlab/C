#!/bin/bash

gcc Server.c -o server.elf
echo "gcc Server.c -o server.elf"

gcc Client.c -o client.elf
echo "gcc Client.c -o client.elf"
