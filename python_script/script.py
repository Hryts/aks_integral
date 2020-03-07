import os
import sys


def run(threads_num, experiments_number):
    # Reconfigure
    lines = open(CONF_FILE).read().splitlines()
    thread_line = lines[2].split(sep='=')
    lines[2] = thread_line[0] + '=' + str(threads_num)
    open(CONF_FILE, 'w').write('\n'.join(lines))

    # Recompile
    commands = ['make clean', 'cmake .', 'make']
    for command in commands:
        os.system(command)

    # Run program
    min_time_tmp = float('inf')
    for _ in range(experiments_number):
        cmd = f'{PROG} {CONF_FILE}'
        res = os.popen(cmd).read()
        print(res)
        min_time_tmp = min(min_time_tmp, (float(res.split()[-1][:-1])))

    result = res.split()[2]

    return result, min_time_tmp


def get_path():
    tmp_path = str(__file__).split('/')[:-1]
    return ''.join(tmp_path)


def get_abs_err():
    with open(CONF_FILE) as conf:
        return float(conf.readline().split('=')[-1])


if __name__ == '__main__':
    PATH_TO_SCRIPT = get_path()
    CONF_FILE = f'{PATH_TO_SCRIPT}/../configuration_file.txt'
    PROG = f'{PATH_TO_SCRIPT}/../integral'
    REPS = int(sys.argv[1])
    RESULTS = dict()
    MAX_THREADS = 4
    ABS_ERR = get_abs_err()

    # Collect data from experiments
    for threads_num in range(1, MAX_THREADS+1):
        result, min_time = run(threads_num, REPS)
        RESULTS[str(threads_num)] = (result, min_time)

    # Inspect collected data
    calculations = [float(RESULTS[k][0]) for k in RESULTS.keys()]
    calculations.sort()
    counter_tmp = 1
    counter = 0
    i, j = 0, 1
    while j < len(calculations):
        if calculations[i] + 2 * ABS_ERR >= calculations[j]:
            j += 1
            counter_tmp += 1
        else:
            i += 1
            counter = max(counter, counter_tmp)
            counter_tmp -= 1

    print(f'{counter} out of {len(calculations)} results are within absolute error')

    print(RESULTS)
