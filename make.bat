gcc lexer.c -c
gcc symbol_table.c -c
gcc func.c lexer.o symbol_table.o -o func.exe
func sample.txt

