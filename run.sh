g++ *.cpp -o index `llvm-config --cflags --libs`

./index test.lang

lli output.ll

echo $?

