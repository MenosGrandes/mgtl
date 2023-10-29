#/bin/bash
cd build/benchmarks/
readarray -d '' array < <( find . -executable -type f -print0)

for value in "${array[@]}"
do
  echo "Run Benchmak!: $value"
  hyperfine --warmup 10 $value
done


cd -
