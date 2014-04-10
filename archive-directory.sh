#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This is a simple script to archive and compress the contents of a directory.

tar cvf - . --exclude='archive.tar.gz' | gzip -9 - > archive.tar.gz

exit 0
