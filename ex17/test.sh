#!/bin/bash
set -e

echo "Creating database ..."
./ex17_fix_bug db.dat c 1000 1000
echo ""

echo "Saving zed, frank, joe to database ..."
./ex17_fix_bug db.dat s 1 zed zed@zedshaw.com
./ex17_fix_bug db.dat s 2 frank frank@zedshaw.com
./ex17_fix_bug db.dat s 3 joe joe@zedshaw.com
echo ""

echo "Printing all records ..."
./ex17_fix_bug db.dat l
echo ""

echo "Deleting record by id 3 ..."
./ex17_fix_bug db.dat d 3
echo ""

echo "Printing all records ..."
./ex17_fix_bug db.dat l
echo ""

echo "Getting record by id 2 ..."
./ex17_fix_bug db.dat g 2