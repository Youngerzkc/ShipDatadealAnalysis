#!/bin/sh
testfile=$1
	cat $1 |cut -d ' ' -f 1 >>portname
