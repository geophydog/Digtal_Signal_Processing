'''
    Benchmarks of filtering:
        SAC
        this
        obspy
'''
from obspy import read
import numpy as np
import matplotlib.pyplot as plt

# Read raw data in SAC format.
tr = read('BX.BROLN.BHZ.SAC')[0]
dt = tr.stats.delta
t = np.arange(len(tr.data)) * dt
# Cut off frequency for high-padd filter.
fcl = 0.1
# Cut off frequency for low-padd filter.
fch = 0.3
# Low corner frequency for band-pass filter.
f1 = 0.1
# High corner frequency for band-pass filter.
f2 = 0.3
# Orders of filters.
N = 4
# Low-pass filter of obspy.
trl = tr.copy()
trl.filter('lowpass', freq=fcl, corners=N, zerophase=True)
dl = trl.data
# High-pass filter of obspy.
trh = tr.copy()
trh.filter('highpass', freq=fch, corners=N, zerophase=True)
dh = trh.data
# Band-pass filter of obspy.
trb = tr.copy()
trb.filter('bandpass', freqmin=f1, freqmax=f2, corners=N, zerophase=True)
db = trb.data

# Read filtered data by this C code.
trthisl = read('BX.BROLN.BHZ.SAC.lpthis')[0]
trthish = read('BX.BROLN.BHZ.SAC.hpthis')[0]
trthisb = read('BX.BROLN.BHZ.SAC.bpthis')[0]

# Read filtered data by SAC tool.
trsacl = read('BX.BROLN.BHZ.SAC.lpsac')[0]
trsach = read('BX.BROLN.BHZ.SAC.hpsac')[0]
trsacb = read('BX.BROLN.BHZ.SAC.bpsac')[0]

plt.figure(figsize=(12, 12))
plt.subplot(311)
plt.plot(t, dl, 'r', lw=3, label='obspy')
plt.plot(t, trsacl.data, 'g', lw=2, label='SAC')
plt.plot(t, trthisl.data, 'k', lw=1, label='this')
#plt.xlabel('Time (s)', fontsize=14)
plt.ylabel('Amplitude', fontsize=14)
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.legend(fontsize=12)
plt.title('low-pass filter: <= 0.1 Hz', fontsize=14)

plt.subplot(312)
plt.plot(t, dh, 'r', lw=3, label='obspy')
plt.plot(t, trsach.data, 'g', lw=2, label='SAC')
plt.plot(t, trthish.data, 'k', lw=1, label='this')
#plt.xlabel('Time (s)', fontsize=14)
plt.ylabel('Amplitude', fontsize=14)
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.legend(fontsize=12)
plt.title('high-pass filter: >= 0.3 Hz', fontsize=14)

plt.subplot(313)
plt.plot(t, db, 'r', lw=3, label='obspy')
plt.plot(t, trsacb.data, 'g', lw=2, label='SAC')
plt.plot(t, trthisb.data, 'k', lw=1, label='this')
plt.xlabel('Time (s)', fontsize=14)
plt.ylabel('Amplitude', fontsize=14)
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.legend(fontsize=12)
plt.title('band-pass filter: 0.1 - 0.3 Hz', fontsize=14)
plt.savefig('benchmark.pdf')
plt.show()