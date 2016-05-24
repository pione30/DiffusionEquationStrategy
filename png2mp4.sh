#!/bin/bash
ffmpeg -y -i ./res/output%04d.png -f mp4 -c:v libx264 -pix_fmt yuv420p output.mp4
