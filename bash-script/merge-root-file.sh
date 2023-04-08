#!/bin/bash
# 设置要合并的文件名规则
file_pattern="tag_[0-9][0-9]_test.root"
# 设置要合并的文件所在的目录列表(dir1表示相对路径)
file_dirs=(
   "/path/to/root/files/dir1"
   "/path/to/root/files/dir2"
   "/path/to/root/files/dir3"
)
# 设置要输出的合并文件所在的目录
merged_dir="/path/to/merged/root/files"
# 设置要输出的合并文件名
merged_file="merged.root"
# 创建临时目录
mkdir /path/to/output_file/merged_file
# 合并文件
for dir in "${file_dirs[@]}"
do
  cd "$dir"
  for file in $(find . -name "$file_pattern")
  do
    cp "$file" "/path/to/output_file/merged_file"
    done
  done
cd "/path/to/output_file/merged_file"
hadd "$merged_dir/$merged_file" rootname*.root
# 删除临时目录
rm -rf "/path/to/output_file/merged_file"
# 输出合并后的文件路径
echo "Merged file saved as: $merged_dir/$merged_file"
