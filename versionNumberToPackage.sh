#!/bin/bash
if [ -z "$1" ] || [ -z "$2" ]; then
   exit 0
fi
for i in "$2"/*/*/*;do
   if [ -d "$i" ];then
      cp $1 $i
   fi
done
