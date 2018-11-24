function fast() {
  docker run --rm -v $(pwd):/e -w /e -it yijun/fast:built $@
}
export -f fast

f=${1/.cpp/}
sed -e 's/,.*,/,/g' "$f"_raw_attention_with_node_type.txt > "$f"_raw_attention_without_node_type.txt
fast -z -a -t -Y "$f"_raw_attention_without_node_type.txt $f.pb | sort -g -k7 | tail
fast -H -a -t -Y "$f"_raw_attention_without_node_type.txt $f.pb > $f.html
open $f.html
