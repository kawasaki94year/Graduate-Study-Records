# 将条件写入数组
conditions=("a[3] > 3" "b[5] > 50" "c[4] < -2.4" "d[5] > 2.4")

# 遍历数组中的条件
for i in "${!conditions[@]}"; do
  # 取出当前条件
  condition="${conditions[$i]}"
  # 使用正则表达式分离变量名和比较符号后面的数字
  if [[ "$condition" =~ ^(.*)\s+([<>]=?)\s+([-+]?[0-9]*\.?[0-9]+)$ ]]; then
    # 取出变量名
    var="${BASH_REMATCH[1]}"
    # 取出比较符号
    op="${BASH_REMATCH[2]}"
    # 取出数字
    num="${BASH_REMATCH[3]}"
    # 修改变量的值
    sed -i "s/\($var $op\) *[0-9]*\.?[0-9]*/\1$num/" file.c
  fi
done
