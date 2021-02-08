#! /bin/bash

./mkimage mm/1.jpg 1image
./mkimage mm/2.jpg 2image
./mkimage mm/3.jpg 3image
./mkimage mm/4.jpg 4image
./mkimage mm/5.jpg 5image
./mkimage mm/6.jpg 6image
./mkimage mm/7.jpg 7image
./mkimage mm/8.jpg 8image
./mkimage mm/9.jpg 9image
./mkimage mm/10.jpg 10image
./mkimage mm/11.jpg 11image
./mkimage mm/12.jpg 12image
./mkimage mm/13.jpg 13image
./mkimage mm/14.jpg 14image
./mkimage mm/15.jpg 15image
./mkimage mm/16.jpg 16image
./mkimage mm/17.jpg 17image
./mkimage mm/18.jpg 18image
./mkimage mm/19.jpg 19image
./mkimage mm/20.jpg 20image

cat 2image >> 1image
cat 3image >> 1image
cat 4image >> 1image
cat 5image >> 1image
cat 6image >> 1image
cat 7image >> 1image
cat 8image >> 1image
cat 9image >> 1image
cat 10image >> 1image
cat 11image >> 1image
cat 12image >> 1image
cat 13image >> 1image
cat 14image >> 1image
cat 15image >> 1image
cat 16image >> 1image
cat 17image >> 1image
cat 18image >> 1image
cat 19image >> 1image
cat 20image >> 1image

mv 1image pics
rm -f *image
