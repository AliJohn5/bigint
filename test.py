import sys

sys.set_int_max_str_digits(100000000) 

with open('outp.txt',"w") as f:
    f.write(str(2**77232917 - 1))