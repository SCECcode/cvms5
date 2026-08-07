#!/usr/bin/env python3

##
#  Retrieves the actual data files from hypocenter. They are
#  very big
#

import getopt
import sys
import shutil
import subprocess
import os

model = "CVMS5"

def usage():
    print("\n./make_data_files.py\n\n")
    sys.exit(0)

def download_urlfile(url, fname):
    # Option 1A: aria2c tuned for slow/unstable connections
    if shutil.which("aria2c"):
        cmd = [
            "aria2c",
            "-x", "4",               # Limit to 4 connections (prevents network congestion)
            "-s", "4",               # Split into 4 parts
            "-c",                    # Always resume partial downloads
            "--max-tries=0",         # Infinite retries if Wi-Fi drops
            "--retry-wait=5",        # Wait 5 sec between retries
            "-o", fname,
            url
        ]
    # Option 1B: curl with resume fallback
    elif shutil.which("curl"):
        cmd = [
            "curl",
            "-L",                    # Follow redirects
            "-C", "-",               # Resume automatically
            "--retry", "999",        # Retry on failure
            "--retry-delay", "5",
            "-o", fname,
            url
        ]
    else:
        raise RuntimeError("Neither aria2c nor curl is installed.")
    process = subprocess.run(cmd, check=True)
# Check for success
    if process.returncode == 0 and os.path.exists(fname):
        print(f"\n[SUCCESS] Download completed! Proceeding with script...")
        return True
    else:
        raise RuntimeError(f"Download failed with exit code {process.returncode}")
    return True

def main():

    # Set our variable defaults.
    path = ""
    mdir = ""

    try:
        fp = open('./config','r')
    except:
        print("ERROR: failed to open config file")
        sys.exit(1)

    ## look for model_data_path and other varaibles
    lines = fp.readlines()
    for line in lines :
        if line[0] == '#' :
          continue
        parts = line.split('=')
        if len(parts) < 2 :
          continue;
        variable=parts[0].strip()
        val=parts[1].strip()

        if (variable == 'model_data_path') :
            path = val + '/' + model
            continue
        if (variable == 'model_dir') :
            mdir = "./"+val;
            continue
        continue
    if path == "" :
        print("ERROR: failed to find variables in config file")
        sys.exit(1)

    fp.close()

    print("\nDownloading model dataset\n")

    subprocess.check_call(["mkdir", "-p", mdir])

    fname= mdir+ "/vp.dat"
    url = path + "/" + fname
    download_urlfile(url,fname)

    fname= mdir+ "/vs.dat"
    url = path + "/" + fname
    download_urlfile(url,fname)

    print("\nDone!")

if __name__ == "__main__":
    main()
