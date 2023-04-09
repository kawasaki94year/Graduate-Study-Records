#!/bin/bash
#指定要合并的root文件名
file_pattern="tag_0_delphes_events.root"
#指定合并后的root文件名
output="merged.root"
#指定要合并的输入root文件
input_files=(
	"/home/xwl/BG/BGww/Events/run_04_0/$file_pattern"
  "/home/xwl/BG/BGww/Events/run_04_1/$file_pattern"
  "/home/xwl/BG/BGww/Events/run_04_2/$file_pattern"
  "/home/xwl/BG/BGww/Events/run_04_3/$file_pattern"
  "/home/xwl/BG/BGww/Events/run_04_4/$file_pattern"
)
#合并输入root文件
hadd "$output" "${input_files[@]}"
