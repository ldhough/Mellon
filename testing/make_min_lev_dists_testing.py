# Takes a list of passwords separated by newlines and creates a csv
# file of two columns, with the first column being each password, and
# the second column being the minimum Levenshtein distance from that
# password to all subsequent passwords in the original list

import editdistance
import sys

def calc_lev_list(l):
    out_list = []
    i = 0
    while i < len(l)-1:
        pass_i_min = 2147483647
        j = i+1
        while j < len(l):
            dist = editdistance.eval(l[i], l[j])
            pass_i_min = dist if dist < pass_i_min else pass_i_min
            j += 1
        out_list.append((l[i][0:-1], str(pass_i_min)))
        i += 1
    print(out_list)
    return out_list

def generate_test_code(l, out_name):
    with open(out_name, "w") as f:
        for element in l:
            f.write("%s,%s\n" % (element[0], element[1]))

for element in sys.argv[1:]:
    file_name = element.split(".")[0] # Strip extension 
    out_file_name = file_name + "_min_levs.csv"
    passwords = []
    with open(element, "r") as f:
        passwords = f.readlines()
    lev_list = calc_lev_list(passwords)
    generate_test_code(lev_list, out_file_name)
