#!/bin/sh
grep -Ri "@todo" * | grep -v ".svn"
