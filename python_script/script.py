import os
import sys


cmd = './integral ./configuration_file.txt'

min_time = float('inf')
reps = int(sys.argv[1])
results = []
for _ in range(reps):
    print(_)
    so = os.popen(cmd).read()
    min_time = min(min_time, (float(so.split()[-1][:-1])))
    results.append(float(so.split()[2]))

results.sort()



print(min_time)