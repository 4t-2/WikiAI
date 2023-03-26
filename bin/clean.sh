text=$(cat "unclean.txt")

newText=""

newText=$(echo $text | sed -e 's/\(.*\)/\L\1/')
newText=$(echo $newText | sed -r 's/[^a-z ]//g')

echo $newText > cleantext.txt
