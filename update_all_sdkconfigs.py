#!/usr/bin/env python3
import os
import subprocess

# execute './switchconf.sh --list' to get the list of available configurations
output = subprocess.check_output(['bash', './switchconf.sh', '--list']).decode('utf-8').splitlines()

# read symlink './sdkconfig' to get the current configuration
current_config = None
try:
    current_config = os.readlink('./sdkconfig').split('sdkconfig_')[1]
except:
    pass

if len(output) == 0:
    print('No configurations found!')
    exit(1)

if 'bicycle-led-software' not in os.environ['PATH']:
    print('Please execute ". export.sh"')
    exit(1)

for config in output:
    print('Switching to configuration: ' + config)
    subprocess.check_call(['bash', './switchconf.sh', config])
    subprocess.check_call(['idf.py', 'reconfigure'])

if current_config is None:
    print('No current configuration found, exiting')
    exit(0)

# switch back to current configuration
print('Switching back to configuration: ' + current_config)
subprocess.check_call(['bash', './switchconf.sh', current_config])
