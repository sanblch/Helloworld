#!/bin/bash

name=$1
build=$2
key=$3

curl -T $name-0.0.$build-Linux.deb -usanblch:$key "https://api.bintray.com/content/sanblch/homework/homework/$build/$name-0.0.$build-Linux.deb;deb_distribution=xenial;deb_component=main;deb_architecture=amd64;publish=1"
