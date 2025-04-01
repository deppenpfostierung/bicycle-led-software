#!/usr/bin/env python3
import os
import subprocess

# execute './switchconf.sh --list' to get the list of available configurations
output = subprocess.check_output(['bash', './switchconf.sh', '--list']).decode('utf-8').splitlines()

# read symlink './sdkconfig' to get the current configuration
current_config = os.readlink('./sdkconfig').split('sdkconfig_')[1]

if len(output) == 0:
    print('No configurations found!')
    exit(1)

# check if PATH (env) contains 'bobbycar-boardcomputer-firmware
if 'bicycle-led-software' not in os.environ['PATH']:
    print('Please execute ". export.sh"')
    exit(1)

for config in output:
    print('Switching to configuration: ' + config)
    subprocess.check_call(['bash', './switchconf.sh', config])
    subprocess.check_call(['idf.py', 'reconfigure'])

# switch back to current configuration
print('Switching back to configuration: ' + current_config)
subprocess.check_call(['bash', './switchconf.sh', current_config])
