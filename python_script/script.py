import os
cmd = './integral ../configuration_file.txt'
so = os.popen(cmd).read()
print(so)