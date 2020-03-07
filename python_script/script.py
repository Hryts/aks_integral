import os
import sys
import subprocess


def run(threads_num, experiments_number):
    # Reconfigure
    lines = open(CONF_FILE).read().splitlines()
    thread_line = lines[2].split(sep='=')
    lines[2] = thread_line[0] + threads_num
    open(CONF_FILE, 'w').write('\n'.join(lines))

    # Recompile
    commands = ['make clean', 'cmake .', 'make']
    subprocess.run(commands)

    # Run program
    min_time = float('inf')
    for _ in range(experiments_number):
        cmd = f'{PROG} {CONF_FILE}'
        res = os.popen(cmd).read()
        min_time = min(min_time, (float(so.split()[-1][:-1])))

    result = res.split()[2]

    return result, min_time


if __name__ == '__main__':
    PATH_TO_SCRIPT = __file__
    CONF_FILE = f'{PATH_TO_SCRIPT}/../configuration_file.txt'
    PROG = f'{PATH_TO_SCRIPT}/../integral'
    REPS = int(sys.argv[1])
    RESULTS = dict()
    MAX_THREADS = 4

    for threads_num in range(MAX_THREADS):
        result, min_time = run(threads_num, REPS)
        RESULTS[str(threads_num)] = (result, min_time)

    print(RESULTS)