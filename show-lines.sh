ls| egrep "\.h|\.cpp"  | xargs -I@ sh -c "wc -l @"
